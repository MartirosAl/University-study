#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"

int main()
{
   BinTreeNode* Tree = NULL;
   int ñhoice = 0;
   int data;
   while (1)
   {
      printf("1. Find\n");//1
      printf("2. Insert\n");
      printf("3. Remove\n");
      printf("4. Print leaves\n");//6
      printf("5. Sum\n");//2
      printf("6. Max\n");//3
      printf("7. Min\n");//4
      printf("8. Number of elements\n");//5
      printf("9. Depth-sensitive printing\n");//7
      printf("10. Depth of the elements\n");//8
      printf("11. Number of elements with same depth\n");//9
      printf("12. Sorting array\n");//10
      scanf_s("%d", &ñhoice);
      switch (ñhoice)
      {
      case(1):
         printf("Enter data: ");
         scanf_s("%d", &data);
         printf("\n%d\n\n", Find(Tree, data) != NULL);;
         break;
      case(2):
         printf("Enter data: ");
         scanf_s("%d", &data);
         BinTreeNode* NewTree = (BinTreeNode*)malloc(sizeof(BinTreeNode));
         NewTree->data = data;
         NewTree->left = NULL;
         NewTree->right = NULL;
         NewTree->parent = NULL;
         Insert(&Tree, NewTree);
         printf("\nDone\n\n");
         break;
      case(3):
         printf("Enter data: ");
         scanf_s("%d", &data);
         Remove(&Tree, data);
         printf("\nDone\n\n");
         break;
      case(4):
         Print_leaves(&Tree);
         printf("\n\n");
         break;
      case(5):
         printf("\n%d\n\n", Sum(&Tree, 0));
         break;
      case(6):
         printf("\n%d\n\n", Max(&Tree));
         break;
      case(7):
         printf("\n%d\n\n", Min(&Tree));
         break;
      case(8):
         printf("Element: ");
         scanf_s("%d", &data);
         printf("\n%d\n\n", Number_of_elements(&Tree, data));
         break;
      case(9):
         printf("\n");
         Depth_sensitive_printing(&Tree, 0);
         printf("\n");
         break;
      case(10):
         printf("Element: ");
         scanf_s("%d", &data);
         printf("\n%d\n\n", Depth_elements(&Tree, data, 0));
         break;
      case(11):
         printf("Depth (starts with 0): ");
         scanf_s("%d", &data);
         printf("\n%d\n\n", Same_depth(&Tree, data, 0, 0));
         break;
      case(12):
         printf("\n%d\n\n", Depth_tree(&Tree));
         break;      
      default:
         return 0;
      }
   }
}