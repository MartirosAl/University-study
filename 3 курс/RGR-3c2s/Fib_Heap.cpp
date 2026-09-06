#include "Fib_Heap.h"

Fib_Heap* Fib_Heap::Fib_Heap_Insert(Fib_Heap_Vertex* x)
{
    if (min == nullptr)
    {
        min = x;
    }
    else
    {
        Pull_out_vertex_with_child(x);
        Place_vertex_right_to_min(x);
    }

    x->mark = false;
    number_vertices++;
    number_trees++;

    return this;
}

Fib_Heap* Fib_Heap::Fib_Heap_Insert(int x)
{
    Fib_Heap_Vertex* new_vertex = new Fib_Heap_Vertex(x);

    if (min == nullptr)
    {
        min = new_vertex;
    }
    else
    {
        Place_vertex_right_to_min(new_vertex);

        if (new_vertex->key < min->key)
        {
            min = new_vertex;
        }
    }

    number_vertices++;
    number_trees++;

    return this;
}

Fib_Heap_Vertex* Fib_Heap::Fib_Heap_Min()
{
    return min;
}

Fib_Heap* Fib_Heap::Fib_Heap_Union(Fib_Heap* H_2)
{
    min->right->left = H_2->min->left;
    H_2->min->left->right = min->right;
    min->right = H_2->min;
    H_2->min->left = min;

    if (min->key > H_2->min->key)
        min = H_2->min;

    number_vertices += H_2->number_vertices;
    number_trees += H_2->number_trees;
    number_marks += H_2->number_marks;

    H_2->min = nullptr;

    return this;
}

Fib_Heap* Fib_Heap::Fib_Heap_Delete_Min()
{
    if (min == nullptr)
        return this;

    Fib_Heap_Vertex* child_min = min->child;
    int min_degree = min->degree;
    for (int i = 0; i < min_degree; i++)
    {
        min->child = child_min->right;
        Fib_Heap_Insert(child_min);
        number_vertices--;
        number_trees--;
        child_min = min->child;
    }

    if (min == min->right)
    {
        min = nullptr;
        number_vertices = 0;
        number_trees = 0;
        return this;
    }
    min = min->right;

    Delete_vertex_without_child(min->left);

    Consolidation();

    return this;
}

Fib_Heap* Fib_Heap::Fib_Heap_Decrease_Key(Fib_Heap_Vertex* x, int k)
{
    if (k > x->key)
        abort();

    x->key = k;
    Fib_Heap_Vertex* y = x->parent;

    if (y != nullptr && x->key < y->key)
    {
        Cut(x, y);
        Cascading_Сut(y);
    }

    if (x->key < min->key)
    {
        min = x;
    }

    return this;
}

Fib_Heap* Fib_Heap::Fib_Heap_Delete(Fib_Heap_Vertex* x)
{
    Fib_Heap_Decrease_Key(x, INT_MIN);
    Fib_Heap_Delete_Min(); 
    return this;
}

Fib_Heap* Fib_Heap::Consolidation()
{
    int max_degree = round(log(number_vertices) / log(numbers::phi)) + 1;

    Fib_Heap_Vertex** A = new Fib_Heap_Vertex*[max_degree];
    for (int i = 0; i < max_degree; i++)
        A[i] = nullptr;

    Fib_Heap_Vertex* cur_root = min;
    bool flag_end = false;
    while(!flag_end)
    {
        Fib_Heap_Vertex* x = cur_root;
        int d = cur_root->degree;
        cur_root = cur_root->right;
        while (A[d] != nullptr)
        {
            Fib_Heap_Vertex* y = A[d];
            if (x->key > y->key)
            {
                swap(x, y);
            }

            Fib_Heap_Link(x, y);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;

        for (int i = 0; i < max_degree; i++)
        {
            if (cur_root == A[i] || cur_root->parent != nullptr)
                flag_end = true;
        }

        //for (int i = 0; i < max_degree; i++)
        //{
        //    cout << i << ": ";
        //    if (A[i] != nullptr)
        //        cout << A[i]->key;
        //    cout << endl;
        //}
        //cout << endl;
        
    }

    min = nullptr;

    number_trees = 0;

    for (int i = 0; i < max_degree; i++)
    {
        if (A[i] != nullptr)
        {
            Place_vertex_right_to_min(A[i]);
            
            if (A[i]->key < min->key)
                min = A[i];

            number_trees++;
        }
    }

    return this;
}

Fib_Heap* Fib_Heap::Fib_Heap_Link(Fib_Heap_Vertex* x, Fib_Heap_Vertex* y)
{
    Pull_out_vertex_with_child(y);

    y->parent = x;
    if (x->child == nullptr)
        x->child = y;

    Place_vertex_right_to(y, x->child);

    return this;
}

Fib_Heap* Fib_Heap::Cut(Fib_Heap_Vertex* x, Fib_Heap_Vertex* y)
{
    Fib_Heap_Vertex* p = x->parent;
    bool flag_mark = p->mark;
    Pull_out_vertex_with_child(x);
    Place_vertex_right_to_min(x);
    p->mark = flag_mark;
    return this;
}

Fib_Heap* Fib_Heap::Cut(Fib_Heap_Vertex* x)
{
    Fib_Heap_Vertex* p = x->parent;
    bool flag_mark = p->mark;
    Pull_out_vertex_with_child(x);
    Place_vertex_right_to_min(x);
    p->mark = flag_mark;
    return this;
}

Fib_Heap* Fib_Heap::Cascading_Сut(Fib_Heap_Vertex* y)
{
    Fib_Heap_Vertex* z = y->parent;
    if (z != nullptr)
    {
        if (y->mark == false && y->parent != nullptr) //Фактически y->parent != nullptr весегда выполняется тк метод запускается в случае наличия отца
            y->mark = true;
        else
        {
            Cut(y, z);
            Cascading_Сut(z);
        }
    }
    return this;
}

Fib_Heap_Vertex* Fib_Heap::Pull_out_vertex_with_child(Fib_Heap_Vertex* x)
{
    if (x == min)
    {
        if (min->right == min)
            min = nullptr;
        else
            min = min->right;
    }

    if (x->parent != nullptr)
    {
        if (x->parent->child == x)
            if (x->right == x)
                x->parent->child = nullptr;
            else
                x->parent->child = x->right;

        x->parent->degree--;
        if (x->parent->parent != nullptr)
        {
            x->parent->mark = true;
            number_marks++;
        }
        x->parent = nullptr;
    }

    x->right->left = x->left;
    x->left->right = x->right;
    x->right = x;
    x->left = x;

    return x;
}

Fib_Heap* Fib_Heap::Place_vertex_right_to_min(Fib_Heap_Vertex* x)
{
    if (min == nullptr)
    {
        min = x;
    }

    x->left = min;
    x->right = min->right;
    min->right->left = x;
    min->right = x;
    
    x->mark = false;

    return this;
}

Fib_Heap* Fib_Heap::Place_vertex_right_to(Fib_Heap_Vertex* vertex, Fib_Heap_Vertex* vertex_right_to)
{
    vertex->left = vertex_right_to;
    vertex->right = vertex_right_to->right;
    vertex_right_to->right->left = vertex;
    vertex_right_to->right = vertex;

    if (vertex_right_to->parent != nullptr)
        vertex_right_to->parent->degree++;

    return this;
}

Fib_Heap* Fib_Heap::Delete_vertex_without_child(Fib_Heap_Vertex* x)
{
    Pull_out_vertex_with_child(x);

    if (x->mark == true)
    {
        number_marks--;
        x->mark = false;
    }

    number_vertices--;

    delete x;

    return this;
}




