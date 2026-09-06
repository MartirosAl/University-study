#pragma once

#include <cmath>
#include <time.h>
#include <numbers>
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Fib_Heap_Vertex
{
    int key;
    Fib_Heap_Vertex* parent;
    Fib_Heap_Vertex* child;
    Fib_Heap_Vertex* left;
    Fib_Heap_Vertex* right;
    int degree;
    bool mark; // mark[x] = true <=> x потерял сына после того, как в последний раз стал чьим-то сыном

    Fib_Heap_Vertex(int key_)
    {
        key = key_;
        parent = nullptr;
        child = nullptr;
        left = this;
        right = this;
        degree = 0;
        mark = false;
    }

    Fib_Heap_Vertex(int key_, Fib_Heap_Vertex* parent_, Fib_Heap_Vertex* child_, Fib_Heap_Vertex* left_, Fib_Heap_Vertex* right_, int degree_, bool mark_)
    {
        key = key_;
        parent = parent_;
        child = child_;
        left = left_;
        right = right_;
        degree = degree_;
        mark = mark_;
    }

    ~Fib_Heap_Vertex()
    {
        delete child;

        if (right != this && right != nullptr)
        {
            left->right = nullptr;
            delete right;
        }
    }

    friend ostream& operator<<(ostream& os, const Fib_Heap_Vertex* vertex)
    {
        Print_tree(os, vertex, 0);

        return os;
    }

    static ostream& Print_tree(std::ostream& os, const Fib_Heap_Vertex*& vertex, int depth)
    {
        for (int i = 0; i < depth; i++)
            os << "|   ";
        os << "|-- key = " << vertex->key << " (deg = " << vertex->degree << " , mark = " << vertex->mark << " )" << endl;

        const Fib_Heap_Vertex* cur_child = vertex->child;
        depth++;
        for (int i = 0; i < vertex->degree; i++)
        {
            Print_tree(os, cur_child, depth);
            cur_child = cur_child->right;
        }

        return os;
    }
};