#include <stdio.h>
#include <stdlib.h>
#include "Stones.h"

int fromChartoInt(char* a)
{
   int b = 0;
   int rank = 10;
   for (int i = 0; a[i] != '\0'; i++)
   {
      if (a[i] >= '0' && a[i] <= '9')
      b = b * rank + a[i] - '0';
   }
   return b;
}

struct Heap_of_the_stones
{
   int Number_of_stones;
   char* Color_of_stones;
   int Operation_with_stones_plus;
   int Operation_with_stones_multy;
};

char* CombitateColor(HeapS* a, HeapS* b)
{
   if (a->Color_of_stones == NULL || b->Color_of_stones == NULL)
   {
      if (a->Color_of_stones != NULL)
         return a->Color_of_stones;
      if (b->Color_of_stones != NULL)
         return b->Color_of_stones;
      return NULL;
   }
   int flag = 0;
   for (int i = 0; a->Color_of_stones[i] != 0 && b->Color_of_stones[i] != 0; i++)
   {
      if (a->Color_of_stones[i] != b->Color_of_stones[i])
         return "black";
   }
   return a->Color_of_stones;
}

int Make_color(HeapS* heap_, char* color_)
{
   int color = fromChartoInt(color_);
   switch (color)
   {
   case(0):
      heap_->Color_of_stones = "black";
      return 0;
   case(255255255):
      heap_->Color_of_stones = "white";
      return 0;
   case(128128128):
      heap_->Color_of_stones = "gray";
      return 0;
   case(128000128):
      heap_->Color_of_stones = "purple";
      return 0;
   case(255000000):
      heap_->Color_of_stones = "red";
      return 0;
   case(255255000):
      heap_->Color_of_stones = "yellow";
      return 0;
   case(128000):
      heap_->Color_of_stones = "green";
      return 0;
   case(255):
      heap_->Color_of_stones = "blue";
      return 0;
   default:
      printf("I dont know what is the color");
      return NULL;
   }
   
}

void Operation(HeapS* heap_, char operator)
{
   switch (operator)
   {
   case(74):
      heap_->Number_of_stones = heap_->Number_of_stones * heap_->Operation_with_stones_multy;
      if (heap_->Number_of_stones < 0)
         heap_->Number_of_stones = 0;
      break;
   case(75):
      heap_->Number_of_stones = heap_->Number_of_stones + heap_->Operation_with_stones_plus;
      if (heap_->Number_of_stones < 0)
         heap_->Number_of_stones = 0;
   default:
      printf("I dont know what is the operator");
   }
}

int Itisthatcolor(HeapS* heap_, char* color_)
{
   char* color = heap_->Color_of_stones;

   for (int i = 0; color[i] != '\0' || color_[i] != '\0'; i++)
      if (color[i] != color_[i])
         return 1;
   return 0;
}

HeapS* CompinateHeap(HeapS* heap1_, HeapS* heap2_)
{
   HeapS* heap3 = (HeapS*)malloc(sizeof(HeapS));
   if (heap3 == NULL)
      return NULL;

   heap3->Number_of_stones = heap1_->Number_of_stones + heap2_->Number_of_stones;
   heap3->Color_of_stones = CombitateColor(heap1_, heap2_);
   heap3->Operation_with_stones_plus = (heap1_->Operation_with_stones_plus + heap2_->Operation_with_stones_plus) / 2;
   heap3->Operation_with_stones_multy = (heap1_->Operation_with_stones_multy + heap2_->Operation_with_stones_multy) / 2;

   free(heap1_);
   free(heap2_);
   return heap3;
}

struct Data_Base
{
   HeapS** Heap;
   size_t size;
}; 

void Make_Element(Data_Base* a, unsigned int number_, int operation1_, int operation2_)
{
   HeapS* heap = (HeapS*)malloc(sizeof(HeapS));
   if (heap == NULL)
      return NULL;

   heap->Number_of_stones = number_;
   heap->Operation_with_stones_plus = operation1_;
   heap->Operation_with_stones_multy = operation2_;
   if (Make_color == NULL)
      heap->Color_of_stones = NULL;

   a->Heap[a->size] = heap;
   a->size++;
}

