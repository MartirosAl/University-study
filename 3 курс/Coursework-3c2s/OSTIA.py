from graphviz import Digraph
import os
import itertools

class State:
	def __init__(self, name: int):
		self.name: int = name
		self.is_final: bool = False
		self.final_output: str = ""
		self.string_prefix: str = ""
		self.incoming_states: list[State] = []
		self.outcoming_states: list[State] = []

	def __hash__(self):
		return hash(self.name)

	def __eq__(self, other):
		return isinstance(other, State) and self.name == other.name

	def __repr__(self) -> str:
		f = f" [F:'{self.final_output}']" if self.is_final else ""
		return f"State({self.name}){f}"

class SubsequentialTransducer:
	def __init__(self):
		state_zero = State(0)
		self.states: list[State] = [state_zero]
		self.transitions: dict[State, dict[str, tuple[State, str]]] = {state_zero: {}}
		self.next_state = 1

	def new_state(self) -> State:
		new_state = State(self.next_state)
		self.next_state += 1
		self.states.append(new_state)
		self.transitions[new_state] = {}
		return new_state

	def make_transition(self, state_out: State, state_in: State, transition_sym: str, output_string: str) -> None:
		state_in.string_prefix = state_out.string_prefix + transition_sym
		state_in.incoming_states.append(state_out)
		self.transitions[state_out][transition_sym] = (state_in, output_string)
		state_out.outcoming_states.append(state_in)

	def TST(self, samples: list[tuple[str, str]]) -> None:
		for input_str, output_str in samples:
			current_state = self.states[0]
			for sym in input_str:
				if sym not in self.transitions[current_state]:
					new_state = self.new_state()
					self.make_transition(current_state, new_state, sym, "")
				current_state = self.transitions[current_state][sym][0]
			current_state.is_final = True
			if current_state.final_output != "" and current_state.final_output != output_str:
				raise ValueError(f"Conflict in final output for state {current_state.name}")
			current_state.final_output = output_str

	def convert_to_sequential(self) -> None:
		for state in list(self.states):
			if state.is_final:
				new_state = self.new_state()
				new_state.is_final = True
				self.make_transition(state, new_state, "#", state.final_output)
				state.is_final = False
				state.final_output = ""

	def lcp(self, state: State) -> str:
		outputs: list[str] = [out for _, out in self.transitions[state].values()]
		if not outputs: return ""
		common = outputs[0]
		for s in outputs[1:]:
			i = 0
			while i < len(common) and i < len(s) and common[i] == s[i]: i += 1
			common = common[:i]
			if not common: return ""
		return common

	def remove_prefix(self, state: State) -> None:
		u = self.lcp(state)
		for parent in state.incoming_states:
			for sym, (target, out) in self.transitions[parent].items():
				if target is state: self.transitions[parent][sym] = (target, u + out)
		for sym, (target, out) in list(self.transitions[state].items()):
			if out.startswith(u): self.transitions[state][sym] = (target, out[len(u):])

	def OTST(self, raw_samples: list[tuple[str, str]]) -> None:
		self.TST(raw_samples)
		self.convert_to_sequential()
		for state in sorted(self.states, key=lambda s: s.name, reverse=True):
			if state.name != 0: self.remove_prefix(state)

	def clone(self) -> 'SubsequentialTransducer':
		t = object.__new__(SubsequentialTransducer)
		t.states = []
		t.transitions = {}
		t.next_state = self.next_state
		mapping = {}
		for s in self.states:
			ns = State(s.name)
			ns.is_final, ns.final_output, ns.string_prefix = s.is_final, s.final_output, s.string_prefix
			t.states.append(ns)
			mapping[s] = ns
		for s in self.states:
			ns = mapping[s]
			ns.incoming_states = [mapping[p] for p in s.incoming_states if p in mapping]
			ns.outcoming_states = [mapping[c] for c in s.outcoming_states if c in mapping]
		for s, trans in self.transitions.items():
			ns = mapping[s]
			t.transitions[ns] = {sym: (mapping.get(tgt), out) for sym, (tgt, out) in trans.items() if tgt in mapping}
		return t

	def merge(self, state_1: State, state_2: State) -> list[tuple[State, str, str, State, str, State]]:
		if state_1 not in self.transitions or state_2 not in self.transitions: return []
		conflicts: list[tuple[State, str, str, State, str, State]] = []
		trans_1, trans_2 = self.transitions[state_1], self.transitions[state_2]

		for parent in list(state_2.incoming_states):
			trans_p = self.transitions.get(parent)
			if not trans_p: continue
			for sym, (target, out) in list(trans_p.items()):
				if target is state_2:
					trans_p[sym] = (state_1, out)
					if state_1 not in parent.outcoming_states: parent.outcoming_states.append(state_1)
			if state_2 in parent.outcoming_states: parent.outcoming_states.remove(state_2)

		state_1.incoming_states = list(set(state_1.incoming_states + state_2.incoming_states))

		for sym, (target_q, out_q) in list(trans_2.items()):
			if sym in trans_1:
				target_p, out_p = trans_1[sym]
				if out_p == out_q:
					if target_p is not target_q: conflicts.extend(self.merge(target_p, target_q))
				else: conflicts.append((state_1, sym, out_p, target_p, out_q, target_q))
			else:
				trans_1[sym] = (target_q, out_q)
				if target_q not in state_1.outcoming_states: state_1.outcoming_states.append(target_q)

		if state_2.is_final:
			if state_1.is_final and state_1.final_output != state_2.final_output:
				conflicts.append((state_1, '#', state_1.final_output, state_1, state_2.final_output, state_1))
			else:
				state_1.is_final, state_1.final_output = True, state_2.final_output

		if state_2 in self.states: self.states.remove(state_2)
		if state_2 in self.transitions: del self.transitions[state_2]
		state_2.incoming_states.clear()
		state_2.outcoming_states.clear()
		return conflicts

	def push_to_incoming(self, u: str, state: State) -> None:
		if state not in self.transitions or not u: return
		for parent in state.incoming_states:
			trans = self.transitions.get(parent)
			if not trans: continue
			for sym, (target, out) in list(trans.items()):
				if target is state: trans[sym] = (target, u + out)
		for sym, (target, out) in list(self.transitions[state].items()):
			if out.startswith(u): self.transitions[state][sym] = (target, out[len(u):])

	def validate(self, samples: list[tuple[str, str]]) -> bool:
		return all(self.transduce(inp) == exp for inp, exp in samples)

	def OSTIA(self, raw_samples: list[tuple[str, str]]) -> None:
		self.TST(raw_samples)
		self.visualize(f"step_1_Trie")

		self.convert_to_sequential()
		self.visualize(f"step_2_Seq")

		for state in sorted(self.states, key=lambda s: s.name, reverse=True):
			if state.name != 0: self.remove_prefix(state)
		self.visualize(f"step_3_Onward")

		changed = True
		merge_step = 3
		while changed:
			changed = False
			states = sorted([s for s in self.states if s.name != 0], key=lambda s: s.string_prefix)
			for i in range(len(states)):
				q = states[i]
				for p in states[:i]:
					candidate = self.clone()
					p_c = next(s for s in candidate.states if s.name == p.name)
					q_c = next(s for s in candidate.states if s.name == q.name)
					if p_c.is_final and q_c.is_final and p_c.final_output != q_c.final_output: continue

					conflicts = candidate.merge(p_c, q_c)
					resolved = True
					while conflicts:
						r, sym, out1, t1, out2, t2 = conflicts.pop(0)
						if r not in candidate.transitions or t1 not in candidate.transitions or t2 not in candidate.transitions: continue
						u = "".join(a for a, b in zip(out1, out2) if a == b)
						if sym == '#' and out1 != out2: resolved = False; break
						if t1.name < q.name or t2.name < q.name: resolved = False; break
						candidate.push_to_incoming(u, r)
						if t1 is not t2 and t1 in candidate.transitions and t2 in candidate.transitions:
							conflicts.extend(candidate.merge(t1, t2))

					if resolved and candidate.validate(raw_samples):
						self.states, self.transitions, self.next_state = candidate.states, candidate.transitions, candidate.next_state
						merge_step += 1
						self.visualize(f"step_{merge_step}_merge_q{p_c.name}_q{q_c.name}")
						changed = True
						break
				if changed: break

	def transduce(self, input_str: str) -> str | None:
		current, output = self.states[0], ""
		for sym in input_str:
			trans = self.transitions.get(current)
			if not trans or sym not in trans: return None
			current, out = trans[sym]
			output += out
		trans = self.transitions.get(current)
		if trans and "#" in trans: output += trans["#"][1]
		elif current.is_final: output += current.final_output
		else: return None
		return output

	def is_onward(self) -> bool:
		for state in self.states:
			outputs = [out for _, out in self.transitions.get(state, {}).values()]
			if not outputs: continue
			common = outputs[0]
			for out in outputs[1:]:
				i = 0
				while i < len(common) and i < len(out) and common[i] == out[i]: i += 1
				common = common[:i]
				if not common: break
			if common: return False
		return True

	def visualize(self, filename: str = "step_n", format: str = "png", folder="ostia_steps") -> None:
		# Создаем папку, если её нет
		if not os.path.exists(folder):
			os.makedirs(folder)

		dot = Digraph(name="SubsequentialTransducer", format=format)
		dot.attr(rankdir="LR", size="10", dpi="1500", fontname="Arial")
		dot.attr("node", shape="circle", style="filled", fillcolor="lightyellow", fontname="Arial")
		dot.node("__start__", shape="point", width="0")
		dot.edge("__start__", f"q{self.states[0].name}", style="bold")

		for state in self.states:
			sid = f"q{state.name}"
			dot.node(sid, label=sid, shape="doublecircle" if state.is_final else "circle")
			for sym, (target, out) in self.transitions.get(state, {}).items():
				dot.edge(sid, f"q{target.name}", label=f"{sym or 'ε'} / {out or 'ε'}", color="red" if sym=="#" else "black", fontcolor="red" if sym=="#" else "black")

		full_path = os.path.join(folder, filename)
		output_path = dot.render(full_path, cleanup=True)
		print(f" Сохранено: {output_path}")




