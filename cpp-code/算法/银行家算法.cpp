#include <stdio.h>
#include <stdlib.h>

#define P 10 //最大进程数
#define R 5  //最大资源种类

int p = 0; //实际进程数
int r = 0; //实际资源种类
int i, j;  //临时变量

int max[P][R] = {0};               //最大需求
int allocation[P][R] = {0};        //已分配
int need[P][R] = {0};              //还需
int available[P][R] = {0};         //可利用
int work[P][R] = {0};              //工作
int workAndAllocation[P][R] = {0}; //工作+可利用
int finish[P] = {0};               //完成顺序
int resourceMax[R] = {0};          //资源总量
int resource[R] = {0};             //资源当前剩余量
int finishCount = 0;               //当前已完成进程个数

int openFile()
{

  FILE *fp = fopen("data.txt", "r");
  //文件不存在
  if (fp == NULL)
  {
    fp = fopen("data.txt", "w"); //新建文件
    fprintf(fp, "5 3\n7 5 3 0 1 0\n3 2 2 2 0 0\n9 0 2 3 0 2\n2 2 2 2 1 1\n4 3 3 0 0 2\n10 5 7\n");
    fclose(fp);
    printf("输入格式：\n第一行：进程数量 资源种类\n第二行：进程0的最大需求、已分配资源，按照资源种类依次写出。\n第三行，进程1的...以此类推。最后一行：各类资源的总量。\n示例内容已写入，请重新写入数据，保存文件后再次运行此程序。\n");
    system("start data.txt"); //打开TXT文件
    return 0;
  }
  else
  {                              //文件存在
    fscanf(fp, "%d %d", &p, &r); //读取实际进程p和资源r

    //导入最大需求max和已分配allocation
    for (i = 0; i < p; i++)
    {
      for (j = 0; j < r; j++)
      {
        fscanf(fp, "%d ", &max[i][j]);
      }
      for (j = 0; j < r; j++)
      {
        fscanf(fp, "%d ", &allocation[i][j]);
      }
    }

    //导入最大资源量resourceMax
    for (i = 0; i < r; i++)
    {
      fscanf(fp, "%d ", &resourceMax[i]);
    }

    //计算还需need
    for (i = 0; i < p; i++)
    {
      for (j = 0; j < r; j++)
      {
        need[i][j] = max[i][j] - allocation[i][j];
      }
    }

    //计算资源当前剩余量resource
    for (i = 0; i < r; i++)
    {
      resource[i] = resourceMax[i];
      for (j = 0; j < p; j++)
      {
        resource[i] -= allocation[j][i];
      }
    }
  }
  fclose(fp);
  return 1;
}

void showInit()
{
  printf("进程总数 %d 个，资源类型 %d 个(最大数量为 ", p, r);
  for (i = 0; i < r; i++)
  {
    printf("%d ", resourceMax[i]);
  }
  printf("，剩余数量为 ");
  for (i = 0; i < r; i++)
  {
    printf("%d ", resource[i]);
  }
  printf(")\n\n初始状态为：\n\n| 进程  |  最大需求  |   已分配   |    还需    |\n");
  for (i = 0; i < p; i++)
  {
    printf("|  P%-4d|", i);
    for (j = 0; j < r; j++)
    {
      printf("%3d ", max[i][j]);
    }
    printf("|");
    for (j = 0; j < r; j++)
    {
      printf("%3d ", allocation[i][j]);
    }
    printf("|");
    for (j = 0; j < r; j++)
    {
      printf("%3d ", need[i][j]);
    }
    printf("|\n");
  }
}