int Find_Element_number(Data_Base* a, int b)
{
   for(int i = 0; i < a->size; i++)
      if (a->Heap[i]->Number_of_stones == b)
      {
         return i;
      }
   return NULL;
}

int Find_Element_color(Data_Base* a, char* b)
{
   for (int i = 0; i < a->size; i++)
      if (a->Heap[i]->Color_of_stones[0] == b[0])
      {
         int flag = 0;
         for (int j = 0; b[j] != '\0' && a->Heap[i]->Color_of_stones[j] != '\0'; j++)
         {
            if (a->Heap[i]->Color_of_stones[j] != b[j])
               flag = 1;
         }
         if (flag == 0)
            return i;
      }
   return NULL;
}

void Del_heap(HeapS* a)
{
   free(a->Number_of_stones);
   free(a->Operation_with_stones_plus);
   free(a->Operation_with_stones_multy);
   free(a->Color_of_stones);
   free(a);
}

void Del_Element(Data_Base* a, void* needdelete, int typedelete)
{
   int number_element;
   switch (typedelete)
   {
   case(0):
      for (int i = 0; i < a->size; i++)
      {
         if (Find_Element_number(a, (int)needdelete) != NULL)
            number_element = Find_Element_number(a, (int)needdelete);
         else
            return;
         Del_heap(a->Heap[number_element]);
         a->size--;
         Move_Elements(a, number_element);
      }
      break;
   case(1):
      for (int i = 0; i < a->size; i++)
      {
         if (Find_Element_color(a, (char*)needdelete) != NULL)
            number_element = Find_Element_color(a, (char*)needdelete);
         else
            return;
         Del_heap(a->Heap[number_element]);
         a->size--;
         Move_Elements(a, number_element);
      }
      break;
   default:
      printf("Wrong data");
      return -1;
   }
}

void Move_Elements(Data_Base* a, int number_element)
{
   for (int i = number_element; i < (int)a->size; i++)
   {
      a->Heap[i] = a->Heap[i + 1];
   }
}

void PrintDB(Data_Base* a)
{
   for (int i = 0; i < a->size; i++)
   {
      printf("%d   %d \n %s \n %d \n %d", i, a->Heap[i]->Number_of_stones, 
         a->Heap[i]->Color_of_stones, a->Heap[i]->Operation_with_stones_plus, a->Heap[i]->Operation_with_stones_multy);
   }
}

Data_Base* CreateDB()
{
   Data_Base* Base = (Data_Base*)malloc(sizeof(Data_Base));

   if (Base == NULL)
      return -1;

   Base->Heap = malloc(20 * sizeof(HeapS));
   if (Base->Heap == NULL)
      return -1;

   Base->size = 0;
   return Base;
}

void SortDB(Data_Base* a)
{
   quickSort(a, 0, a->size);
}

void swap(HeapS* a, HeapS* b) 
{
   HeapS temp = *a;
   *a = *b;
   *b = temp;
}

int partition(HeapS* arr, int low, int high) 
{
   HeapS pivot = arr[high];
   int i = low - 1;

   for (int j = low; j <= high - 1; j++) {
      if (Min(arr[j], pivot) > 0) {
         i++;
         swap(&arr[i], &arr[j]);
      }
   }
   swap(&arr[i + 1], &arr[high]);
   return (i + 1);
}

void quickSort(Data_Base* arr, int low, int high) 
{
   if (low < high) {
      int p = partition(arr, low, high);

      quickSort(arr, low, p - 1);
      quickSort(arr, p + 1, high);
   }
}

int Min(HeapS a, HeapS b)
{
   return a.Number_of_stones - b.Number_of_stones;
}

void DelDB(Data_Base* a)
{
   free(a->Heap);
   free(a);
}