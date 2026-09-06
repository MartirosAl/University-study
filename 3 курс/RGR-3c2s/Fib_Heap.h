#pragma once
#include "Fib_Heap_Vertex.h"

class Fib_Heap
{

protected:
    Fib_Heap_Vertex* min;
    int number_vertices;
    int number_trees;
    int number_marks;

public:

    Fib_Heap()
    {
        min = nullptr;
        number_vertices = 0;
        number_trees = 0;
        number_marks = 0;
    }

    ~Fib_Heap()
    {
        delete min;
    }

    int Give_n() const { return number_vertices; };
    int Give_t() const { return number_trees; };
    int Give_m() const { return number_marks; };


    //Время O(1), Ам. ст. O(1)
    Fib_Heap* Fib_Heap_Insert(Fib_Heap_Vertex* x);
    Fib_Heap* Fib_Heap_Insert(int x);

    //Время O(1), Ам. ст. O(1)
    Fib_Heap_Vertex* Fib_Heap_Min();

    //Время O(1), Ам. ст. O(1)
    Fib_Heap* Fib_Heap_Union(Fib_Heap* H_2);

    //Время O(D(n) + number_trees) <= C_1(D(n) + number_trees), Ам. ст. O(D(n)), D(n) - максимальная степень вершины в куче с n ключами
    Fib_Heap* Fib_Heap_Delete_Min();

    //Время O(r) <= C2*r, Ам. ст <= (C2-c)r + 4c
    Fib_Heap* Fib_Heap_Decrease_Key(Fib_Heap_Vertex* x, int k);

    //Время O(D(n))
    Fib_Heap* Fib_Heap_Delete(Fib_Heap_Vertex* x);

    friend std::ostream& operator<<(std::ostream& os, const Fib_Heap& Heap)
    {
        os << "n[H] = " << Heap.Give_n() << ", t[H] = " << Heap.Give_t() << ", m[H] = " << Heap.Give_m() << endl;
        Fib_Heap_Vertex* cur_root = Heap.min;
        if (cur_root != nullptr)
        {
            while (true)
            {
                os << cur_root;
                cur_root = cur_root->right;
                if (cur_root == Heap.min)
                    break;
            }
        }

        return os;
    }

private:

    Fib_Heap* Consolidation();

    Fib_Heap* Fib_Heap_Link(Fib_Heap_Vertex* x, Fib_Heap_Vertex* y);

    Fib_Heap* Cut(Fib_Heap_Vertex* x, Fib_Heap_Vertex* y);
    Fib_Heap* Cut(Fib_Heap_Vertex* x);

    Fib_Heap* Cascading_Сut(Fib_Heap_Vertex* y);

    Fib_Heap_Vertex* Pull_out_vertex_with_child(Fib_Heap_Vertex* x);

    Fib_Heap* Place_vertex_right_to_min(Fib_Heap_Vertex* x);
    Fib_Heap* Place_vertex_right_to(Fib_Heap_Vertex* vertex, Fib_Heap_Vertex* vertex_right_to);
    
    Fib_Heap* Delete_vertex_without_child(Fib_Heap_Vertex* x);

};

