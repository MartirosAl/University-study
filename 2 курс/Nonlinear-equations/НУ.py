# Импорт необходимых библиотек
import sympy as sp  # Для символьных вычислений
import scipy as scp  # Для научных вычислений и оптимизации
import math  # Математические функции
import numpy as np  # Числовые вычисления

# Объявление символьных переменных
x = sp.symbols('x')  # Основная переменная
l = sp.symbols('l')  # Параметр метода


def input_function():
    """Функция для ввода пользовательской функции и её преобразования"""
    expr_str = input("Введите функцию: ")  # Запрос функции у пользователя
    expr = sp.parse_expr(expr_str, local_dict={'x': x})  # Парсинг строки в символьное выражение
    # Возвращаем лямбда-функцию для вычисления значения и строковое представление
    return lambda x_val: expr.subs(x, x_val).evalf(), expr_str


def derivative(func):
    """Вычисление производной функции"""
    # Возвращаем лямбда-функцию для вычисления производной и символьное выражение производной
    return lambda x_val: sp.simplify(sp.diff(func, x)).subs(x, x_val).evalf(), sp.diff(func, x)


def main_condition(a, b, d_func):
    """Проверка условий сходимости метода на интервале [a, b]"""
    # Проверка знаков производной на концах интервала
    if d_func(a) < 0 and d_func(b) < 0:
        return -1  # Оба значения отрицательные
    if d_func(a) > 0 and d_func(b) > 0:
        return 0  # Оба значения положительные
    # Дополнительные условия для разных случаев
    if a > 0 and b > 0:
        if d_func(a) <= 0:
            return 1
        if d_func(b) <= 0:
            return 1
    if a < 0 and b < 0:
        if d_func(a) >= 0:
            return 2
        if d_func(b) >= 0:
            return 2
    return 0  # Условия не выполнены


def intervals(func):
    """Поиск интервалов, где функция меняет знак"""
    intervals = []
    # Перебор возможных интервалов
    for i in range(-1000, 1000):
        # Проверка смены знака функции
        if func(i) * func(i + 1) < 0:
            intervals.append((i, i + 1))  # Добавление интервала
    return intervals


def costal(x):
    """Вспомогательная функция для оптимизации"""
    max_f = float(np.squeeze(d_func(x)))  # Вычисление значения производной
    return -abs(max_f)  # Возвращаем отрицательный модуль (для минимизации)


# Основное тело программы

# Получаем функцию от пользователя
func, func_str = input_function()
# Вычисляем её производную
d_func, d_func_str = derivative(func_str)

# Находим интервалы смены знака
inter = intervals(func)
print("Найденные интервалы:", inter)

# Обработка каждого интервала
for i in range(len(inter)):
    print("Текущий интервал:", inter[i])
    # Создаем копии функций для текущего интервала
    func_c = lambda x: func(x)
    d_func_c = lambda x: d_func(x)
    # Границы интервала
    a = float(inter[i][0])
    b = float(inter[i][1])

    # Проверяем условия сходимости
    mc = main_condition(a, b, d_func_c)
    # Корректируем интервал при необходимости
    while (mc != 0):
        if (mc == -1):
            # Меняем знак функции
            func_c = lambda x: -func(x)
            d_func_c = derivative(f"-({func_str})")[0]
        elif (mc == 1):
            a += 0.001  # Сдвигаем левую границу
        elif (mc == 2):
            b -= 0.001  # Сдвигаем правую границу
        mc = main_condition(a, b, d_func_c)

    # Вывод значений функции и производной на границах
    print("Значения на границах:", func_c(a), func_c(b), d_func_c(a), d_func_c(b))

    # Вычисляем коэффициенты
    k1 = max(float(d_func_c(a)), float(d_func_c(b)))
    k2 = min(float(d_func_c(a)), float(d_func_c(b)))

    # Определяем итерационные функции
    fi = lambda x, l: x - l * func_c(x)  # Основная итерационная функция
    d_fi = lambda x, l: 1 - l * d_func_c(x)  # Производная итерационной функции

    # Находим максимум производной на интервале
    max_val = d_func_c(scp.optimize.minimize_scalar(costal, bounds=(a, b), method='bounded').x)
    # Вычисляем оптимальный параметр lambda
    lam = round(abs(2 / max_val), 2) - 0.01
    # Вычисляем параметр alpha
    if (abs(1 - lam * k2) < abs(1 - lam * k1)):
        alfa = abs(1 - lam * k1)
    else:
        alfa = abs(1 - lam * k2)

    # Начальное приближение
    x0 = (a + b) / 2
    # Первая итерация
    x1 = fi(x0, lam)
    eps = 10 ** -2  # Точность
    # Вычисление количества итераций
    a1 = (abs(x0 - x1))
    a2 = (1 - alfa)
    n = math.ceil(math.log(eps / a1 * a2, alfa))

    # Выполнение итераций
    xn = x1
    print("Начальное приближение x0 = ", x0)
    print("Первая итерация x1 = ", x1)
    for j in range(n - 1):
        xn = fi(xn, lam)  # Вычисление следующего приближения
        print("x", j + 2, "=", xn)  # Вывод результата

    # Вывод итоговых параметров
    print("Параметры метода:")
    print("alfa =", alfa, "max =", max_val, "k1 =", k1, "k2 =", k2, "lam =", lam)