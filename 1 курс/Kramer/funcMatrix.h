#pragma once

/*
* @brief Функция для решения СЛАУ
* @param n - размер матрицы
* @return Решение СЛАУ
*/
void solveSystem(int n);

/*
* @brief Функция для определителя матрицы
* @param matrix[][100] - матрица
* @param n - размер матрицы
* @return Значение определителя матрицы
*/
float The_determinant(float matrix[][100], int n);