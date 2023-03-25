/*制表符
△▽〇◇□☆▲▼●◆■★
‥…∷※√×♀♂§◎¤‖卍卐〓℡
▁▂▃▄▅▆▇█

▏▎▍▌▋▊▉█

▓█　▏▕▁▔│┃║─━═┈┉┊┋╱╲╳
　▁　┌┬┐┏┳┓╔╦╗↖↑↗◤　◥
▕　▏├┼┤┣╋┫╠╬╣←㊣→　◆　
　▔　└┴┘┗┻┛╚╩╝↙↓↘◣　◢
*/

//初始化窗口大小
#include<stdlib.h>
system("mode con cols=50 lines=15");

//初始化窗口的标题
#include<windows.h>
SetConsoleTitle("窗口"); 

//请按任意键继续
#include<stdio.h>
system("PAUSE");//请按任意键继续. . .

//初始化背景、文字颜色
#include<stdlib.h>
system("color 07");//背景，文字
/*
0 = 黑色   8 = 灰色 
1 = 蓝色   9 = 淡蓝色 
2 = 绿色   A = 淡绿色 
3 = 浅绿色 B = 淡浅绿色 
4 = 红色   C = 淡红色 
5 = 紫色   D = 淡紫色 
6 = 黄色   E = 淡黄色 
7 = 白色   F = 亮白色 
*/

//颜色
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_INTENSITY);//黑底亮蓝字。	

//数字转字符串
#include<stdlib.h>
itoa(123,str,10);  //将整型值转换为字符串
itoa(123,str,10);  //将长整型值转换为字符串
ultoa(123,str,10); //将无符号长整型值转换为字符串
//(被转换的数字,目标字符串,基数)
//上述函数与ANSI标准是不兼容的。

//字符串格式转换函数
#include<stdio.h>
sprintf(str,"%X",15);//注意：不是输出
/*(目标字符串,转换格式,被转换数字)
%c 整数转成对应的 ASCII 字元。
%d 整数转成十进位。
%f 倍精确度数字转成浮点数。
%o 整数转成八进位。
%s 整数转成字符串。
%x 整数转成小写十六进位。
%X 整数转成大写十六进位。*/

//字符串转数字(注意溢出)
#include<stdlib.h>
atoi(str);
/*atof()    将字符串转换为双精度浮点型值
 atoi()     将字符串转换为整型值
 atol()     将字符串转换为长整型值
 strtod()   将字符串转换为双精度浮点型值，并报告不能被转换的所有剩余数字
 strtol()   将字符串转换为长整值，并报告不能被转换的所有剩余数字
 strtoul()  将字符串转换为无符号长整型值，并报告不能被转换的所有剩余数字*/

//延时
#include<windows.h>
Sleep(1000);//毫秒

//清屏
#include<windows.h>
system("cls");

//获取输入字符，不显示
#include<conio.h>
getch();

//随机数
#include<stdlib.h>
#include<time.h>
srand((unsigned)time(NULL));
rand();

//初始化光标输出位置(函数)
#include<windows.h>
void gotoxy(int x,int y)
{
	HANDLE app;
	COORD  pos;
	pos.X=x;
	pos.Y=y;
	app=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(app,pos);
}

//获取当前光标所在的屏幕的位置坐标
#include <stdio.h>
#include <afx.h>
void main()
{
    POINT point;
    ::GetCursorPos(&point);
    printf("x=%d,y=%d\n",point.x,point.y);
}

//获取指定位置颜色值
#include<afxwin.h>
#include<windows.h>
#pragma comment (lib,"User32.lib")
void main()
{
	HWND hWnd=::GetDesktopWindow();
	HDC hdc=::GetDC(hWnd);
	int x=100,y=100;//指定位置
	COLORREF pixel=::GetPixel(hdc,x,y);
	if(pixel!=CLR_INVALID) 
	{
		int red = GetRValue(pixel);
		int green = GetGValue(pixel);
		int blue = GetBValue(pixel);
		printf("%x%x%x\n",red,green,blue);
	}
	else 
		printf("越界！\n");
	system("PAUSE");//请按任意键继续. . .
}

//获取当前光标所在工作台的坐标
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
void main(int argc,char*argv[])
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen={0,0}; 
    CONSOLE_SCREEN_BUFFER_INFO csbi;
	int x,y;
    if (GetConsoleScreenBufferInfo(hConsole,&csbi))
	{
		x=csbi.dwCursorPosition.X;
		y=csbi.dwCursorPosition.Y;
	}
	printf("光标坐标:(%d,%d)\n",x,y);
}

//输出时间
#include <stdio.h>
#include <time.h>  
void main ()
{
	time_t rawtime;
	struct tm*timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	char CruuentTime[50];
	strftime(CruuentTime,24,"%Y-%m-%d %H:%M:%S\n",timeinfo);//格式化时间
	printf(CruuentTime);
}

#include <time.h>
#include<stdio.h>
/*struct tm1{
int tm_sec;  //代表目前秒数, 正常范围为0-59, 但允许至61 秒
int tm_min;  //代表目前分数, 范围0-59
int tm_hour;  //从午夜算起的时数, 范围为0-23
int tm_mday;  //目前月份的日数, 范围01-31
int tm_mon;  //代表目前月份, 从一月算起, 范围从0-11
int tm_year;  //从1900 年算起至今的年数
int tm_wday;  //一星期的日数, 从星期一算起, 范围为0-6
int tm_yday;  //从今年1 月1 日算起至今的天数, 范围为0-365
int tm_isdst;  //日光节约时间的旗标
};*/
void main(){
    char *wday[] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    printf("%d-%d-%d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    printf(" %s %d:%d:%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
}

//纯数字整数型输出
#include<stdio.h>
#include<string.h>
#include<math.h>
int num(char s[])
{
	int i,x,err=0,length=0,num=0;
	length=strlen(s);
	for(i=0;i<length;i++)
		if(s[i]<'0'||s[i]>'9') 
		{err=1;break;}
		if(err==0)
		{
			for(i=0;i<length;i++)
			{
				x=((int)s[i])-48;
				num+=(pow(10,(length-i-1))*x);
			}
			return num;
		}
		else 
			return -1;
}

void main()
{
	char s[10];
	gets(s);
	printf("%d",num(s));
}

//纯数字字符串输出
#include<stdio.h>
#include<string.h>
int num(char s[])
{
	int i,x,err=0,length=0,num=0;
	length=strlen(s);
	for(i=0;i<length;i++)
		if(s[i]<'0'||s[i]>'9') 
		{err=1;break;}
		return err;
}

void main()
{
	char s[10];
	gets(s);
	if(num(s)==0) puts(s);
}

//冒泡排序
for(j=0;j<n-1;j++)
for(i=0;i<n-1-j;i++)
{
	if(a[i]>a[i+1])
	{t=a[i];a[i]=a[i+1];a[i+1]=t;}
}

//选择排序
for(i=0;i<N-1;i++)
{
	k=i;
	for(j=i+1;j<N;j++)
		if(a[k]<a[j])k=j;
		if(k!=i){t=a[i];a[i]=a[k];a[k]=t;}
}

//字符串排序
void sort(struct people *p)
{
	int i,j,k;
	struct people tmp;
	for(i=0;i<N-1;i++)
	{
		k=i;
		for(j=i+1;j<N;j++)
		{
			if(strcmp(p[k].name,p[j].name)>0)k=j;
			if(k!=j){tmp=p[i];p[i]=p[j];p[j]=tmp;}
		}
	}
}