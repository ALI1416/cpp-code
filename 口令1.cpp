#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define PW "123"//密码
#define N 8//最大输入上限

void main()
{
	char s[]=PW;
	char *t=(char *)malloc(N);
	while(1)
	{
		gets(t);
		if(strlen(t)>N)
		{
			printf("密码溢出！\n");
		}
		else
		{
			if(strcmp(s,t)==0)
			{
				printf("密码正确！\n");
				break;
			}
			else
			{
				printf("密码错误！\n");
			}
		}
	}
}