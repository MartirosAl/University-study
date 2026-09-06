#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Point.h"
#include "Triangle.h"

void Print_Triangles(Triangle* triangles_, int size_);

int Expansion(Triangle*& arr_, size_t& size_);

Triangle* Find_Max(Triangle* arr_, size_t size_);

void Menu();

bool Is_Triangle(double one_x_, double one_y_, double two_x_, double two_y_, double three_x_, double three_y_);
