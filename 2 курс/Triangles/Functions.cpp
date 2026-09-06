#include "Functions.h"

void Print_Triangles(Triangle* triangles_, int size_)
{
   printf("+-------------------------------------------------------------------------------------------------------\n");
   for (size_t i = 0; i < size_; i++)
   {
      triangles_[i].Print_Triangle();
      printf("+-------------------------------------------------------------------------------------------------------\n");
   }
}

int Expansion(Triangle*& arr_, size_t& size_)
{

   Triangle* temp = new Triangle[size_];

   for (size_t i = 0; i < size_; ++i)
   {
      temp[i] = arr_[i];
   }
   delete[] arr_;

   arr_->Set_Count(1);

   arr_ = new Triangle[size_+1];

   for (size_t i = 0; i < size_; ++i)
   {
      arr_[i] = temp[i];
   }

   return 0;
}

Triangle* Find_Max(Triangle* arr_, size_t size_)
{
   Triangle* max = arr_;
   for (size_t i = 0; i < size_; i++)
   {
      arr_++;
      if (max->Get_Area_of_Triangle() < arr_->Get_Area_of_Triangle())
         max = arr_;
   }
   return max;
}

void Menu()
{
   printf("1. Add triangle\n");
   printf("2. Get Area\n");
   printf("3. Edit triangle\n");
   printf("4. Print triangles\n");
   printf("5. Move triangle\n");
   printf("6. Does a triangle include another triangle\n");
   printf("7. Find the maximum triangle from the array by area\n");
}

bool Is_Triangle(double one_x_, double one_y_, double two_x_, double two_y_, double three_x_, double three_y_)
{
   double side_one = sqrt(pow(one_x_ - two_x_, 2) + pow(one_y_ - two_y_, 2)); //0-0 = 0

   double side_two = sqrt(pow(two_x_ - three_x_, 2) + pow(two_y_ - three_y_, 2));//5

   double side_three = sqrt(pow(three_x_ - one_x_, 2) + pow(three_y_ - one_y_, 2));//4


   if (side_one + side_two > side_three && side_one + side_three > side_two && side_two + side_three > side_one)
      return true;

   return false;
}


