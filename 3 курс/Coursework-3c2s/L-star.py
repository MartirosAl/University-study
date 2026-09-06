from typing import Optional
import collections
from graphviz import Digraph
import os
import itertools

class DFA:
	"""Простое представление детерминированного конечного автомата (DFA)."""

	def __init__(self, states: set[str], start: str, accept: set[str],
	             transitions: dict[str, dict[str, str]], alphabet: set[str]):
		self.states = states
		self.start = start
		self.accept = accept
		self.transitions = transitions
		self.alphabet = alphabet

	def accepts(self, word: str) -> bool:
		"""Проверяет, принимает ли автомат строку word."""
		state = self.start
		for c in word:
			if c not in self.alphabet:
				return False
			state = self.transitions[state][c]
		return state in self.accept

	def __repr__(self):
		return (f"DFA(states={len(self.states)}, start='{self.start}', "
		        f"accept={self.accept}, trans={len(self.states)}x{len(self.alphabet)})")


def visualize(dfa: DFA, filename: str = "dfa", format: str = "png",
              folder: str = "lstar_steps") -> None:
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
	dot.edge("__start__", dfa.start, style="bold")

	# Добавляем состояния
	for state in sorted(dfa.states):
		is_final = state in dfa.accept
		shape = "doublecircle" if is_final else "circle"
		dot.node(state, label=state, shape=shape)

	# Добавляем переходы
	for state in sorted(dfa.transitions.keys()):
		transitions = dfa.transitions[state]
		for symbol in sorted(transitions.keys()):
			target = transitions[symbol]
			# Graphviz сам рисует петлю, если source == target
			dot.edge(state, target, label=symbol)

	# Полный путь к файлу: папка + имя
	full_path = os.path.join(folder, filename)
	output_path = dot.render(full_path, cleanup=True)
	print(f"Сохранено: {output_path}")


class LStarLearner:
	"""
	Реализация алгоритма L* (Dana Angluin, 1987).
	Обучает DFA, используя:
	  - Membership Queries (MQ): принадлежит ли строка языку?
	  - Equivalence Queries (EQ): совпадает ли текущая гипотеза с целевым языком?
	"""

	def __init__(self, alphabet: set[str],
	             membership_query: callable[[str], bool],
	             equivalence_query: callable[['DFA'], Optional[str]],
	             visualize_steps: bool = False,
	             visualization_folder: str = "lstar_steps"):
		self.alphabet = sorted(list(alphabet))
		self.mq = membership_query
		self.eq = equivalence_query
		self.S: set[str] = {""}  # Префиксы (строки доступа к состояниям)
		self.E: set[str] = {""}  # Суффиксы (различающие строки)
		self.T: dict[str, dict[str, bool]] = {}  # Таблица наблюдений

		# Параметры визуализации
		self.visualize_steps = visualize_steps
		self.visualization_folder = visualization_folder
		self.step_counter = 0

	def _fill_table(self) -> None:
		"""Заполняет недостающие ячейки таблицы наблюдений через MQ."""
		rows = self.S | {s + a for s in self.S for a in self.alphabet}
		for row in rows:
			if row not in self.T:
				self.T[row] = {}
			for col in self.E:
				if col not in self.T[row]:
					self.T[row][col] = self.mq(row + col)

	def _row(self, w: str) -> tuple[bool, ...]:
		"""Возвращает строку таблицы для слова w (в виде кортежа для сравнения)."""
		return tuple(self.T[w][e] for e in sorted(self.E))

	def _is_closed(self) -> bool:
		"""Проверяет замкнутость таблицы: для каждого s∈S и a∈Σ строка s·a должна совпадать с какой-то строкой из S."""
		for s in self.S:
			for a in self.alphabet:
				sa = s + a
				sa_row = self._row(sa)
				if not any(self._row(s_prime) == sa_row for s_prime in self.S):
					return False
		return True

	def _close(self) -> None:
		"""Делает таблицу замкнутой, добавляя недостающие строки в S."""
		changed = True
		while changed:
			changed = False
			new_rows = []
			for s in self.S:
				for a in self.alphabet:
					sa = s + a
					sa_row = self._row(sa)
					if not any(self._row(s_prime) == sa_row for s_prime in self.S):
						new_rows.append(sa)
			if new_rows:
				self.S.update(new_rows)
				self._fill_table()
				changed = True

	def _is_consistent(self) -> bool:
		"""Проверяет согласованность. Если находит нарушение, добавляет различающий суффикс в E и возвращает False."""
		s_list = sorted(list(self.S))
		for i in range(len(s_list)):
			for j in range(i + 1, len(s_list)):
				s1, s2 = s_list[i], s_list[j]
				if self._row(s1) == self._row(s2):
					for a in self.alphabet:
						s1a, s2a = s1 + a, s2 + a
						if self._row(s1a) != self._row(s2a):
							# Ищем суффикс e, который различает s1·a и s2·a
							for e in sorted(self.E):
								if self.T[s1a][e] != self.T[s2a][e]:
									self.E.add(a + e)
									return False
		return True

	def _make_consistent(self) -> None:
		"""Делает таблицу согласованной."""
		while not self._is_consistent():
			self._fill_table()  # E изменился, нужно пересчитать таблицу

	def _build_hypothesis(self) -> DFA:
		"""Строит DFA-гипотезу из замкнутой и согласованной таблицы."""
		states = list(self.S)
		start = ""
		accept = {s for s in self.S if self.T[s][""]}
		transitions = {s: {} for s in self.S}

		for s in self.S:
			for a in self.alphabet:
				sa = s + a
				sa_row = self._row(sa)
				for s_prime in self.S:
					if self._row(s_prime) == sa_row:
						transitions[s][a] = s_prime
						break
		return DFA(set(states), start, accept, transitions, set(self.alphabet))

	def _visualize_current_state(self) -> None:
		"""Визуализирует текущее состояние обучения."""
		if not self.visualize_steps:
			return

		self.step_counter += 1
		hyp = self._build_hypothesis()
		filename = f"step_{self.step_counter}"
		visualize(hyp, filename)

	def learn(self) -> DFA:
		"""Основной цикл обучения."""

		# Начальное заполнение таблицы
		self._fill_table()
		self._visualize_current_state()

		iteration = 0
		while True:
			iteration += 1

			# Замыкание таблицы
			was_closed = self._is_closed()
			self._close()
			if not was_closed:
				self._visualize_current_state()

			# Согласованность
			was_consistent = self._is_consistent()
			self._make_consistent()
			if not was_consistent:
				self._visualize_current_state()

			# Построение гипотезы
			hyp = self._build_hypothesis()
			self._visualize_current_state()

			# Запрос эквивалентности у учителя
			counterexample = self.eq(hyp)
			if counterexample is None:
				# Финальная визуализация
				self.step_counter += 1
				filename = f"step_{self.step_counter:03d}_FINAL"
				visualize(hyp, filename)
				return hyp  # Автомат выучен

			# Обработка контрпримера
			print(f"Найдена ошибка! Контрпример: '{counterexample}'")
			print(f"Гипотеза: {hyp.accepts(counterexample)}, Цель: {self.mq(counterexample)}")

			# Добавляем все префиксы контрпримера в S (стандартный шаг Angluin)
			old_S = self.S.copy()
			for i in range(len(counterexample) + 1):
				self.S.add(counterexample[:i])
			new_states = self.S - old_S
			print(f"   Добавлены состояния: {sorted(new_states)}")

			self._fill_table()
			self._visualize_current_state(f"Counterexample: '{counterexample}'")

			print(f"\n   Продолжение обучения...")


