#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define N 8

char *lim()
{
	int i=0;
	char ch;
	char *s=(char *)malloc(sizeof(char)*N);
	while(1)
	{
		ch=getch();
		if(ch>=32&&ch<=127&&i<=N-1)//有效输入字符
		{
			s[i++]=ch;
			printf("*");//输出'*'
			//printf("%c",ch);//输出字符
		}
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

void main()
{
	char *s=lim();
	printf("%s",s);
}

