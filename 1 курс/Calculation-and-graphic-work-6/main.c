#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX 2147483647

int my_sqrt(int n)
{
   int i = 0;
   for (; i * i < n; ++i);
   return i;
}

void MinInSplit_w(int* b, int k, int* arr, int n, int p)
{
   for (int x = 0; x < k; x++)
   {
      int index = x * p;
      for (int i = x * p; i < (x + 1) * p && i < n; i++)
         if (arr[i] < arr[index])
            index = i;
      b[x] = index;
   }
}

void MinInSplit_rew(const int* arr, int n, int* b, int step, int index_b)
{
   int index = index_b*step;
   for (int i = index_b * step; i < (index_b + 1) * step && i < n; i++)
      if (arr[i] < arr[index])
         index = i;
   b[index_b] = index;
}

int MinInSplit_index(const int* arr, int n, int* b, int k)
{
   int min_index = 0;
   for (int i = 0; i < k && i < n; ++i)
      if (arr[b[i]] < arr[b[min_index]])
         min_index = i;
   return b[min_index];
}

void QuadraticChoice(int* arr, int n)
{
   int index_x = 0;
   int p = my_sqrt(n); 
   int k = (n + p - 1) / p; 

   int* b = (int*)malloc((unsigned long) (k+1) * sizeof(int)); 
   if (b == NULL)
   {
      printf("Memory allocation failed");
      return;
   }
         
   int* c = (int*)malloc((unsigned long)(n+1) * sizeof(int));
   if (c == NULL)
   {
      printf("Memory allocation failed");
      return;
   }
   
   MinInSplit_w(b, k, arr, n, p);

   for (int i = 0; i < n; ++i)
   {
      index_x = MinInSplit_index(arr, n, b, k);
      
      c[i] = arr[index_x];
      arr[index_x] = MAX;
      MinInSplit_rew(arr, n, b, p, index_x/p);
   }

   for (int i = 0; i < n; ++i)
      arr[i] = c[i];

   free(b);
   free(c);
}

int BlockSearch(const int* arr, int n, int cn_blocks, int x)
{
   int step = (n + cn_blocks - 1) / cn_blocks;
   int l = 0;
   int r = step;
   while (arr[((r < n) ? r : n) - 1] < x)
   {
      l = r;
      r = r + step;
      if (l > n)
         return -1;
   }

   while (arr[l] < x)
   {
      ++l;
      if (l == ((r < n) ? r : n))
         return -1;
   }

   return ((arr[l] == x) ? l : -1);
}

int main(int argc, char* argv[])
{
   
   if (argc != 3)
   {
      printf("Mismatch in number of arguments");
   }
   

   int N = 0;
   for (int y = 0; argv[1][y] != '\0'; ++y)
      N = N * 10 + (argv[1][y] - '0');
      

   int find = 0;
   for (int f = 0; argv[2][f] != '\0'; ++f)
      find = find * 10 + (argv[2][f] - '0');


   int* arr = (int*)malloc((unsigned long)(N+1) * sizeof(int));
   if (arr == NULL) 
   {
      printf("Memory allocation failed");
      return -20;
   }

   srand((unsigned int)(time(NULL)));
   
   for (int x = 0; x < N; ++x)
      arr[x] = rand() % MAX;
   
   QuadraticChoice(arr, N);

   double minimal_time = MAX;
   int optimal_option = 0;
   int t = 0;
   clock_t start, finish;
   double time = 0.0;

   for (int x = 1; x < N; ++x)
   {
      start = clock();
      t = BlockSearch(arr, N, x, find);
      finish = clock();

      time = ((double)(finish - start)) / (CLOCKS_PER_SEC);
      
      if (minimal_time > time)
      {
         minimal_time = time;
         optimal_option = x;
      }
   }
   printf("Optimal option: %d %d %f \n", optimal_option, t, time);

   free(arr);
   return 0;
}
