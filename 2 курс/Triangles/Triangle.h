#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Point.h"
#include <iostream>
#include "math.h"

class Triangle
{
   static int count;
   char* name;

   Point p_one;
   Point p_two;
   Point p_three;

   double s_one_two;
   double s_two_three;
   double s_three_one;

public:

   Triangle();

   Triangle(double one_x_, double one_y_, double two_x_, double two_y_, double three_x_, double three_y_);

   Triangle(const Triangle& other_);

   bool operator>(Triangle other_);

   bool operator>=(Triangle other_);

   bool operator==(Triangle other_);

   Triangle& operator=(Triangle& other_);


   Point Get_P_One();

   Point Get_P_Two();

   Point Get_P_Three();

   void Set_Triangle(double one_x_, double one_y_, double two_x_, double two_y_, double three_x_, double three_y_);

   void Set_Triangle(Point p1_, Point p2_, Point p3_);

   void Set_P_One(double one_x_, double one_y_);

   void Set_P_Two(double two_x_, double two_y_);

   void Set_P_Three(double three_x_, double three_y_);

   int Get_Count();

   void Set_Count(int count_);

   void Print_Triangle();

   double Get_Area_of_Triangle();
   
   double Get_Area_of_Triangle(Point p1_, Point p2_, Point p3_);

   //”гол от точки один в радианах
   double Get_Angle_One_of_Triangle();

   //”гол от точки два в радианах
   double Get_Angle_Two_of_Triangle();

   //”гол от точки три в радианах
   double Get_Angle_Three_of_Triangle();

   void Move_Triangle(double x_, double y_);

   bool Triangle_Includes_Point(Point point_);

   bool Triangle_Includes_Point_Using_Area(Point point_);

   bool Triangle_Includes_Triangle(Triangle other_);

};


