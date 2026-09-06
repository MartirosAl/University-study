import os
from graphviz import Digraph
import itertools


def visualize(dfa, filename="step", format="png", folder="rpni_steps") -> None:
    """
    Визуализирует DFA и сохраняет картинку в указанную папку.
    """
    # Создаем папку, если её нет
    if not os.path.exists(folder):
        os.makedirs(folder)

    dot = Digraph(name="DFA_Step", format=format)
    dot.attr(rankdir="LR", size="10", dpi="1000", fontname="Arial")
    dot.attr("node", shape="circle", style="filled", fillcolor="lightyellow", fontname="Arial")
    dot.node("__start__", shape="point", width="0")
    dot.edge("__start__", dfa.start_state, style="bold")

    for state in dfa.grammar.keys():
        is_final = any(not rule for rule in dfa.grammar[state])
        dot.node(state, label=state, shape="doublecircle" if is_final else "circle")

        for rule in dfa.grammar[state]:
            if rule:
                symbol, target = rule
                label_str = f"{symbol}"

                dot.edge(state, str(target), label=label_str, color="black")

    # Полный путь к файлу: папка + имя
    full_path = os.path.join(folder, filename)
    output_path = dot.render(full_path, cleanup=True)
    print(f" Сохранено: {output_path}")

class DfaParce:
    def __init__(self, grammar):
        self.grammar = grammar

    def find_rule(self, key, char):
        if key not in self.grammar:
            return None

        for rule in self.grammar[key]:
            if not rule:
                continue
            if rule[0] == char:
                return rule
        return None

    def check_word(self, word, start_state = 'q0'):
        state = start_state
        for cur_char in word:
            rule = self.find_rule(state, cur_char)
            if rule:
                state = rule[1]
            else:
                return (False, 'Missing right rule')

        for rule in self.grammar[state]:
            if len(rule) == 0:
                return (True)

        return (False, 'The last state is not accepting') # rule [] means accepting state

    def match_rule(self, rule, example, at):
        result = []
        for part in rule:
            at, result_state = self.match_state(part, example, at)
            if result_state is None:
                return at, None
            result.append(result_state)
        return at, result

    def match_state(self, state, example, at = 0):
        if state not in self.grammar:
            if example[at:].startswith(state):
                return (at + len(state), (state, []))
            else:
                return (at, None)
        rules = self.grammar[state]
        for rule in rules:
            if not rule:
                continue
            left_side, result = self.match_rule(rule, example, at)
            if result is not None:
                return left_side, (state, result)
        if [] in rules:
            left_side, result = self.match_rule([], example, at)
            if result is not None:
                return left_side, (state, result)
        return (0, None)


    def accept_example(self, example, start_state = 'q0'):
        (at, result) = self.match_state(start_state, example)
        if result is None:
            return False
        if at == len(example):
            return True
        return False

class DFA:
    def __init__(self, start_state = 'q0'):
        self.grammar: dict[str, list[str]] = {}
        self.start_state = start_state
        self.grammar[self.start_state] = []
        self.next_state = 0


    def check_transition_possibility(self, state, key):
        rules = self.grammar[state]
        for rule in rules:
            if not rule:
                continue
            if rule[0] == key:
                return rule
        return None

    def new_state(self):
        self.next_state += 1

        new_state = "q" + str(self.next_state)
        self.grammar[new_state] = []
        return new_state

    def add_new_transition(self, from_state, to_state, key):
        self.grammar[from_state].append([key, to_state])
        return self.grammar[from_state]

   #Построение принимающего префиксного дерева
    def build_pta(self, positive_examples):
        for example in positive_examples:
            cur_state = self.start_state
            for char in example:
                transition = self.check_transition_possibility(cur_state, char)
                if transition is None:
                    new_state = self.new_state()
                    self.add_new_transition(cur_state, new_state, char)
                    cur_state = new_state
                else:
                    cur_state = transition[1]
            if [] not in self.grammar[cur_state]:
                self.grammar[cur_state].append([])

        return self


    def accept_example(self, example):
        state = self.start_state
        for char in example:
            found_transition = False
            for rule in self.grammar.get(state, []):
                if rule and rule[0] == char:
                    state = rule[1]
                    found_transition = True
                    break
            if not found_transition:
                return False  # Нет перехода по символу -> отвержение

        # Проверяем, является ли финальное состояние допускающим (содержит [])
        return any(not rule for rule in self.grammar.get(state, []))

    def is_relevant(self, positive_examples, negative_examples):
        for example in negative_examples:
            if self.accept_example(example):
                return False

        for example in positive_examples:
            if not self.accept_example(example):
                print(self.grammar)
                print(example)
                return False
        return True


