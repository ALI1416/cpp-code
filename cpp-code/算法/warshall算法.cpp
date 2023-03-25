#include <stdio.h>

#define N 4

void main()
{
  int i, j, k, m, n;
  int a[N][N] = {{1, 0, 1, 0}, {1, 1, 0, 1}, {0, 1, 0, 0}, {1, 0, 1, 1}};
  printf("初值\n");
  for (m = 0; m < N; m++)
  {
    for (n = 0; n < N; n++)
    {
      printf("%d ", a[m][n]);
    }
    printf("\n");
  }
  printf("\n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      for (k = 0; k < N; k++)
      {
        if (a[i][j] && (a[i][k] || a[j][k]))
        {
          a[i][k] = 1;
        }
      }
    }
    printf("第%d次\n", i + 1);
    for (m = 0; m < N; m++)
    {
      for (n = 0; n < N; n++)
      {
        printf("%d ", a[m][n]);
      }
      printf("\n");
    }
    printf("\n");
  }
}
