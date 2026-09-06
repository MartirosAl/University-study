#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"

/*
Операции поиска, вставки и удаления в двоичном дереве
поиска высоты h могут быть выполнены за время O(h).
Доказательство
• На каждом шаге алгоритм переходит от отца к сыну.
• Глубина текущей вершины увеличивается на 1.
• Число шагов не превосходит высоты дерева.
*/
BinTreeNode* Find(BinTreeNode* tree_, int data_)
{
   if (tree_ == NULL)
      return NULL;
   if (data_ == tree_->data)
      return tree_;
   if (data_ < tree_->data)
      return Find(tree_->left, data_);
   else
      return Find(tree_->right, data_);
}

/*
Если двоичное дерево поиска содержит n вершин, то
операции поиска, вставки и удаления могут быть выполнены
за время O(n), причём эта оценка достигается.
Доказательство
• Если дерево содержит n вершин, то его высота не
превосходит n.
• Если дерево содержит единственную ветвь
1 → 2 → · · · → n, то операции поиска n, удаления n и
вставки n + 1 требуют времени Θ(n). 
*/
void Insert(BinTreeNode** tree_, BinTreeNode* node_)
{
   if (*tree_ == NULL)
      *tree_ = node_;
   else
   {
      node_->parent = *tree_;
      if (node_->data < (*tree_)->data)
         Insert(&(*tree_)->left, node_);
      else
         Insert(&(*tree_)->right, node_);
   }
}

/*
Пусть двоичное дерево поиска изначально пусто. Тогда n
операций поиска, вставки и удаления могут быть выполнены
за время O(n^2), причём эта оценка достигается.
Доказательство
• После каждой операции дерево содержит не более n
вершин.
• Каждая операция выполняется за время O(n).
• Общее время: O(n^2).
*/
void Remove(BinTreeNode** tree_, int data_)
{
   BinTreeNode* f = Find((*tree_), data_);

   if (f->parent == NULL)
   {
      if (f->left != NULL)
      {
         BinTreeNode* temp = f->left;
         while (temp->right != NULL)
         {
            temp = temp->right;
         }
         f->data = temp->data;
         Remove(&temp, temp->data);
         return;
      }
      if (f->right != NULL)
      {
         BinTreeNode* temp = f->right;
         while (temp->left != NULL)
         {
            temp = temp->left;
         }
         f->data = temp->data;
         Remove(&temp, temp->data);
         return;
      }
   }

   if (f->right == NULL && f->left == NULL)
   {
      if (f->parent != NULL)
      {
         if (f->data < f->parent->data)
            f->parent->left = NULL;
         else
            f->parent->right = NULL;
      }
      free(f);
      return;
      
   }
   if (f->right == NULL)
   {
      f->left->parent = f->parent;
      if (f->data < f->parent->data)
         f->parent->left = f->left;
      else
         f->parent->right = f->left;
   }
   else if (f->left == NULL)
   {
      f->right->parent = f->parent;
      if (f->data < f->parent->data)
         f->parent->left = f->right;
      else
         f->parent->right = f->right;
   }
   else
   {
      BinTreeNode* temp = f->left;
      while (temp->right != NULL)
      {
         temp = temp->right;
      }
      f->data = temp->data;
      Remove(&temp, temp->data);
      return;
   }
   free(f);
}

void Print(BinTreeNode** tree_)
{
   if (*tree_ != NULL) 
   {
      printf("%d ", (*tree_)->data);
      Print(&(*tree_)->left);
      Print(&(*tree_)->right);
   }
}

int Sum(BinTreeNode** tree_, int sum)
{
   if (*tree_ != NULL)
   {
      sum += (*tree_)->data;
      sum += Sum(&(*tree_)->left, 0);
      sum += Sum(&(*tree_)->right, 0);
      return sum;
   }
   return 0;
}

int Max(BinTreeNode** tree_) 
{
   if ((*tree_)->right != NULL)
      return Max(&(*tree_)->right);
   return (*tree_)->data;
}

int Min(BinTreeNode** tree_)
{
   if ((*tree_)->left != NULL)
      return Min(&(*tree_)->left);
   return (*tree_)->data;
}

int Number_of_elements(BinTreeNode** tree_, int data)
{
   BinTreeNode* f = Find((*tree_), data);
   
   if (f == NULL)
      return 0;
   int counter = 1;

   while (1)
   {
      f = Find(f->right, data);
      if (f != NULL)
         counter++;
      else 
         return counter;
   }
}

void Print_leaves(BinTreeNode** tree_)
{
   if (*tree_ != NULL) {
      if ((*tree_)->left == NULL && (*tree_)->right == NULL)
         printf("%d ", (*tree_)->data);
      Print_leaves(&(*tree_)->left);
      Print_leaves(&(*tree_)->right);
   }
}

void Depth_sensitive_printing(struct BinTreeNode** tree_, int data)
{
   if ((*tree_) == NULL) {
      return;
   }

   for (int i = 0; i < data; i++) {
      printf("  ");
   }
   printf("%d\n", (*tree_)->data);

   Depth_sensitive_printing(&(*tree_)->right, ++data);

   Depth_sensitive_printing(&(*tree_)->left, ++data);
}

int Depth_elements(struct BinTreeNode** tree_, int data, int data2)
{
   if ((*tree_) == NULL)
      return -1;
   if (data == (*tree_)->data)
   {
      return data2;
   }
      
   if (data < (*tree_)->data)
      return Depth_elements(&(*tree_)->left, data, data2 + 1);
   else
      return Depth_elements(&(*tree_)->right, data, data2 + 1);
}

int Same_depth(struct BinTreeNode** tree_, int data, int data2, int count)
{
   if ((*tree_) == NULL)
      return 0;
   if (data == data2)
      return 1;

   if (data > data2)
   {
      count += Same_depth(&(*tree_)->left, data, data2 + 1, 0);

      count += Same_depth(&(*tree_)->right, data, data2 + 1, 0);

      return count;
   }

   return 0;
}

int Depth_tree(struct BinTreeNode** tree_)
{
   if ((*tree_) == NULL) {
      return 0;
   }
   else {
      int leftDepth = Depth_tree(&(*tree_)->left);
      int rightDepth = Depth_tree(&(*tree_)->right);

      return 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
   }
}
