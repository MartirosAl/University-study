#include "Point.h"

   Point::Point()
   {
      x = 0;
      y = 0;
   }

   Point::Point(double x_, double y_)
   {
      x = x_;
      y = y_;
   }

   Point Point::operator=(const Point& other_)
   {
      x = other_.x;
      y = other_.y;
      return *this;
   }

   Point Point::operator+(const Point& other_)
   {
      return Point(x + other_.x, y + other_.y);
   }

   Point Point::operator-(const Point& other_)
   {
      return Point(x - other_.x, y - other_.y);
   }

   //—кал€рное произведение
   double Point::operator*(const Point& other_)
   {
      return x * other_.x + y * other_.y;
   }

   void Point::operator+=(const Point& other_)
   {
      x += other_.x;
      y += other_.y;
   }

   Point Point::operator()(double x_, double y_)
   {
      x = x_;
      y = y_;
      return *this;
   }

   double Point::Get_X()
   {
      return x;
   }

   double Point::Get_Y()
   {
      return y;
   }

   void Point::Set_X(double x_)
   {
      x = x_;
   }

   void Point::Set_Y(double y_)
   {
      y = y_;
   }

   void Point::Set_Points(double x_, double y_)
   {
      x = x_;
      y = y_;
   }

   void Point::Print_Points()
   {
      printf("(%.3lf, %.3lf) ", x, y);
   }
