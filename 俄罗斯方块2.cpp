//////////////////////////////////////////////////////////////
//          名称：   俄罗斯方块 彩色版  1.1.0
//          语言：   C语言
//      上一版本：   俄罗斯方块 彩色版  1.0.0
//      增加功能：   增加关卡 和 最高分
//          环境：   Microsoft Visual C++ 6.0
//          作者：   鼠标猎人
//          日期：   2015年1月19号
//////////////////////////////////////////////////////////////
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
void gotoxy(int x, int y); //控制光标。X表示横坐标，Y表示纵坐标
void console();            //设置控制台窗口大小，为了让程序运行得更好看
void my_print();           //设置界面
void my_randout();         //随机出现方块，并打印在提示区
void my_printblock();      //打印 4*4 的方格来显示方块
void my_up();              //旋转
void my_down();            //下移
void my_lift();            //左移
void my_right();           //右移
void my_exit();            //退出前保存最高分
void clear();              //消除整行
void gameover();           //游戏结束
void my_stop();            //游戏暂停
int tem[4][4];             //用4*4的方格来控制方块的操作和显示 这个作为传值媒介
int block[4][4];           //提示区的方块
int BLOCK[4][4];           //正在下落的方块
int scope[25][34] = {0};   //操作的范围 这里要注意，一个方格是占两个横坐标单位的
int point_x, point_y;      //方格的左上角坐标
int fen = 0;               //得分
int pass = 1;              //关卡  新增
int hang = 0;              //消除的总行数
int max_fen = 0;           //最高分 新增
FILE *fp;
bool check = true;                                                           //检查方块还能不能下落
int block0[4][4] = {{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}; // 7 个方块 用数组表示 正“7”
int block1[4][4] = {{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}; // 反“7”
int block2[4][4] = {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}}; // 反“z”
int block3[4][4] = {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}; // 正“z”
int block4[4][4] = {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}; // 倒“T”
int block5[4][4] = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}; // 正方形
int block6[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}}; // 直条

void main()
{
  if ((fp = fopen("test.txt", "r")) == NULL)
  {
    fp = fopen("test.txt", "w+"); //打开文件 如果没有就创建
  }
  srand((unsigned)time(NULL)); //设置随机数种子
  char key;
  int i, j;
  fscanf(fp, "%d", &i);
  max_fen = max_fen > i ? max_fen : i; //将最高分赋给max_fen
  fclose(fp);                          //关闭文件
  int time;                            //控制下落时间
  console();
  my_print();
  my_randout();
  while (true) //死循环
  {
    if (check) //如果没有正在下落的方块就执行if里面的
    {
      check = false;
      point_x = 14; //方块最初出现的地方
      point_y = 0;
      for (i = 0; i < 4; i++)
      {
        for (j = 0; j < 4; j++)
        {
          BLOCK[i][j] = block[i][j]; //将提示区的方块数组传到下落的方块数组
        }
      }
      my_printblock(); //在point_x,point_y显示方块。
      my_randout();    //提示区随机换一个方块
    }
    if (kbhit()) //检测，如果有按键就执行if里面的
    {
      key = getch(); //捕获按键
      switch (key)
      {
      case 72:
        my_up(); //上
        break;
      case 75:
        my_lift(); //左
        break;
      case 77:
        my_right(); //右
        break;
      case 80:
        my_down(); //下
        break;
      case 32:
        my_stop(); //空格 暂停或开始
        break;
      case 27:
        my_exit(); // Esc 退出
      default:;
      }
    }
    Sleep(30);                         //等待0.03秒 0.03秒才能执行一个按键 也降低CPU
    if (0 == ++time % (32 - pass * 3)) //控制下落的时间=30*30毫秒
    {
      my_down(); //时间到自动下落一格
    }
    if (true == check) //当不能下落时
    {
      for (i = 0; i < 4; i++)
      {
        for (j = 0; j < 4; j++)
        {
          if (1 == BLOCK[i][j])
            scope[point_x / 2 + j][point_y + i] = BLOCK[i][j]; //把下落的方块赋值给操作区的数组
                                                               //这里的point_x除以2是因为一个小格子占两个横坐标
        }
      }
      my_printblock();
      clear(); //如果有某一行满了就消除
    }
  }
}

