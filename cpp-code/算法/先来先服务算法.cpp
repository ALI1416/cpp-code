#include <stdio.h>

#define N 10  //最大进程数
#define T 100 //最大时间长度
#define M 100 //最大队列数

int queue[M] = {0}; //队列
int head = 0;       //队头
int end = 0;        //队尾

//入队
void queue_in(int i)
{
  queue[end++] = i;
}

//出队
int queue_out()
{
  return queue[head++];
}

//队空
int queue_empty()
{
  if (end == head)
    return 1;
  return 0;
}

void main()
{
  int i, j;                  //中间变量
  int n;                     //进程数量
  int arrive[N];             //到达时间
  int serve[N];              //服务时间
  int serve_copy[N];         //服务时间拷贝
  int start[N];              //开始执行时间
  int finish[N];             //结束执行时间
  int interval[N];           //周转时间
  float interval_average[N]; //平均周转时间
  int running = -1;          //正在运行的进程序号
  int end_number = 0;        //完成进程个数

  printf("先来先服务算法：\n\n请输入进程个数 ");
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    printf("请输入第 %d 个进程的 到达时间 和 服务时间 ", i);
    scanf("%d%d", &arrive[i], &serve[i]);
  }

  //拷贝服务时间
  for (i = 0; i < n; i++)
  {
    serve_copy[i] = serve[i];
  }
  printf("\n运行顺序为：\n");

  //现在时间依次+1
  for (i = 0; i < T; i++)
  {
    //所有进程已完成
    if (end_number == n)
    { //退出循环
      break;
    }

    //查找到达进程
    for (j = 0; j < n; j++)
    {
      //存在到达时间为现在时间的进程
      if (arrive[j] == i)
      { //放进队列
        queue_in(j);
      }
    }

    //特殊情况，cpu有空闲
    if (queue_empty() == 1 && running == -1)
    {
      //运行顺序
      printf("无 ");
      //队列为空，没有正在运行的进程，并且还有进程未执行
      continue;
    }

    //没有正在运行的进程
    if (running == -1)
    {
      running = queue_out();  //队列取出
      start[running] = i;     //记录该进程开始时间
      printf("%d ", running); //运行顺序
      serve_copy[running]--;  //服务时间--
      if (serve_copy[running] == 0)
      {                          //特殊情况，该进程服务时间为1
        finish[running] = i + 1; //结束时间为当前时间+1
        running = -1;            //标记无进程在运行
        end_number++;            //完成进程+1
      }
    }
    else
    {                         //进程正在运行
      printf("%d ", running); //运行顺序
      serve_copy[running]--;  //服务时间--
      if (serve_copy[running] == 0)
      {                          //该进程已运行结束
        finish[running] = i + 1; //结束时间为当前时间+1
        running = -1;            //标记无进程在运行
        end_number++;            //完成进程+1
      }
    }
  }

  //计算周转和平均周转
  for (i = 0; i < n; i++)
  {
    interval[i] = finish[i] - arrive[i];
    interval_average[i] = (float)interval[i] / serve[i];
  }

  printf("\n\n进程\t到达\t服务\t开始\t结束\t周转\t平均周转\n");
  for (i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%.2f\n", i, arrive[i], serve[i], start[i], finish[i], interval[i], interval_average[i]);
  }
}
