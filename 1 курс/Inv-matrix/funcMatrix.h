#pragma once

/*
* @brief Функция для определителя матрицы
* @param matrix[][100] - матрица
* @param n - размер матрицы
* @return Значение определителя матрицы
*/
float The_determinant(float matrix[][100], int n);

/*
* @brief Функция для обратной матрицы
* @param matrix[][100] - матрица
* @param n - размер матрицы
* @return Указатель на обратную матрицу
*/
void inverse(float matrix[][100], int n);
