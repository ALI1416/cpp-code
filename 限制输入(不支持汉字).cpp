#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define N 8

char *lim()
{
  int i = 0;
  char ch;
  char *s = (char *)malloc(sizeof(char) * N);
  while (1)
  {
    ch = getch();
    //有效输入字符
    if (ch >= 32 && ch <= 127 && i <= N - 1)
    {
      s[i++] = ch;
      printf("*"); //输出'*'
                   // printf("%c",ch);//输出字符
    }
    //退格
    if (ch == 8 && i > 0)
    {
      i--;
      printf("\b \b");
    }
    //回车
    if (ch == 13 && i > 0)
    {
      s[i] = 0;
      return s;
    }
  }
}

void main()
{
  char *s = lim();
  printf("%s", s);
}
