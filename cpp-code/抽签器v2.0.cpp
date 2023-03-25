#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

void rand(int x);
int scan();
void gotoxy(int x, int y);
void dot_num(int x);

void main()
{
  system("mode con cols=96 lines=32"); //初始化窗口大小
  system("color 07");                  //初始化背景、文字颜色
  SetConsoleTitle("抽签器");           //初始化窗口标题
  srand((unsigned)time(NULL));
  printf("**************************\n");
  printf("******欢迎使用抽签器******\n");
  printf("**************************\n\n");
  printf("---------使用方法---------\n");
  printf("--按回车抽签，按其他退出--\n");
  rand(scan());
}

//改变光标位置
void gotoxy(int x, int y)
{
  HANDLE app;
  COORD pos;
  pos.X = x;
  pos.Y = y;
  app = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(app, pos);
}

//输入字符串，并检查输入是否合法
int scan()
{
  while (1)
  {
    char s[100];
    int i, err = 0, length = 0, x;
    printf("\n请输入学生数量");
    gets(s);
    length = strlen(s);
    for (i = 0; i < length; i++)
      if (s[i] < '0' || s[i] > '9')
      {
        err = 1;
        break;
      }
    x = atoi(s);
    if (x != 0 && err == 0)
    {
      return x;
      break;
    }
    else
    {
      printf("\n输入有误，请重新输入\n");
      continue;
    }
  }
}

//随机数
void rand(int x)
{
  while (1)
  {
    int t;
    t = rand() % x + 1;
    system("cls");
    gotoxy(0, 0);
    printf("抽取的学号为：%d\t", t);
    dot_num(t);
    if (getch() == 13)
      continue;
    else
      break;
  }
}

//打印点阵数字
void dot_num(int x)
{
  int i = 0, j = 10, len = 0;
  char s[10];
  itoa(x, s, 10);
  len = strlen(s);
  i = (96 - len * 12) / 2;
  for (int k = 0, int t = 0; k < len; k++, t++)
  {
    switch (s[k])
    {
    case '0':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("    ■■■  ");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■■    ■");
      gotoxy(i, j++);
      printf("  ■  ■  ■");
      gotoxy(i, j++);
      printf("  ■    ■■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("    ■■■  ");
      i += 12;
      j = 10;
      break;
    case '1':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("      ■    ");
      gotoxy(i, j++);
      printf("    ■■    ");
      gotoxy(i, j++);
      printf("      ■    ");
      gotoxy(i, j++);
      printf("      ■    ");
      gotoxy(i, j++);
      printf("      ■    ");
      gotoxy(i, j++);
      printf("      ■    ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      i += 12;
      j = 10;
      break;
    case '2':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("  ■        ");
      gotoxy(i, j++);
      printf("  ■        ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      i += 12;
      j = 10;
      break;
    case '3':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      i += 12;
      j = 10;
      break;
    case '4':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      i += 12;
      j = 10;
      break;
    case '5':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("  ■        ");
      gotoxy(i, j++);
      printf("  ■        ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      i += 12;
      j = 10;
      break;
    case '6':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("  ■        ");
      gotoxy(i, j++);
      printf("  ■        ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      i += 12;
      j = 10;
      break;
    case '7':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      i += 12;
      j = 10;
      break;
    case '8':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      i += 12;
      j = 10;
      break;
    case '9':
      gotoxy(i, j++);
      printf("            ");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■      ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("          ■");
      gotoxy(i, j++);
      printf("  ■■■■■");
      i += 12;
      j = 10;
      break;
    }
  }
}