//设置窗口位置和大小，为了让程序运行得更好看
void console()
{
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
  CONSOLE_SCREEN_BUFFER_INFO bInfo;              // 窗口缓冲区信息
  GetConsoleScreenBufferInfo(hOut, &bInfo);      // 获取窗口缓冲区信息
  SetConsoleTitle("俄罗斯方块 C版");             // 设置窗口的标题
  COORD size = {80, 32};                         //不能小于默认大小（80，25）
  SetConsoleScreenBufferSize(hOut, size);        // 重新设置缓冲区大小*/
  SMALL_RECT rc = {0, 0, 63, 31};                //不能大于缓冲区大小
  SetConsoleWindowInfo(hOut, true, &rc);         // 重置窗口大小
}

void my_print()
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY); //黑底亮蓝字。
  for (int i = 1; i < 30; i++)
    printf("■\t\t\t\t■ |                           |\n");
  printf("■■■■■■■■■■■■■■■■■ |---------------------------|\n"); //框架
  gotoxy(36, 0);
  printf("---------------------------");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); //黑底亮黄字。
  gotoxy(40, 2);
  printf("关  卡： %d", pass);
  gotoxy(40, 3);
  printf("分  数： %d", fen);
  gotoxy(40, 4);
  printf("最高分： %d", max_fen);
  gotoxy(36, 6);
  printf("下一个方块：");
  gotoxy(36, 14);
  printf("操作方法：");
  gotoxy(40, 16);
  printf("↑：旋转 ↓：沉淀");
  gotoxy(40, 18);
  printf("→：右移 ←：左移");
  gotoxy(39, 20);
  printf("空格键：开始 / 暂停");
  gotoxy(39, 22);
  printf("    Esc：退出");
  gotoxy(36, 25);
  printf("关 于：");
  gotoxy(40, 26);
  printf("俄罗斯方块 1.1.0");
  gotoxy(49, 27);
  printf("作者：鼠标猎人");
  gotoxy(50, 28);
  printf("2015年1月19日");
}

//设置光标输出的位置函数。坐标不能为负数
void gotoxy(int x, int y) // X表示横坐标，Y表示纵坐标。
{
  HANDLE app;
  COORD pos;
  pos.X = x;
  pos.Y = y;
  app = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(app, pos);
}
//旋转 将4*4方格顺时针旋转
void my_up()
{
  int i, j;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      tem[i][j] = BLOCK[i][j];
      if (1 == BLOCK[i][j])
      {
        gotoxy(point_x + j * 2, point_y + i);
        printf("  ");
      }
    }
  }
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      BLOCK[j][3 - i] = tem[i][j];
    }
  }
  //以上为旋转。
  //下面为防止旋转后超出框架范围
  for (j = 0; j < 2; j++)
  {
    for (i = 0; i < 4; i++)
    {
      if (1 == BLOCK[i][j] && point_x < 2)
      {
        point_x += 2;
      }
      else if (1 == BLOCK[i][3 - j] && point_x > 24)
      {
        point_x -= 2;
      }
    }
  }
  my_printblock(); //旋转之后立即显示出来
}
//左移
void my_lift()
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
    {
      if (1 == BLOCK[j][i] && (point_x + 2 * i - 1 < 2 || 1 == scope[point_x / 2 + i - 1][point_y + j]))
      {
        return; //如果到边缘 或者是左边已经有了方块
      }
    }
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (1 == BLOCK[i][j])
      {
        gotoxy(point_x + j * 2, point_y + i);
        printf("  "); //把之前的擦掉
      }
  point_x -= 2;
  my_printblock();
}

void my_right()
{
  int i, j;
  for (i = 3; i > 0; i--)
    for (j = 0; j < 4; j++)
    {
      if (1 == BLOCK[j][i] && (point_x + 2 * i + 2 > 30 || 1 == scope[point_x / 2 + i + 1][point_y + j]))
      {
        return; //如果到边缘 或者是右边已经有了方块
      }
    }
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (1 == BLOCK[i][j])
      {
        gotoxy(point_x + j * 2, point_y + i);
        printf("  "); //把之前的擦掉
      }
  point_x += 2;
  my_printblock();
}

