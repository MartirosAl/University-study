#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <math.h>
#include "Functions.h"
#define PI 3.14159265358979323846 //20 знаков после запятой
#define max_size 100

int main()
{

   SetConsoleOutputCP(1251); //для вывода
   SetConsoleCP(1251); //из Windows.h для ввода

   Triangle* triangles = nullptr;
   size_t size = 0;

   while (1)
   {
      system("cls");
      int choice;
      int choice_triangle;
      int choice_triangle2;
      double x1, x2, x3, y1, y2, y3;
      printf("What do you need?\n");

      Menu();
      printf("> ");
      if (!scanf("%d", &choice))
         return 4;

      system("cls");



      switch (choice)
      {
      case 1:
         printf("Enter the coordinates of the points: ");
         if (!scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3))
            return 4;
         system("cls");
         if (!Is_Triangle(x1, y1, x2, y2, x3, y3))
         {
            printf("This is not triangle\n");
            system("pause");
            continue;
         }

         Expansion(triangles, size);
         triangles[size].Set_Triangle(x1, y1, x2, y2, x3, y3);
         size++;
         
         printf("Done\n");
         system("pause");
         continue;
      case 2:
         printf("Choice triangle:");
         if (!scanf("%d", &choice_triangle))
            return 4;
         system("cls");
         if (!triangles)
            return 3;
         printf("%lf", triangles[choice_triangle].Get_Area_of_Triangle());

         system("pause");
         continue;

      case 3:
         printf("Choice triangle:");
         if (!scanf("%d", &choice_triangle))
            return 4;

         system("cls");

         printf("Enter the coordinates of the points: ");
         if (!scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3))
            return 4;
         system("cls");
         triangles[choice_triangle - 1].Set_Triangle(x1, y1, x2, y2, x3, y3);

         printf("Done");
         system("pause");
         continue;

      case 4:
         Print_Triangles(triangles, size);

         system("pause");
         continue;

      case 5:
         printf("Choice triangle:");
         if (!scanf("%d", &choice_triangle))
            return 4;

         system("cls");
         printf("Enter the vector of the direction of movement of the triangle relative to 0: ");
         if (!scanf("%lf %lf", &x1, &y1))
            return 4;
         system("cls");
         triangles[choice_triangle - 1].Move_Triangle(x1, y1);

         printf("Done");
         system("pause");
         continue;

      case 6:
         Print_Triangles(triangles, size);
         printf("Choice first triangle:");
         if (!scanf("%d", &choice_triangle))
            return 4;
         system("cls");
         printf("Choice second triangle:");
         if (!scanf("%d", &choice_triangle2))
            return 4;
         system("cls");
         printf("%s", triangles[choice_triangle - 1].Triangle_Includes_Triangle(triangles[choice_triangle2 - 1]) ? "Yes\n" : "No\n");

         system("pause");
         continue;

      case 7:
         Find_Max(triangles, size)->Print_Triangle();

         system("pause");
         continue;

      default:
         int choise_def;
         printf("Do you want to exit?\n> ");
         printf("1. No\n");
         printf("Any one. Yes\n");
         if (!scanf("%d", &choise_def))
            return 4;
         if (choise_def != 1)
            return 0;
         continue;
      }
   }
   return 0;
}


