#include <stdio.h>

#define N 100 //进程最大数量
#define M 10  //物理块最大数量

int n = 20;                                                                 //实际进程数量
int m = 3;                                                                  //实际物理块数量
int page[N] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}; //页面号
int miss[N];                                                                //是否缺页
int map[N][M];                                                              //置换图
int i, j, k;                                                                //局部变量

void scan()
{
  printf("请输入物理块数量 ");
  scanf("%d", &m);
  printf("请输入进程页面号，-1结束输入\n");
  for (i = 0; i < N; i++)
  {
    scanf("%d", &k);
    if (k != -1)
    {
      page[i] = k;
    }
    else
    {
      n = i;
      break;
    }
  }
}

void init()
{
  //初始化map
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m; j++)
    {
      map[i][j] = -1;
    }
  }
  //初始化miss
  for (i = 0; i < n; i++)
  {
    miss[i] = 0;
  }
}

void input(int x, int i, int j, int num_v)
{
  // x=0 fifo算法 输入i,num_v (队首出队,num_v入队)
  // x=1  lru算法 输入i,j (序号j出队，map[i][j]入队)
  int num;
  //计算已使用的物理块数量
  for (k = 0; k < m; k++)
  {
    if (map[i][k] == -1)
    {
      num = k - 1;
      break;
    }
    else
    {
      num = m - 1;
    }
  }
  // fifo
  if (x == 0)
  {
    //替换
    for (k = 0; k < num; k++)
    {
      map[i][k] = map[i][k + 1];
    }
  }
  else
  {                    // lru
    num_v = map[i][j]; //保存该页面号
    for (k = j; k < num; k++)
    { //替换
      map[i][k] = map[i][k + 1];
    }
  }
  map[i][num] = num_v; //把该页面号放到队尾
}

void fifo_lru(int x)
{
  // x=0 fifo
  // x=1 lru
  int find, num, num_v;
  for (i = 0; i < n; i++)
  {
    find = 0;
    //第一遍 寻找存在的页面号
    for (j = 0; j < m; j++)
    {
      //查找到空闲物理块 结束查找
      if (map[i][j] == -1)
      {
        break;
      }
      //找到相同物理块
      if (map[i][j] == page[i])
      {
        find = 1;
        //如果为lru算法
        if (x == 1)
          input(1, i, j, 0);
        break;
      }
    }
    if (find == 0)
    {
      //第二遍 寻找空闲物理块
      for (j = 0; j < m; j++)
      {
        if (map[i][j] == -1)
        {
          map[i][j] = page[i]; //找到
          find = 1;
          miss[i] = 1; //标记为缺页
          break;
        }
      }
      if (find == 0)
      {
        input(0, i, 0, page[i]); // fifo&lru
        miss[i] = 1;             //标记为缺页
      }
    }
    //复制当前页面号map到下一个
    for (j = 0; j < m; j++)
    {
      map[i + 1][j] = map[i][j];
    }
  }
}

void print()
{
  int miss_num = 0;
  printf("进程页面号为：\n");
  for (i = 0; i < n; i++)
  {
    printf("%4d", page[i]);
  }
  printf("\n置换图为：\n");
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < n; j++)
    {
      printf("%4d", map[j][i]);
    }
    printf("\n");
  }
  for (i = 0; i < n; i++)
  {
    if (miss[i] == 1)
    {
      miss_num++;
      printf("  缺");
    }
    else
      printf("    ");
  }
  printf("\n");
  printf("缺页 %d 次，缺页率 %.2f %%\n", miss_num, miss_num / (float)n * 100);
}

void main()
{
  int def;
  printf("输入0使用默认数据，输入1手动输入数据");
  scanf("%d", &def);
  if (def != 0)
    scan();

  printf("总共 %d 个进程，有 %d 个物理块\n", n, m);
  printf("\n先来先服务算法(FIFO)\n");
  init();
  fifo_lru(0);
  print();

  printf("\n最近最久未使用算法(LRU)\n");
  init();
  fifo_lru(1);
  print();
}
