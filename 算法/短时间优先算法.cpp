#include<stdio.h>
#define N 10	//最大进程数
#define T 100	//最大时间长度
#define M 100	//最大队列数

int queue[M]={0};	//队列
int end=0;	//队尾

void queue_in(int i){	//入队
	queue[end++]=i;
}

int queue_out(int * serve){	//出队
		int s[M]={0};	//已入队进程的服务时间
		int min=M;	//服务时间最小值
		int min_no=0;	//服务时间最小值s序号
		int min_no_value=0;		//服务时间最小值的serve真实序号
		for(int i=0;i<end;i++){	//读取已入队进程的服务时间
			s[i]=serve[queue[i]];
		}
		for(i=0;i<end;i++){	//找出最小值和序号
			if(s[i]<min){
				min=s[i];
				min_no=i;
			}
		}
		min_no_value=queue[min_no];	//serve序号
		queue[min_no]=queue[end-1];	//把最后一个值换到即将出队的空间里
		end--;
		return min_no_value;
}

int queue_empty(){	//队空
	if(end==0)
		return 1;
	return 0;
}

void main(){
	int i,j;		//中间变量
	int n;			//进程数量
	int arrive[N];	//到达时间
	int serve[N];	//服务时间
	int serve_copy[N];	//服务时间拷贝
	int start[N];	//开始执行时间
	int finish[N];		//结束执行时间
	int interval[N];	//周转时间
	float interval_average[N];	//平均周转时间
	int running=-1;	//正在运行的进程序号
	int end_number=0;	//完成进程个数
	
	printf("短时间优先算法：\n\n请输入进程个数 ");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("请输入第 %d 个进程的 到达时间 和 服务时间 ",i);
		scanf("%d%d",&arrive[i],&serve[i]);
	}
	
	for(i=0;i<n;i++){	//拷贝服务时间
		serve_copy[i]=serve[i];
	}
	
	printf("\n运行顺序为：\n");
	for(i=0;i<T;i++){	//现在时间依次+1
		if(end_number==n){	//所有进程已完成
			break;	//退出循环
		}
		
		for(j=0;j<n;j++){	//查找到达进程
			if(arrive[j]==i){	//存在到达时间为现在时间的进程
				queue_in(j);	//放进队列
			}
		}
		
		if(queue_empty()==1&&running==-1){	//特殊情况，cpu有空闲
			printf("无 ");	//运行顺序
			continue;	//队列为空，没有正在运行的进程，并且还有进程未执行
		}
		
		if(running==-1){	//没有正在运行的进程
			running=queue_out(serve);	//队列取出
			start[running]=i;	//记录该进程开始时间
			printf("%d ",running);	//运行顺序
			serve_copy[running]--;	//服务时间--
			if(serve_copy[running]==0){	//特殊情况，该进程服务时间为1
				finish[running]=i+1;	//结束时间为当前时间+1
				running=-1;	//标记无进程在运行
				end_number++;	//完成进程+1
			}
		}else{	//进程正在运行
			printf("%d ",running);	//运行顺序
			serve_copy[running]--;	//服务时间--			
			if(serve_copy[running]==0){	//该进程已运行结束
				finish[running]=i+1;	//结束时间为当前时间+1
				running=-1;	//标记无进程在运行
				end_number++;	//完成进程+1
			}
		}
	}
	
	for(i=0;i<n;i++){	//计算周转和平均周转
		interval[i]=finish[i]-arrive[i];
		interval_average[i]=(float)interval[i]/serve[i];
	}
	
	printf("\n\n进程\t到达\t服务\t开始\t结束\t周转\t平均周转\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%.2f\n",i,arrive[i],serve[i],start[i],finish[i],interval[i],interval_average[i]);
	}
}