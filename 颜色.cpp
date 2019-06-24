#include <windows.h>  
#include <stdio.h>
#include <stdlib.h>
/*
FOREGROUND_BLUE 蓝色
FOREGROUND_GREEN 绿色
FOREGROUND_RED 红色
FOREGROUND_INTENSITY 加强
BACKGROUND_BLUE 蓝色背景
BACKGROUND_GREEN 绿色背景
BACKGROUND_RED 红色背景
BACKGROUND_INTENSITY 背景色加强
COMMON_LVB_REVERSE_VIDEO 反色
GetConsoleScreenBufferInfo 获取控制台窗口信息
GetConsoleTitle 获取控制台窗口标题
ScrollConsoleScreenBuffer 在缓冲区中移动数据块
SetConsoleScreenBufferSize 更改指定缓冲区大小
SetConsoleTitle 设置控制台窗口标题
SetConsoleWindowInfo 设置控制台窗口信息
*/
int main()  
{  
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);    
 	
	//  获取输出流的句柄
	
	SMALL_RECT rc = {350,250,500,500};
	SetConsoleWindowInfo(hOut,true ,&rc);
	system("mode con cols=94 lines=30");//屏幕大小

	COORD size={94,100};
	SetConsoleScreenBufferSize(hOut,size);//缓冲区大小
	
	printf("普通颜色看看\n");
	
	SetConsoleTextAttribute(hOut,  
		FOREGROUND_GREEN |		// 前景色_绿色
		FOREGROUND_INTENSITY ); // 前景色_加强
	printf("设置了浅绿色\n");  
	printf("并且完了之后就一直是浅绿色\n");
	
	SetConsoleTextAttribute(hOut,  
		FOREGROUND_BLUE |		// 前景色_蓝色
		FOREGROUND_INTENSITY |	// 前景色_加强
		COMMON_LVB_UNDERSCORE);	// 添加下划线
	printf("文字蓝色，再加个下划线\n");    
	
	SetConsoleTextAttribute(hOut,  
		FOREGROUND_RED |		// 前景色_红色
		FOREGROUND_INTENSITY |	// 前景色_加强
		BACKGROUND_BLUE );		// 背景色_蓝色
	printf("设置文字红色，背景蓝色\n");  
	
	SetConsoleTextAttribute(hOut,  
		FOREGROUND_RED |			// 前景色_红色
		FOREGROUND_INTENSITY |		// 前景色_加强
		COMMON_LVB_GRID_LVERTICAL );// 网格_左_竖
	printf("                      加 左 网格\n");  
	
	SetConsoleTextAttribute(hOut,  
		FOREGROUND_RED |			// 前景色_红色
		FOREGROUND_INTENSITY |		// 前景色_加强
		COMMON_LVB_GRID_RVERTICAL );// 网格_右_竖  
	printf("                      加 右 网格\n");    
	SetConsoleTextAttribute(hOut,  
		FOREGROUND_RED |  // 前景色_红色
		FOREGROUND_BLUE | // 前景色_蓝色
		FOREGROUND_INTENSITY);// 加强
	printf(" 红 + 蓝 = 紫色 ^_^\n");  
	SetConsoleTextAttribute(hOut,  
		FOREGROUND_RED |	// 前景色_红色
		FOREGROUND_GREEN |	// 前景色_绿色
		FOREGROUND_BLUE );  // 前景色_蓝色
	printf("改回白色\n");  
	//system("pause");
	SetConsoleTextAttribute(hOut,4);
	printf("改回白色\n");  
	return 0;  
}