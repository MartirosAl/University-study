import numpy as np


# Преобразование матрицы к диагональному преобладанию
def convert_to_diagonal_dominance(matrix, vector):
    size = len(matrix)
    matrix = matrix.copy()
    vector = vector.copy()

    print("\nНачальное преобразование матрицы для обеспечения диагонального преобладания...")

    for row_index in range(size):
        # Находим индекс максимального элемента в строке
        row_abs = abs(matrix[row_index])
        max_index = np.argmax(row_abs)
        # Меняем местами текущую строку и строку с максимальным элементом
        if max_index != row_index:
            print(f"Перестановка строки {row_index + 1} со строкой {max_index + 1}")
            matrix[[row_index, max_index]] = matrix[[max_index, row_index]]
            vector[[row_index, max_index]] = vector[[max_index, row_index]]

    print("Преобразованная матрица:")
    for i in range(size):
        print(f"Строка {i + 1}:", " ".join(f"{x:.3f}" for x in matrix[i]), "|", f"{vector[i]:.3f}")

    return matrix, vector


# Метод простых итераций
def iterative_method(matrix, vector, tolerance=1e-2, max_iterations=100):
    size = len(vector)
    approximation = np.zeros(size)

    print("\nЗапуск итерационного процесса решения системы...")
    print(f"Параметры метода: точность = {tolerance}, макс. итераций = {max_iterations}")
    print("Начальное приближение:", " ".join(f"{x:.3f}" for x in approximation))

    for iteration in range(max_iterations):
        new_approximation = np.zeros(size)
        for row_index in range(size):
            # Суммируем все элементы, кроме диагонального
            sum_of_others = sum(matrix[row_index][col_index] * approximation[col_index]
                                for col_index in range(size) if col_index != row_index)
            # Вычисляем новое значение для текущей переменной
            new_approximation[row_index] = (vector[row_index] - sum_of_others) / matrix[row_index][row_index]

        # Выводим информацию о текущей итерации
        diff = np.max(np.abs(new_approximation - approximation))
        print(f"\nИтерация {iteration + 1}:")
        print("Текущее решение:", " ".join(f"{x:.5f}" for x in new_approximation))
        print("Максимальное изменение:", f"{diff:.5f}")

        # Проверяем, достигнута ли сходимость
        if diff < tolerance:
            print(f"\nРешение найдено за {iteration + 1} итераций с требуемой точностью.")
            return new_approximation

        approximation = new_approximation.copy()

    print("\nВнимание: метод не сошелся за указанное число итераций!")
    print("Возможно, следует увеличить количество итераций или проверить условия сходимости.")
    return approximation


# Считывание данных из файла
def load_input_file(filename):
    print(f"Чтение входных данных из файла '{filename}'...")
    with open(filename, 'r') as file:
        # Читаем строки и преобразуем их в числовые массивы
        lines = [list(map(float, line.split())) for line in file]

    matrix = np.array([line[:-1] for line in lines])  # Все, кроме последнего элемента
    vector = np.array([line[-1] for line in lines])  # Последний элемент каждой строки

    print("\nИсходная система уравнений:")
    for i, (row, b) in enumerate(zip(matrix, vector)):
        eq = " + ".join(f"{a:.2f}x{i + 1}" for i, a in enumerate(row))
        print(f"Уравнение {i + 1}: {eq} = {b:.2f}")

    return matrix, vector


# Пример использования
if __name__ == "__main__":
    filename = "input.txt"  # Задайте свой файл
    try:
        matrix, vector = load_input_file(filename)
        matrix, vector = convert_to_diagonal_dominance(matrix, vector)
        solution = iterative_method(matrix, vector)
        print("\nФинальный результат:")
        for i, x in enumerate(solution):
            print(f"x{i + 1} = {x:.6f}")
    except FileNotFoundError:
        print(f"\nОшибка: файл '{filename}' не найден!")
    except Exception as e:
        print(f"\nПроизошла ошибка: {str(e)}")