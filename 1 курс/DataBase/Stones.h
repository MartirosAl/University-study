#pragma once

typedef struct Heap_of_the_stones HeapS;

typedef struct Data_Base Data_Base;

int fromChartoInt(char* a);

char* CombitateColor(HeapS* a, HeapS* b);

int Make_color(HeapS* heap_, char* color_);

void Operation(HeapS* heap_, char operator);

int Itisthatcolor(HeapS* heap_, char* color_);

HeapS* CompinateHeap(HeapS* heap1_, HeapS* heap2_);

void Make_Element(Data_Base* a, unsigned int number_, int operation1_, int operation2_);

int Find_Element_number(Data_Base* a, int b);

int Find_Element_color(Data_Base* a, char* b);

void Del_heap(HeapS* a);

void Del_Element(Data_Base* a, void* needdelete, int typedelete);

Data_Base* CreateDB();

void SortDB(Data_Base* a);

void swap(HeapS* a, HeapS* b);

int partition(HeapS* arr, int low, int high);

void quickSort(Data_Base* arr, int low, int high);

int Min(HeapS a, HeapS b);

void PrintDB(Data_Base* a);

void DelDB(Data_Base* a);
