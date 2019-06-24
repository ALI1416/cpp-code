#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

void main()
{
	printf("欢迎使用学生管理系统\n");
	printf("请输入口令！\n");
	char get[10],pw[]="123";//密码
	int count=3;
	while(count)
	{
		gets(get);
		if(strcmp(get,pw)==0)
		{
			printf("口令正确！正在进入系统...\n");
			Sleep(500);//head();
		}
		else
		{
			if(count!=1)
			{
				printf("口令错误！请重新输入！\n");
				printf("您还有%d次机会！\n",--count);
			}
			else
			{
				printf("口令错误！按任意键退出系统！\n");
				getch();exit(1);
			}
		}
	}
}