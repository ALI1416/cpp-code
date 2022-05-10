#include <afxwin.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "User32.lib")

void main()
{
  SetConsoleTitle("拾色器");          //标题
  system("mode con cols=30 lines=3"); //指定窗口大小
  while (1)
  {
    POINT point;
    ::GetCursorPos(&point); //获取指针坐标
    HWND hWnd = ::GetDesktopWindow();
    HDC hdc = ::GetDC(hWnd);
    int x = point.x, y = point.y;
    COLORREF pixel = ::GetPixel(hdc, x, y);
    if (pixel != CLR_INVALID) //获取坐标RGB值
    {
      int red = GetRValue(pixel);
      int green = GetGValue(pixel);
      int blue = GetBValue(pixel);
      printf("坐 标:(%d,%d)\nRGB值:%X%X%X", x, y, red, green, blue);
    }
    else
      printf("越界！\n");
    Sleep(200);    //延时
    system("cls"); //清屏
  }
}
