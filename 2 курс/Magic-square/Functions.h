#pragma once

int Create_Matrix_f(const char* namefile_, int& size_, int**& matrix_);

bool Is_magic_square(int** matrix_, int size_);

bool The_same_numbers(int** matrix_, int size_);

void Print_Matrix(int** matrix_, int size_);