import os
from graphviz import Digraph
import itertools


class DFASynthesizer:
	def __init__(self, alphabet):
		self.alphabet = sorted(alphabet)
		self.states = []
		self.transitions = {}
		self.accepting = set()
		self.start_state = None

	def build_from_examples(self, P, N, visualize_steps=True, viz_folder="trakhtenbrot"):
		P, N = set(P), set(N)

		# 1. Проверка непротиворечивости (прямые конфликты)
		if P & N:
			raise ValueError("Примеры противоречивы: пересечение P и N не пусто.")

		# 2. Построение дерева префиксов (Trie)
		# Используем явные булевы флаги, чтобы избежать путаницы None/False
		trie = {'is_end': False, 'children': {}}
		for word in sorted(P | N):  # sorted для детерминизма обхода
			node = trie
			for char in word:
				if char not in self.alphabet:
					raise ValueError(f"Символ '{char}' в примере отсутствует в алфавите {self.alphabet}")
				if char not in node['children']:
					node['children'][char] = {'is_end': False, 'children': {}}
				node = node['children'][char]
			node['is_end'] = word in P

		# 3. Преобразование Trie в начальный ДКА
		self.states = []
		self.transitions = {}
		self.accepting = set()

		# Создаем начальное состояние (0) и состояние-сток (1)
		self.start_state = self._add_state()
		sink_state = self._add_state()
		for char in self.alphabet:
			self.transitions[sink_state][char] = sink_state

		self._build_automaton_from_trie(trie, self.start_state, sink_state)

		if visualize_steps:
			self.visualize(filename="01_initial_dfa", folder=viz_folder)

		# 4. Минимизация (алгоритм Мура)
		self._merge_equivalent_states()

		if visualize_steps:
			self.visualize(filename="02_minimized_dfa", folder=viz_folder)

		# 5. Верификация на исходных примерах
		self._verify_examples(P, N)

		if visualize_steps:
			self.visualize(filename="03_final_verified_dfa", folder=viz_folder)

		return self

	def _add_state(self):
		q = len(self.states)
		self.states.append(q)
		self.transitions[q] = {}
		return q

	def _build_automaton_from_trie(self, node, state, sink_state):
		# Явно устанавливаем принимающий статус
		if node['is_end']:
			self.accepting.add(state)
		else:
			self.accepting.discard(state)

		# Заполняем переходы. Если ребра в Trie нет -> ведем в сток.
		for char in self.alphabet:
			if char in node['children']:
				next_state = self._add_state()
				self.transitions[state][char] = next_state
				# Рекурсивный обход только существующих ветвей
				self._build_automaton_from_trie(node['children'][char], next_state, sink_state)
			else:
				self.transitions[state][char] = sink_state

	def _merge_equivalent_states(self):
		# 1. Начальное разбиение: принимающие vs не принимающие
		non_accepting = set(self.states) - self.accepting
		partition = [g for g in [self.accepting, non_accepting] if g]

		changed = True
		while changed:
			changed = False
			new_partition = []
			for group in partition:
				subgroups = {}
				for q in group:
					# Строгая проверка: переходы должны существовать для всех символов алфавита
					signature = tuple(self.transitions[q][a] for a in self.alphabet)
					subgroups.setdefault(signature, []).append(q)

				if len(subgroups) > 1:
					changed = True
					new_partition.extend(subgroups.values())
				else:
					new_partition.append(group)
			partition = new_partition

		# 2. Сжатие автомата: маппинг старых состояний на репрезентантов классов
		state_map = {}
		for group in partition:
			rep = min(group)
			for q in group:
				state_map[q] = rep

		# Перенумеровываем состояния последовательно 0..k-1 для каноничности
		unique_reps = sorted(set(state_map.values()))
		canon_map = {old_rep: new_idx for new_idx, old_rep in enumerate(unique_reps)}

		# Перестраиваем таблицу переходов и множество принимающих состояний
		new_states = list(canon_map.values())
		new_trans = {
			canon_map[rep]: {
				a: canon_map[state_map[self.transitions[rep][a]]]
				for a in self.alphabet
			}
			for rep in unique_reps
		}
		new_accept = {canon_map[state_map[q]] for q in self.accepting}
		new_start = canon_map[state_map[self.start_state]]

		# Обновляем атрибуты класса
		self.states = new_states
		self.transitions = new_trans
		self.accepting = new_accept
		self.start_state = new_start

	def _verify_examples(self, P, N):
		def run(word):
			state = self.start_state
			for ch in word:
				if ch not in self.alphabet:
					raise ValueError(f"Символ '{ch}' не принадлежит алфавиту автомата.")
				state = self.transitions[state][ch]
			return state in self.accepting

		for w in P:
			if not run(w):
				raise ValueError(f"Автомат отвергает положительный пример: '{w}'")
		for w in N:
			if run(w):
				raise ValueError(f"Автомат принимает отрицательный пример: '{w}'")

	def accepts(self, word):
		state = self.start_state
		for ch in word:
			if ch not in self.alphabet:
				raise ValueError(f"Символ '{ch}' не принадлежит алфавиту автомата.")
			state = self.transitions[state][ch]
		return state in self.accepting

	def visualize(self, filename: str = "dfa", format: str = "png",
	              folder: str = "trakhtenbrot") -> None:
		if not self.states:
			print("Автомат пуст, визуализация невозможна.")
			return

		if not os.path.exists(folder):
			os.makedirs(folder)

		dot = Digraph(name="DFA_Step", format=format)
		dot.attr(rankdir="LR", ratio="auto", dpi="1000", fontname="Arial", size="10")
		dot.attr("node", shape="circle", style="filled", fillcolor="lightyellow", fontname="Arial")
		dot.node("__start__", shape="point", width="0", fixedsize="true")

		if self.start_state is not None:
			dot.edge("__start__", str(self.start_state), style="bold")

		for q in self.states:
			dot.node(str(q), label=str(q), shape="doublecircle" if q in self.accepting else "circle")

		for q in self.states:
			for char, target in self.transitions.get(q, {}).items():
				dot.edge(str(q), str(target), label=str(char))

		full_path = os.path.join(folder, filename)
		output_path = dot.render(full_path, cleanup=True)
		print(f"Сохранено: {output_path}")


if __name__ == "__main__":
	ALPHABET = {'a', 'b'}
	positive = []
	for length in range(1, 5):
		# Последняя буква всегда 'a', генерируем только префикс
		prefix_len = length - 1
		for prefix in itertools.product('ab', repeat=prefix_len):
			word = ''.join(prefix) + 'a'
			positive.append(word)

	negative = []
	for length in range(1, 5):
		# Последняя буква всегда 'b', генерируем только префикс
		prefix_len = length - 1
		for prefix in itertools.product('ab', repeat=prefix_len):
			word = ''.join(prefix) + 'b'
			negative.append(word)

	synthesizer = DFASynthesizer(ALPHABET)
	synthesizer.build_from_examples(positive, negative, visualize_steps=True, viz_folder="Trakhtenbrot")

	print("\nПроверка:")
	print('Должно приниматься')
	for test in positive:
		res = synthesizer.accepts(test)
		print(f"   '{test}' -> {'Принимается' if res else 'Отвергается'}")
	print('Должно отвергаться')
	for test in negative:
		res = synthesizer.accepts(test)
		print(f"   '{test}' -> {'Принимается' if res else 'Отвергается'}")