def run_test(name: str, training_data: list[tuple[str, str]]):
	t = SubsequentialTransducer()
	try:
		# Генерируем безопасный префикс и передаём в OSTIA
		t.OSTIA(training_data)
	except Exception as e:
		print("Ошибка при обучении:", e)
		import traceback
		traceback.print_exc()
		return

	print("Проверка:")
	for inp, exp in training_data:
		res = t.transduce(inp)
		print(f"  '{inp}' -> '{res}' {'Y' if res == exp else f'N (ожид: {exp})'}")

	t.visualize("ostia_result")

def transform(s: str) -> str:
	mapping = {'a': 'b', 'b': 'c', 'c': 'a'}
	return ''.join(mapping[ch] for ch in s)

training_data1 = []
for length in range(0, 4):
	# itertools.product генерирует декартово произведение (все комбинации)
	for combo in itertools.product('abc', repeat=length):
		word = ''.join(combo)
		training_data1.append((word, transform(word)))

training_data2 = []
for length in range(1, 6):
	# Последняя буква всегда 'a', генерируем только префикс
	prefix_len = length - 1
	for prefix in itertools.product('ab', repeat=prefix_len):
		word = ''.join(prefix) + 'a'
		training_data2.append((word, word))


if __name__ == "__main__":
	print("-")
	run_test("Test", training_data1)