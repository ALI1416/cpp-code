//////////////////////////////////////////////////////
//          名称：   抽签器v3.0						//
//          语言：   C语言							//
//		上一版本：   抽签器v2.0						//
//		增加功能：   增大显示数字字体				//
//          环境：   Microsoft Visual C++ 6.0		//
//          作者：   阿狸141						//
//          日期：   2017年5月27日					//
//////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<windows.h>

void rand(int x);
int scan();
void gotoxy(int x,int y);
void dot_num(int x);

void main()
{
	system("mode con cols=96 lines=32");//初始化窗口大小
	system("color 07");//初始化背景、文字颜色
	SetConsoleTitle("抽签器"); //初始化窗口标题
	srand((unsigned)time(NULL));
	printf("\t\t\t\t**************************\n");
	printf("\t\t\t\t******欢迎使用抽签器******\n");
	printf("\t\t\t\t**************************\n\n");
	printf("\t\t\t\t---------使用方法---------\n");	
	printf("\t\t\t\t--按回车抽签，按其他退出--\n\n");
	printf("\t\t\t\t\t\t\t\t关于：抽签器v3.0\n");
	printf("\t\t\t\t\t\t\t\t作者：阿狸141\n");
	printf("\t\t\t\t\t\t\t\t日期：2017年5月27日\n");
	rand(scan());
}

void gotoxy(int x,int y)//改变光标位置
{
	HANDLE app;
	COORD  pos;
	pos.X=x;
	pos.Y=y;
	app=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(app,pos);
}

int scan()//输入字符串，并检查输入是否合法
{
	while(1)
	{
		char s[20];
		int i,err=0,length=0,x;
		printf("\n请输入学生数量");
		gets(s);
		length=strlen(s);
		for(i=0;i<length;i++)
			if(s[i]<'0'||s[i]>'9') 
			{err=1;break;}
			x=atoi(s);
			if(x!=0&&err==0){return x; break;}
			else {printf("\n输入有误，请重新输入\n");continue;}
	}
}

void rand(int x)//随机数
{
	while(1)
	{
		int t;
		t=rand()%x+1;
		system("cls");
		printf("抽取总人数为：%d\n",x);
		printf("抽取的学号为：%d\n",t);
		printf("按回车键继续抽签\n");
		printf("按其他键退出\n");
		dot_num(t);
		if(getch()==13) continue;
		else break;
	}
}

void dot_num(int x)//打印点阵数字
{
	int i=0,j=10,len=0;
	char s[10];
	itoa(x,s,10);
	len=strlen(s);
	i=(96-len*16)/2;
	for(int k=0,int t=0;k<len;k++,t++)
	{
		switch(s[k])
		{
		case '0':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("    ■■■■■  ");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■■        ■");
			gotoxy(i,j++);printf("  ■  ■      ■");
			gotoxy(i,j++);printf("  ■    ■    ■");
			gotoxy(i,j++);printf("  ■      ■  ■");
			gotoxy(i,j++);printf("  ■        ■■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("    ■■■■■  ");
			i+=16;j=10;break;
		case '1':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("        ■      ");
			gotoxy(i,j++);printf("      ■■      ");
			gotoxy(i,j++);printf("    ■  ■      ");
			gotoxy(i,j++);printf("        ■      ");
			gotoxy(i,j++);printf("        ■      ");
			gotoxy(i,j++);printf("        ■      ");
			gotoxy(i,j++);printf("        ■      ");
			gotoxy(i,j++);printf("        ■      ");
			gotoxy(i,j++);printf("        ■      ");
			gotoxy(i,j++);printf("        ■      ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			i+=16;j=10;break;
		case '2':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			i+=16;j=10;break;
		case '3':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			i+=16;j=10;break;
		case '4':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			i+=16;j=10;break;
		case '5':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			i+=16;j=10;break;
		case '6':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■            ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			i+=16;j=10;break;
		case '7':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			i+=16;j=10;break;
		case '8':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			i+=16;j=10;break;
		case '9':
			gotoxy(i,j++);printf("                ");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■          ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("              ■");
			gotoxy(i,j++);printf("  ■■■■■■■");
			i+=16;j=10;break;
		}
	}
}