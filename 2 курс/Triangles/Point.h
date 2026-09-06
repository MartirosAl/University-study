#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Point
{
   double x;
   double y;

public:

   Point();

   Point(double x_, double y_);

   Point operator=(const Point& other_);

   Point operator+(const Point& other_);

   Point operator-(const Point& other_);

   //—кал€рное произведение
   double operator*(const Point& other_);

   void operator+=(const Point& other_);

   Point operator()(double x_, double y_);

   double Get_X();

   double Get_Y();

   void Set_X(double x_);

   void Set_Y(double y_);

   void Set_Points(double x_, double y_);

   void Print_Points();
};