def unique_rules(rules):
    new_rules: dict[str, list[str]] = {}
    for rule in rules:
        if str(rule) in new_rules:
            continue
        new_rules[str(rule)] = rule
    return [new_rules[rule] for rule in new_rules]


def _state_key(s):
    """Безопасное извлечение номера состояния для корректного сравнения"""
    return int(s[1:]) if s.startswith('q') and s[1:].isdigit() else 0


def merge_states_to_nfa(grammar, state1, state2):
    # Наименьшее состояние становится именем нового узла
    new_state = min(state1, state2, key=_state_key)

    # Копируем грамматику, исключая старые состояния
    new_grammar = {state: grammar[state] for state in grammar if state not in [state1, state2]}
    new_grammar[new_state] = unique_rules(grammar[state1] + grammar[state2])

    # Перенаправляем все переходы, ведущие в state1 или state2, на new_state
    for state in new_grammar:
        new_rules = []
        for rule in new_grammar[state]:
            if len(rule) == 0:
                new_rules.append(rule)
                continue
            if len(rule) <= 1:
                continue

            if rule[1] == state1 or rule[1] == state2:
                new_rules.append([rule[0], new_state])
            else:
                new_rules.append([rule[0], rule[1]])
        new_grammar[state] = new_rules

    return new_grammar, new_state

def get_first_accepts(grammar):
    accepts = {}
    for state in grammar:
        for rule in grammar[state]:
            if not rule:
                accepts[state] = None
    return accepts


def canonical_regular_grammar(nfa_grammar, start_state):
    alphabet = {r[0] for rules in nfa_grammar.values() for r in rules if len(r) == 2}
    dfa_grammar = {}
    queue = [frozenset([start_state])]
    visited = {frozenset([start_state]): None}

    while queue:
        current_states = queue.pop(0)
        # Имя DFA-состояния = наименьшее состояние из текущего подмножества
        state_name = min(current_states, key=_state_key)
        dfa_grammar[state_name] = []

        # Если хотя бы одно исходное состояние допускающее, новое тоже допускающее
        if any([] in nfa_grammar.get(s, []) for s in current_states):
            dfa_grammar[state_name].append([])

        for sym in alphabet:
            next_states = set()
            for s in current_states:
                for rule in nfa_grammar.get(s, []):
                    if len(rule) == 2 and rule[0] == sym:
                        next_states.add(rule[1])
            if next_states:
                next_name = min(next_states, key=_state_key)
                dfa_grammar[state_name].append([sym, next_name])
                if frozenset(next_states) not in visited:
                    visited[frozenset(next_states)] = None
                    queue.append(frozenset(next_states))

    # Начальное состояние DFA всегда будет наименьшим в стартовом подмножестве
    return dfa_grammar, min([start_state], key=_state_key)


def rpni(positive_examples, negative_examples, output_folder="rpni_steps"):
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 1. Строим начальное дерево (PTA)
    dfa = DFA().build_pta(positive_examples)
    start_state = 'q0'

    visualize(dfa, filename=f"step_0_initial_pta", folder=output_folder)

    step_counter = 0
    it_is_still_merging = True

    while it_is_still_merging:
        it_is_still_merging = False
        states = list(dfa.grammar.keys())
        # Сортируем состояния для стабильного порядка перебора (q0, q1, q2...)
        states.sort(key=lambda s: int(s[1:]) if s[1:].isdigit() else 0)

        for i in range(1, len(states)):
            for j in range(i):
                state_i, state_j = states[i], states[j]

                nfa, new_state = merge_states_to_nfa(dfa.grammar, state_i, state_j)

                new_start_state = 'q0' if ('q0' in [state_i, state_j]) else start_state

                cr_grammar, new_start_state = canonical_regular_grammar(nfa, new_start_state)

                new_dfa = DFA(start_state=new_start_state)
                new_dfa.grammar = cr_grammar

                relevance = new_dfa.is_relevant(positive_examples, negative_examples)

                if relevance:
                    dfa = new_dfa
                    start_state = new_start_state
                    it_is_still_merging = True

                    step_counter += 1

                    filename = f"step_{step_counter}_merge_{state_j}_{state_i}"
                    visualize(dfa, filename=filename, folder=output_folder)
                    break
            if it_is_still_merging:
                break

    return dfa

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

learned_dfa = rpni(positive, negative)

visualize(learned_dfa, filename="rpni_result")

print()
print('should all be accept', "Y")
for example in positive:
    result = "Y" if learned_dfa.accept_example(example) else "X"
    print(f"{result} '{example}'")
print("---")

print('should all be rejected', "X")
for s in negative:
    result = "Y" if learned_dfa.accept_example(s) else "X"
    print(f"{result} '{s}'")