void showEnd()
{
  int order[P] = {0}; //执行顺序
  int temp;           //中间变量
  temp = finishCount; //记录完成进程数量

  //计算执行顺序
  for (i = 0; i < p; i++)
  {
    for (j = 0; j < p; j++)
    {
      if (finish[j] == i + 1)
      {               //无死锁
        order[i] = j; //保存序号到头部
        break;
      }
    }
    if (finish[i] == 0)
    {                    //死锁
      order[temp++] = i; //保存序号到尾部
      for (j = 0; j < r; j++)
      { //设置工作资源work为当前资源
        work[i][j] = resource[j];
      }
    }
  }
  printf("\n计算结果如下：\n\n");
  printf("| 进程  |  工作资源  |    还需    |   已分配   |   可利用   |  完成顺序  |\n");
  for (i = 0; i < p; i++)
  {
    temp = i;
    i = order[i];
    if (finish[i] == 0)
    {
      printf("--------------------------------------------------------------------------\n");
    }
    printf("|  P%-4d|", i);
    for (j = 0; j < r; j++)
    {
      printf("%3d ", work[i][j]);
    }
    printf("|");
    for (j = 0; j < r; j++)
    {
      printf("%3d ", need[i][j]);
    }
    printf("|");
    for (j = 0; j < r; j++)
    {
      printf("%3d ", allocation[i][j]);
    }
    printf("|");
    for (j = 0; j < r; j++)
    {
      printf("%3d ", workAndAllocation[i][j]);
    }
    printf("|");
    printf("%7d     ", finish[i]);
    printf("|\n");
    i = temp;
  }
  if (finishCount == 5)
  {
    printf("\n无死锁，执行顺序为");
    for (i = 0; i < p; i++)
    {
      printf("P%d ", order[i]);
    }
    printf("\n");
  }
  else
  {
    printf("\n存在死锁。其中完成顺序为0的为死锁进程。\n");
  }
}

//递归实现
//-1，未找到
//其他，找到
void compute(int find)
{
  int flag;
  //未找到
  if (find == -1)
  {
    for (i = 0; i < p; i++)
    {
      //只查询未完成的
      if (finish[i] == 0)
      {
        //查询每个资源
        for (j = 0; j < r; j++)
        {
          //需求资源大于剩余资源，去除
          if (need[i][j] > resource[j])
          {
            flag = 0; //标记不满足条件
            break;    //中断j循环，有一个资源不足，立即中断
          }           // r次判断都可用，执行下面语句
          flag = 1;   //标记满足条件
        }
        if (flag == 1)
        {
          find = i;      //找到可满足进程
          compute(find); //递归
          break;         //中断i循环，只取第一个结果
        }
      }
    }
  }
  else
  {           //找到
    i = find; //替换
    //计算工作work，可利用workAndAllocation，资源当前剩余量resource
    for (j = 0; j < r; j++)
    {
      work[i][j] = resource[j];
      workAndAllocation[i][j] = work[i][j] + allocation[i][j];
      resource[j] = workAndAllocation[i][j];
    }
    finish[i] = ++finishCount; //标记执行顺序，从1开始，0为未执行
    compute(-1);               //递归
  }
}

//初始化导入文件
void initFile()
{
  finishCount = 0; //初始化完成个数finishCount
  //初始化完成顺序finish
  for (i = 0; i < p; i++)
  {
    finish[i] = 0;
  }
  //初始化资源当前剩余量resource
  for (i = 0; i < r; i++)
  {
    resource[i] = resourceMax[i];
    for (j = 0; j < p; j++)
    {
      resource[i] -= allocation[j][i];
    }
  }
}

//请求资源
int request()
{
  int pro;    //进程
  int num[R]; //数量
  printf("请输入要申请资源的进程：");
  scanf("%d", &pro);
  //进程不存在
  if (pro >= p)
  {
    printf("错误：不存在该进程！\n");
    return -1;
  }
  printf("请输入申请资源的个数：");
  for (i = 0; i < r; i++)
  {
    scanf("%d", &num[i]);
  }
  //超额资源申请
  for (i = 0; i < r; i++)
  {
    if (num[i] > need[pro][i])
    {
      printf("错误：超额资源申请！\n");
      return -1;
    }
  }
  //剩余资源不足
  for (i = 0; i < r; i++)
  {
    if (num[i] > resource[i])
    {
      printf("错误：剩余资源不足！\n");
      return -1;
    }
  }
  //替换还需资源
  for (i = 0; i < r; i++)
  {
    need[pro][i] = num[i];
  }
  return pro;
}

void main()
{
  printf("银行家算法\n\n");
  if (openFile() == 1)
  {
    showInit();
    printf("--------------------------------------------------------------------------\n");
    printf("判断当前系统是否死锁\n");
    compute(-1);
    showEnd();
    printf("--------------------------------------------------------------------------\n");
    printf("判断进程申请资源后是否死锁\n");
    initFile();
    int progress = request();
    if (progress != -1)
    {
      compute(progress);
      showEnd();
    }
  }
}