void my_down()
{
  int i, j;
  if (true == check)
  {
    return; //不能下落直接不执行
  }
  gotoxy(point_x, point_y);
  for (i = 3; i > 0; i--) //检测该方格还能不能下落
    for (j = 0; j < 4; j++)
      if (1 == BLOCK[i][j])
      {
        if (1 == scope[point_x / 2 + j][point_y + i + 1] || point_y + i + 1 > 28) //到最下边或是下面已经有方格
        {
          check = true;
          return;
        }
      }
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (1 == BLOCK[i][j])
      {
        gotoxy(point_x + j * 2, point_y + i);
        printf("  "); //能下落，擦除以前的方格
      }
  point_y++;
  my_printblock(); //在下一格显示
}
//暂停
void my_stop()
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
  gotoxy(10, 10);
  printf("              ");
  gotoxy(10, 11);
  printf("  ■■■■■  ");
  gotoxy(10, 12);
  printf("  ■      ■  ");
  gotoxy(10, 13);
  printf("  ■      ■  ");
  gotoxy(10, 14);
  printf("  ■■■■■  ");
  gotoxy(10, 15);
  printf("  ■          ");
  gotoxy(10, 16);
  printf("  ■           ");
  gotoxy(10, 17);
  printf("  ■          ");
  gotoxy(10, 18);
  printf("              ");
  if (32 == getch()) //用等待输入字符实现暂停 32为空格
  {
    gotoxy(10, 10);
    printf("              ");
    gotoxy(10, 11);
    printf("  ■■■■■  ");
    gotoxy(10, 12);
    printf("          ■  ");
    gotoxy(10, 13);
    printf("          ■  ");
    gotoxy(10, 14);
    printf("  ■■■■■  ");
    gotoxy(10, 15);
    printf("          ■  ");
    gotoxy(10, 16);
    printf("          ■  ");
    gotoxy(10, 17);
    printf("  ■■■■■  ");
    gotoxy(10, 18);
    printf("              ");
    Sleep(1000);
    gotoxy(10, 10);
    printf("              ");
    gotoxy(10, 11);
    printf("  ■■■■■  ");
    gotoxy(10, 12);
    printf("          ■  ");
    gotoxy(10, 13);
    printf("          ■  ");
    gotoxy(10, 14);
    printf("  ■■■■■  ");
    gotoxy(10, 15);
    printf("  ■          ");
    gotoxy(10, 16);
    printf("  ■          ");
    gotoxy(10, 17);
    printf("  ■■■■■  ");
    gotoxy(10, 18);
    printf("              ");
    Sleep(1000);
    gotoxy(10, 10);
    printf("              ");
    gotoxy(10, 11);
    printf("      ■■    ");
    gotoxy(10, 12);
    printf("    ■■■    ");
    gotoxy(10, 13);
    printf("      ■■    ");
    gotoxy(10, 14);
    printf("      ■■    ");
    gotoxy(10, 15);
    printf("      ■■    ");
    gotoxy(10, 16);
    printf("      ■■    ");
    gotoxy(10, 17);
    printf("    ■■■■  ");
    gotoxy(10, 18);
    printf("              ");
    Sleep(1000);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    for (int i = 0; i < 9; i++) //将暂停掩盖的方块再次显示出来
    {
      gotoxy(10, 10 + i);
      for (int j = 0; j < 7; j++)
      {
        if (1 == scope[5 + j][10 + i])
        {
          printf("■");
        }
        else
        {
          printf("  ");
        }
      }
    }
  }
}
//消除
void clear()
{
  int i, j, k, m = 0;
  for (i = point_y + 3; i >= point_y; i--)
  {
    for (j = 1; j < 16; j++)
    {
      if (0 == scope[j][i])
      {
        break;
      }
    }
    if (16 == j)
    {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
      m++;
      for (k = i; k > 3; k--)
      {
        for (j = 1; j < 16; j++)
        {
          scope[j][k] = scope[j][k - 1];
          gotoxy(j * 2, k);
          if (1 == scope[j][k])
          {
            printf("■");
          }
          else
          {
            printf("  ");
          }
        }
      }
      for (j = 1; j < 16; j++)
      {
        scope[j][4] = 0;
      }
      i++;
    }
  }
  switch (m)
  { //判断一次消除了几行，来设置得分数
  case 1:
    fen += 100;
    break;
  case 2:
    fen += 230;
    break;
  case 3:
    fen += 438;
    break;
  case 4:
    fen += 854;
    break;
  default:;
  }
  hang += m;
  if (hang > 10) //每10行升一关
  {
    hang = 0;
    pass++;
  }
  max_fen = max_fen > fen ? max_fen : fen;                                                                            //更新最高分
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); //黑底亮黄色字。
  gotoxy(40, 2);
  printf("关  卡： %d", pass);
  gotoxy(40, 3);
  printf("分  数： %d", fen);
  gotoxy(40, 4);
  printf("最高分： %d", max_fen);
  for (j = 7; j < 11; j++)
  {
    if (1 == scope[j][4])
      gameover();
  }
}
//随机出现方块
void my_randout()
{
  int i, j;
  switch (rand() % 7)
  {
  case 0:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        block[i][j] = block0[i][j];
    break;
  case 1:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        block[i][j] = block1[i][j];
    break;
  case 2:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        block[i][j] = block2[i][j];
    break;
  case 3:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        block[i][j] = block3[i][j];
    break;
  case 4:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        block[i][j] = block4[i][j];
    break;
  case 5:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        block[i][j] = block5[i][j];
    break;
  case 6:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        block[i][j] = block6[i][j];
    break;
  default:;
  }
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      tem[i][j] = block[i][j];
    }
  }
  switch (rand() % 4) //再设置随机旋转的方向
  {
  case 0:
    break;
  case 1:
    for (i = 0; i < 4; i++) //顺时针90度
    {
      for (j = 0; j < 4; j++)
      {
        block[j][3 - i] = tem[i][j];
      }
    }
    break;
  case 2:
    for (i = 0; i < 4; i++) //顺180度
    {
      for (j = 0; j < 4; j++)
      {
        block[3 - i][3 - j] = tem[i][j];
      }
    }
    break;
  case 3:
    for (i = 0; i < 4; i++) //顺270度
    {
      for (j = 0; j < 4; j++)
      {
        block[3 - j][i] = tem[i][j];
      }
    }
    break;
  default:;
  }
  //打印提示区的方块
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); //黑底亮红字。
  for (i = 0; i < 4; i++)
  {
    gotoxy(44, 8 + i);
    for (j = 0; j < 4; j++)
    {
      if (1 == block[i][j])
      {
        printf("■");
      }
      else
      {
        printf("  ");
      }
    }
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //黑底白字
}

