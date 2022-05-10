#include <stdio.h>
#include <conio.h>
#define MAX_PSD_LEN 20

char PassWord[MAX_PSD_LEN], *p = PassWord, ch;
int count = 0;
void main()
{
  printf("input password:");

  ch = getch();                               //输入一个字符，但不显示
  while (ch != 13 && count < MAX_PSD_LEN - 1) /*当按下回车键或密码长度达到19，则退出循环*/
  {

    if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || (ch <= '9' && ch >= '0'))
    /*如果输入的是密码的有效字符*/
    {
      printf("*"); /*输出一个星号*/
      count++;
      *p = ch; /*记录密码内容*/
      p++;
    }
    ch = getch(); /*等待输入下一个字符*/
  }
  PassWord[count] = 0;
  printf("\nThe Password you input is:\n");
  printf("%s\n", PassWord);
}
