#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#define N 16

void gotoxy(int x,int y)
{
	HANDLE app;
	COORD  pos;
	pos.X=x;
	pos.Y=y;
	app=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(app,pos);
}
//printf("█　▏▕▁▔");

char *lim()
{
	int i=0;
	char ch;
	char *s=(char *)malloc(sizeof(char)*N);
	while(1)
	{
		ch=getch();
		if(ch>=33&&ch<=127&&i<=N-1)//有效输入字符
		{
			s[i++]=ch;
			printf("*");//输出'*'
			//printf("%c",ch);//输出字符
		}
		if(ch==32)//空格退出
			exit(0);
		if(ch==8&&i>0)//退格
		{
			i--;
			printf("\b \b");
		}
		if(ch==13&&i>0)//回车
		{
			s[i]=0;
			return s;
		}
	}
}

int pass(char *pw)
{
	printf("\n\n\n");
	printf("\t\t\t\t██████████████\n");
	printf("\t\t\t\t▏                        ▕\n");
	printf("\t\t\t\t▏       请输入口令       ▕\n");
	printf("\t\t\t\t▏    ▁▁▁▁▁▁▁▁    ▕\n");
	printf("\t\t\t\t▏  ▕                ▏  ▕\n");
	printf("\t\t\t\t▏    ▔▔▔▔▔▔▔▔    ▕\n");
	printf("\t\t\t\t▏[回车]确认    [空格]关闭▕\n");
	printf("\t\t\t\t▏                        ▕\n");
	printf("\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
	gotoxy(38,7);
	int count=3;
	while(count)
	{
		char *get=lim();
		if(strcmp(get,pw)==0)
		{
			gotoxy(33,10);
			printf("口令正确！正在进入系统...");
			getch();
			//delay();
			return 1;//正确
		}
		else
		{
			if(count!=1)
			{
				gotoxy(33,10);
				printf("口令错误！剩余尝试次数%d次",--count);
				gotoxy(38,7);
				printf("\t\t");
				gotoxy(38,7);
			}
			else
			{
			gotoxy(33,10);
				printf("口令错误！按任意键退出。");
				getch();
				return 0;//错误
			}
		}
	}
	return 0;
}

void main()
{
	pass("123");
	
}