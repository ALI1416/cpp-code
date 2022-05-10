#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//声明
void rand(int a[52], int b[52]);       //分牌器
void print(int a[], int b[], int c[]); //输出
int count(int j[]);                    //计数器

//分牌器
void rand(int a[52], int b[52])
{ // z[]每一个数字的个数,a[]一号牌,b[]二号牌,n总牌
  int z[14] = {0}, n = 0, i, x;
  for (i = 0; n < 52; i++)
  {
    x = rand() % 13 + 1; //产生[1,13]的随机数
    {
      if (z[x] < 4)
      {
        z[x]++;
        n++;
        if (n < 27)
          a[n - 1] = x;
        else
          b[n - 27] = x;
      }
    }
  }
}

//计数器
int count(int j[])
{
  for (int i = 0; i < 52; i++)
    if (j[i] == 0)
      return i;
}

//输出
void print(int a[], int b[], int c[])
{
  int i;
  printf("桌  牌：共%d张\n", count(c)); //桌牌
  for (i = 0; i < 14; i++)
  {
    if (c[i] != 0)
    {
      if ((i + 1) % 10 == 0)
        printf("%-4d\n", c[i]);
      else
        printf("%-4d", c[i]);
    }
  }
  printf("\n玩家一：共%d张\n", count(a)); //玩家一
  for (i = 0; i < 52; i++)
  {
    if (a[i] != 0)
    {
      if ((i + 1) % 10 == 0)
        printf("%-4d\n", a[i]);
      else
        printf("%-4d", a[i]);
    }
  }
  printf("\n玩家二：共%d张\n", count(b)); //玩家二
  for (i = 0; i < 52; i++)
  {
    if (b[i] != 0)
    {
      if ((i + 1) % 10 == 0)
        printf("%-4d\n", b[i]);
      else
        printf("%-4d", b[i]);
    }
  }
  printf("\n");
}

void main()
{
  int a[52] = {0}, b[52] = {0}, c[14] = {0}; // a[]一号牌,b[]二号牌,c[]桌牌
  srand((unsigned)time(NULL));               //用时间做种子，每次产生随机数不一样
  rand(a, b);
  print(a, b, c);
}
