
void Transp(long int** Tmatrix, long int** matrix, int n, int m)
{
   
   for (int i = 0; i < n; ++i)
   {
      for (int j = 0; j < n; ++j)
      {
         Tmatrix[j][i] = matrix[i][j];
      }
   }
}