//显示方格
void my_printblock()
{
  int i, j;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      if (point_x / 2 + j > 0)
      {
        if (1 == scope[point_x / 2 + j][point_y + i])
        {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
          gotoxy(point_x + j * 2, point_y + i);
          printf("■");
        }
        else if (1 == BLOCK[i][j])
        {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
          gotoxy(point_x + j * 2, point_y + i);
          printf("■");
        }
      }
    }
  }
}
void gameover()
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
  gotoxy(4, 10);
  printf("                                                        ");
  gotoxy(4, 11);
  printf("    ■■■      ■      ■      ■■■■      ■■■■  ");
  gotoxy(4, 12);
  printf("  ■      ■    ■      ■      ■            ■    ■  ");
  gotoxy(4, 13);
  printf("  ■      ■      ■  ■        ■■■■      ■■■■  ");
  gotoxy(4, 14);
  printf("  ■      ■      ■  ■        ■            ■■      ");
  gotoxy(4, 15);
  printf("    ■■■          ■          ■■■■      ■  ■    ");
  gotoxy(4, 16);
  printf("                                                        ");
  gotoxy(32, 17);
  printf("空格键：重来\tEsc：退出");
  switch (getch())
  {
  case 32:
    system("cls"); //清屏
    console();
    my_print(); //输出界面
    my_randout();
    memset(scope, 0, sizeof(int) * 25 * 34); //数组清零
    fen = 0;
    hang = 0;
    pass = 1;
    break;
  case 27:
    my_exit();
    break;
  default:;
  }
}
void my_exit() //退出前保存最高分
{
  fp = fopen("test.txt", "w");
  fprintf(fp, "%d\n", max_fen);
  fclose(fp);
  exit(0);
}
