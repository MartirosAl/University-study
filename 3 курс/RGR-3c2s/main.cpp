//Вариант 15. Фибоначчиевые кучи. Вставка, объединение, удаление с мин ключом, удаление произвольной, уменьшение ключа
//Считаем, что все вершины, которые подаются в функции, находятся в одной куче. Иначе нужно будет проверять все вершины находятся ли они в куче.

#include <iostream>
#include <cmath>
#include <time.h>
#include <numbers>
#include "Fib_Heap.h"
using namespace std;

int main()
{
    Fib_Heap Heap;

    //Heap.Fib_Heap_Insert(0);
    //Heap.Fib_Heap_Insert(3);
    //Heap.Fib_Heap_Insert(52);
    //Heap.Fib_Heap_Insert(18);
    //Heap.Fib_Heap_Insert(39);
    //Heap.Fib_Heap_Insert(38);
    //Heap.Fib_Heap_Insert(42);
    //Heap.Fib_Heap_Insert(40);
    //Heap.Fib_Heap_Insert(41);
    //cout << Heap << endl;

    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;


    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;
    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;
    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;
    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;
    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;
    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;
    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;
    //Heap.Fib_Heap_Delete_Min();
    //cout << Heap << endl;

    //Fib_Heap Heap2;
    //Heap2.Fib_Heap_Insert(-1);
    //Heap2.Fib_Heap_Insert(-2);
    //Heap2.Fib_Heap_Insert(4);
    //Heap2.Fib_Heap_Insert(5);
    //Heap2.Fib_Heap_Insert(6);
    //cout << Heap2 << endl;
    //Heap2.Fib_Heap_Delete_Min();
    //cout << Heap2 << endl;
    //Heap.Fib_Heap_Union(&Heap2);

    //Heap.Fib_Heap_Decrease_Key(Heap.Fib_Heap_Min()->child->right, 1);

    //Heap.Fib_Heap_Delete(Heap.Fib_Heap_Min()->child->right->child);

    // Построить все поддеревья
    Heap.Fib_Heap_Insert(34); Heap.Fib_Heap_Insert(10); Heap.Fib_Heap_Insert(-1); Heap.Fib_Heap_Delete_Min();
    Heap.Fib_Heap_Insert(43); Heap.Fib_Heap_Insert(30); Heap.Fib_Heap_Insert(-2); Heap.Fib_Heap_Delete_Min();
    Heap.Fib_Heap_Insert(29); Heap.Fib_Heap_Insert(11); Heap.Fib_Heap_Insert(-3); Heap.Fib_Heap_Delete_Min();

        // Вставить корни и детей
    Heap.Fib_Heap_Insert(26); Heap.Fib_Heap_Insert(9);
        Heap.Fib_Heap_Insert(35); Heap.Fib_Heap_Insert(3);
        Heap.Fib_Heap_Insert(28); Heap.Fib_Heap_Insert(7);
        Heap.Fib_Heap_Insert(36); Heap.Fib_Heap_Insert(21);
        Heap.Fib_Heap_Insert(13); Heap.Fib_Heap_Insert(23);

        // Одна консолидация для всех связей
        Heap.Fib_Heap_Insert(-100); Heap.Fib_Heap_Delete_Min();

        // 3 стал минимальным корнем, 9 и 7 — его дети
        // Это ближе всего к возможному состоянию
        
    cout << Heap << endl;
}