class Teacher:
	"""Имитация учителя, который знает целевой DFA."""

	def __init__(self, target_dfa: DFA, max_search_len: int = 15):
		self.target = target_dfa
		self.max_len = max_search_len

	def membership_query(self, word: str) -> bool:
		return self.target.accepts(word)

	def equivalence_query(self, hypothesis: DFA) -> Optional[str]:
		"""BFS-поиск кратчайшего контрпримера между гипотезой и целью."""
		queue = collections.deque([""])
		visited = {""}
		while queue:
			word = queue.popleft()
			if len(word) > self.max_len:
				return None
			if hypothesis.accepts(word) != self.target.accepts(word):
				return word
			if len(word) < self.max_len:
				for c in self.target.alphabet:
					nxt = word + c
					if nxt not in visited:
						visited.add(nxt)
						queue.append(nxt)
		return None


if __name__ == "__main__":
	alphabet = {'a', 'b'}

	# Целевой язык: строки, оканчивающиеся на 'a'
	target_dfa = DFA(
		states={'q0', 'q1'},
		start='q0',
		accept={'q1'},
		transitions={
			'q0': {'a': 'q1', 'b': 'q0'},
			'q1': {'a': 'q1', 'b': 'q0'},
		},
		alphabet=alphabet
	)

	print("Целевой автомат:")
	print(f"  Состояния: {target_dfa.states}")
	print(f"  Начальное: {target_dfa.start}")
	print(f"  Принимающие: {target_dfa.accept}")
	print(f"  Переходы: {target_dfa.transitions}")

	visualize(target_dfa, filename="target_dfa")

	# Создаем папку для визуализаций
	viz_folder = "lstar_steps"
	if os.path.exists(viz_folder):
		import shutil

		shutil.rmtree(viz_folder)

	teacher = Teacher(target_dfa)
	learner = LStarLearner(
		alphabet,
		teacher.membership_query,
		teacher.equivalence_query,
		visualize_steps=True,  # Включаем визуализацию
		visualization_folder=viz_folder
	)

	learned_dfa = learner.learn()

	# Проверка на тестовых строках
	print("Проверка")
	positive = []
	for length in range(1, 5):
		# Последняя буква всегда 'a', генерируем только префикс
		prefix_len = length - 1
		for prefix in itertools.product('ab', repeat=prefix_len):
			word = ''.join(prefix) + 'a'
			positive.append(word)
	all_ok = True
	for w in positive:
		h_acc = learned_dfa.accepts(w)
		t_acc = target_dfa.accepts(w)
		status = "Y" if h_acc == t_acc else "N"
		print(f"  {status} '{w}': Гипотеза={h_acc}, Цель={t_acc}")
		if h_acc != t_acc:
			all_ok = False

	negative = []
	for length in range(1, 5):
		# Последняя буква всегда 'b', генерируем только префикс
		prefix_len = length - 1
		for prefix in itertools.product('ab', repeat=prefix_len):
			word = ''.join(prefix) + 'b'
			negative.append(word)

	for w in negative:
		h_acc = learned_dfa.accepts(w)
		t_acc = target_dfa.accepts(w)
		status = "Y" if h_acc == t_acc else "N"
		print(f"  {status} '{w}': Гипотеза={h_acc}, Цель={t_acc}")
		if h_acc != t_acc:
			all_ok = False

	if all_ok:
		print("Успешно")
	else:
		print("Обнаружены расхождения.")
	print(f"\nВизуализации сохранены в папку: {viz_folder}/")