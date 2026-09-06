#include "Triangle.h"

int Triangle::count = 1;


Triangle::Triangle()
{
   name = new char[100];

   sprintf(name, "Triangle %d", count);
   count++;

   s_one_two = 0;
   s_two_three = 0;
   s_three_one = 0;
}

Triangle::Triangle(double one_x_, double one_y_, double two_x_, double two_y_, double three_x_, double three_y_)
{
   name = new char[100];

   sprintf(name, "Triangle %d", count);
   count++;

   p_one(one_x_, one_y_);
   p_two(two_x_, two_y_);
   p_three(three_x_, three_y_);

   s_one_two = sqrt(pow(one_x_ - two_x_, 2) + pow(one_y_ - two_y_, 2));
   s_two_three = sqrt(pow(two_x_ - three_x_, 2) + pow(two_y_ - three_y_, 2));
   s_three_one = sqrt(pow(three_x_ - one_x_, 2) + pow(three_y_ - one_y_, 2));
}

Triangle::Triangle(const Triangle& other_)
{
   name = other_.name;

   p_one = other_.p_one;
   p_two = other_.p_two;
   p_three = other_.p_three;

   s_one_two = sqrt(pow(p_one.Get_X() - p_two.Get_X(), 2) + pow(p_one.Get_Y() - p_two.Get_Y(), 2));
   s_two_three = sqrt(pow(p_two.Get_X() - p_three.Get_X(), 2) + pow(p_two.Get_Y() - p_three.Get_Y(), 2));
   s_three_one = sqrt(pow(p_three.Get_X() - p_one.Get_X(), 2) + pow(p_three.Get_Y() - p_one.Get_Y(), 2));
}

bool Triangle::operator>(Triangle other_)
{
   if (Get_Area_of_Triangle() > other_.Get_Area_of_Triangle())
      return true;
   else
      return false;
}

bool Triangle::operator>=(Triangle other_)
{
   if (Get_Area_of_Triangle() >= other_.Get_Area_of_Triangle())
      return true;
   else
      return false;
}

bool Triangle::operator==(Triangle other_)
{
   return Get_Area_of_Triangle() == other_.Get_Area_of_Triangle();
}

Triangle& Triangle::operator=(Triangle& other_)
{
   if (&other_ == this) return *this;

   delete[] name;
   name = new char[100];
   strcpy(name, other_.name);

   p_one = other_.p_one;
   p_two = other_.p_two;
   p_three = other_.p_three;

   s_one_two = other_.s_one_two;
   s_two_three = other_.s_two_three;
   s_three_one = other_.s_three_one;

   return *this;
}


Point Triangle::Get_P_One()
{
   return p_one;
}

Point Triangle::Get_P_Two()
{
   return p_two;
}

Point Triangle::Get_P_Three()
{
   return p_three;
}

void Triangle::Set_Triangle(double one_x_, double one_y_, double two_x_, double two_y_, double three_x_, double three_y_)
{
   p_one.Set_Points(one_x_, one_y_);
   p_two.Set_Points(two_x_, two_y_);
   p_three.Set_Points(three_x_, three_y_);

   s_one_two = sqrt(pow(one_x_ - two_x_, 2) + pow(one_y_ - two_y_, 2));
   s_two_three = sqrt(pow(two_x_ - three_x_, 2) + pow(two_y_ - three_y_, 2));
   s_three_one = sqrt(pow(three_x_ - one_x_, 2) + pow(three_y_ - one_y_, 2));
}

void Triangle::Set_Triangle(Point p1_, Point p2_, Point p3_)
{
   p_one = p1_;
   p_two = p2_;
   p_three = p3_;

   s_one_two = sqrt(pow(p1_.Get_X() - p2_.Get_X(), 2) + pow(p1_.Get_Y() - p2_.Get_Y(), 2));
   s_two_three = sqrt(pow(p2_.Get_X() - p3_.Get_X(), 2) + pow(p2_.Get_Y() - p3_.Get_Y(), 2));
   s_three_one = sqrt(pow(p3_.Get_X() - p1_.Get_X(), 2) + pow(p3_.Get_Y() - p1_.Get_Y(), 2));
}

void Triangle::Set_P_One(double one_x_, double one_y_)
{
   p_one.Set_X(one_x_);
   p_one.Set_Y(one_y_);

   s_one_two = sqrt(pow(one_x_ - p_two.Get_X(), 2) + pow(one_y_ - p_two.Get_Y(), 2));
   s_three_one = sqrt(pow(p_three.Get_X() - one_x_, 2) + pow(p_three.Get_Y() - one_y_, 2));
}

void Triangle::Set_P_Two(double two_x_, double two_y_)
{
   p_one.Set_X(two_x_);
   p_one.Set_Y(two_y_);

   s_one_two = sqrt(pow(p_one.Get_X() - two_x_, 2) + pow(p_one.Get_Y() - two_y_, 2));
   s_two_three = sqrt(pow(two_x_ - p_three.Get_X(), 2) + pow(two_y_ - p_three.Get_Y(), 2));
}

