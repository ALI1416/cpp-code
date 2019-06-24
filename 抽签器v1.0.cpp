#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<windows.h>

void rand(int x);
int scan();
int num(char s[]);

void main()
{
	SetConsoleTitle("抽签器"); //标题
	srand((unsigned)time(NULL));
	printf("**************************\n");
	printf("******欢迎使用抽签器******\n");
	printf("**************************\n\n");
	printf("---------使用方法---------\n");	
	printf("--按回车抽签，按其他退出--\n");
	rand(scan());
}

int scan()//输入字符串
{
	while(1)
	{
		char x[100];
		int t;
		printf("\n请输入学生数量");
		gets(x);
		t=num(x);
		if(t>0){return t;break;}
		else {printf("\n输入有误，请重新输入\n");continue;}
	}
}
int num(char s[])//字符串转纯数字
{
	int i=0,n=0,err=0,length=0,num=0;
	length=strlen(s);
	for(i=0;i<length;i++)
		if(s[i]<'0'||s[i]>'9') {err=1;break;}
		if(err==0)
		{
			for(i=0;i<length;i++)
			{
				n=((int)s[i])-48;
				num+=(pow(10,(length-i-1))*n);
			}
			return num;
		}
		else return -1;
}

void rand(int x)//随机数
{
	while(1)
	{
		printf("正在抽签中....\n");
		Sleep(300);//延时300ms
		printf("抽取的学号为：%d\n",rand()%x+1);
		if(getch()==13) continue;
		else break;
	}
}



