#pragma once

typedef struct BinTreeNode
{
   struct BinTreeNode* parent;
   struct BinTreeNode* left;
   struct BinTreeNode* right;
   int data;
}BinTreeNode;

/*
* @brief Íàõîäèò ýëåìåíò â äåðåâå
* @param tree_: Áèíàðíîå äåðåâî 
* @param data_: Èñêîìîå çíà÷åíèå
* @return Óêàçàòåëü íà ýëåìåíò äåðåâà ñîäåðæàùèé èñêîìîå çíà÷åíèå
*/
BinTreeNode* Find(BinTreeNode* tree_, int data_);

/*
* @brief Âñòàâëÿåò ýëåìåíò â äåðåâî
* @param tree_: Áèíàðíîå äåðåâî
* @param node_: Âñòàâëÿåìûé ýëåìåíò
*/
void Insert(BinTreeNode** tree_, BinTreeNode* node_);

/*
* @brief Óäàëÿåò ýëåìåíò èç äåðåâà
* @param tree_: Áèíàðíîå äåðåâî
* @param node_: Óäàëÿåìûé ýëåìåíò
*/
void Remove(BinTreeNode** tree_, int data_);

void Print(BinTreeNode** tree_);

int Sum(BinTreeNode** tree_, int sum);

int Max(BinTreeNode** tree_);

int Min(BinTreeNode** tree_);

int Number_of_elements(BinTreeNode** tree_, int data);

void Print_leaves(BinTreeNode** tree_);

void Depth_sensitive_printing(struct BinTreeNode** tree_, int data);

int Depth_elements(struct BinTreeNode** tree_, int data, int data2);

int Same_depth(struct BinTreeNode** tree_, int data, int data2, int count);

int Depth_tree(struct BinTreeNode** tree_);