void Triangle::Set_P_Three(double three_x_, double three_y_)
{
   p_one.Set_X(three_x_);
   p_one.Set_Y(three_y_);

   s_two_three = sqrt(pow(p_two.Get_X() - three_x_, 2) + pow(p_two.Get_Y() - three_y_, 2));
   s_three_one = sqrt(pow(three_x_ - p_one.Get_X(), 2) + pow(three_y_ - p_one.Get_Y(), 2));
}

int Triangle::Get_Count()
{
   return count;
}

void Triangle::Set_Count(int count_)
{
   count = count_;
}

void Triangle::Print_Triangle()
{
   printf("Name: %s\n", name);
   printf("Coordinates:");
   p_one.Print_Points();
   p_two.Print_Points();
   p_three.Print_Points();
   printf("\n");
   printf("Sides: %lf %lf %lf\n", s_one_two, s_two_three, s_three_one);
}

double Triangle::Get_Area_of_Triangle()
{
   double p = (s_one_two + s_two_three + s_three_one) / 2;

   double area = sqrt(p * (p - s_one_two) * (p - s_two_three) * (p - s_three_one));

   return area;
}

double Triangle::Get_Area_of_Triangle(Point p1_, Point p2_, Point p3_)
{
   double s_one_two = sqrt(pow(p1_.Get_X() - p2_.Get_X(), 2) + pow(p1_.Get_Y() - p2_.Get_Y(), 2));
   double s_two_three = sqrt(pow(p2_.Get_X() - p3_.Get_X(), 2) + pow(p2_.Get_Y() - p3_.Get_Y(), 2));
   double s_three_one = sqrt(pow(p3_.Get_X() - p1_.Get_X(), 2) + pow(p3_.Get_Y() - p1_.Get_Y(), 2));

   double p = (s_one_two + s_two_three + s_three_one) / 2;

   double area = sqrt(p * (p - s_one_two) * (p - s_two_three) * (p - s_three_one));

   return area;
}

//Угол от точки один в радианах
double Triangle::Get_Angle_One_of_Triangle()
{
   return acos((pow(s_one_two, 2) + pow(s_three_one, 2) - pow(s_two_three, 2)) / (2 * s_one_two * s_three_one));
}

//Угол от точки два в радианах
double Triangle::Get_Angle_Two_of_Triangle()
{
   return acos((pow(s_one_two, 2) + pow(s_two_three, 2) - pow(s_three_one, 2)) / (2 * s_one_two * s_two_three));
}

//Угол от точки три в радианах
double Triangle::Get_Angle_Three_of_Triangle()
{
   return acos((pow(s_two_three, 2) + pow(s_three_one, 2) - pow(s_one_two, 2)) / (2 * s_two_three * s_three_one));
}

void Triangle::Move_Triangle(double x_, double y_)
{
   p_one(p_one.Get_X() + x_, p_one.Get_Y() + y_);
   p_two(p_two.Get_X() + x_, p_two.Get_Y() + y_);
   p_three(p_one.Get_X() + x_, p_three.Get_Y() + y_);
}

bool Triangle::Triangle_Includes_Point(Point point_)
{
   double one_side = ((p_one.Get_X() - point_.Get_X()) * (p_two.Get_Y() - p_one.Get_Y()) - (p_one.Get_Y() - point_.Get_Y()) * (p_two.Get_X() - p_one.Get_X()));
   double two_side = ((p_two.Get_X() - point_.Get_X()) * (p_three.Get_Y() - p_two.Get_Y()) - (p_two.Get_Y() - point_.Get_Y()) * (p_three.Get_X() - p_two.Get_X()));
   double three_side = ((p_three.Get_X() - point_.Get_X()) * (p_one.Get_Y() - p_three.Get_Y()) - (p_three.Get_Y() - point_.Get_Y()) * (p_one.Get_X() - p_three.Get_X()));

   one_side = (one_side > 0) - (one_side < 0);
   two_side = (two_side > 0) - (two_side < 0);
   three_side = (three_side > 0) - (three_side < 0);

   if (one_side + two_side + three_side == 3 || one_side + two_side + three_side == -3) // Нормальный треугольник
      return true;

   if (one_side + two_side + three_side == 2 || one_side + two_side + three_side == -2) // Треугольник сторона которого лежит на изначальном
      return true;

   if ((one_side == two_side && one_side == 0) || (one_side == three_side && one_side == 0) || (two_side == three_side && two_side == 0)) // Не очень треугольник
      return true;

   return false;
}


bool Triangle::Triangle_Includes_Point_Using_Area(Point point_)
{
   double area1 = Get_Area_of_Triangle(p_one, p_two, point_);
   double area2 = Get_Area_of_Triangle(p_one, p_three, point_);
   double area3 = Get_Area_of_Triangle(p_two, p_three, point_);

   if (area1 + area2 + area3 == Get_Area_of_Triangle())
      return true;
   else
      return false;
}


bool Triangle::Triangle_Includes_Triangle(Triangle other_)
{
   if ((*this).Get_Area_of_Triangle() < other_.Get_Area_of_Triangle())
      return false;
   else if (Triangle_Includes_Point(other_.Get_P_One()) && Triangle_Includes_Point(other_.Get_P_Two()) && Triangle_Includes_Point(other_.Get_P_Three()))
      return true;
   else
      return false;
}


