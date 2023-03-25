#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define N 10
#define M 8

//无限制输入
char *inf()
{
  char *arr = (char *)malloc(sizeof(char) * N); //保存字符串，初始长度设定为N
  char input;                                   //保存一个从输入流传入的字符
  int strSize = N;                              //计算arr字符串能存储的最大长度
  int Ngth = 0;                                 //存储arr已经存储的字符串长度
  while ((input = getc(stdin)) != '\n')         //从输入流读取一个字符，如果这个字符不是\n
  {
    arr[Ngth] = input;   //将这个字符放入arr
    ++Ngth;              // arr已存储长度加1
    if (Ngth == strSize) //如果字符串长度已经超过了arr的最大能存储长度
    {
      arr = (char *)realloc(arr, strSize + N); //在原来arr的大小上，重新申请一个多N长度的空间
      strSize += N;                            //将arr能存储的最大长度更新
    }
  }
  arr[Ngth] = '\0'; //在字符串末尾加'\0'以示结束
  return arr;
}

void main()
{
  char *s = inf();
  int len = strlen(s);
  if (len > 0 && len <= M)
    printf("字符串：%s，长度：%d\n", s, len);
  else
    printf("错误！\n");
}
