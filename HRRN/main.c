#include <stdio.h>
#include <stdbool.h>
#include "list.c"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//插入数据 
void insert();
//计算优先级 
void GetPriority(List * PList,int time);
int HRRN(List * PList);
int main(int argc, char** argv) {
	List * PList;
	* PList=NULL;
	insert(PList);
	HRRN(PList);
	return 0;
}
//插入数据 
void insert(List * PList){
	PCB * P;
		do{
		char name;
		int comeTime;
		int severTime;
		char judge;
		
		printf("%s","\n请输入进程名\n");
		scanf("%c",&name);
		printf("%s","请输入进程到达时间\n");
		scanf("%d",&comeTime);
		printf("%s","请输入进程服务时间\n") ; 
		scanf("%d",&severTime);
		P=InsertPCB(name,comeTime,severTime);
		InsertNode(P,PList);
		while(getchar()!='\n') 
			continue;
		printf("%s","还需输入进程吗 y/n\n"); 
		scanf("%c",&judge);
		while(getchar()!='\n') 
			continue;
		if(judge=='n'){
			//printf("yes");
			break;
		}else{
			//printf("no");
			continue;
		}
	}while(true);
} 
// 高响应比算法 
int HRRN(List * PList){
	int time=0;
	Node * temp;
	temp=*PList;
	Node * current;
	current=*PList;	
	while((*PList)->next != NULL){
		
		if(time==0){                                //初始时只需要比较到达时间即可 
			while(current->next	!=NULL){
				current=current->next;
				//先来先服务 
				if(temp->data->ComeTime>current->data->ComeTime)
					temp=current;
				//同时到达，短作业优先	
				else if(temp->data->ComeTime==current->data->ComeTime&&temp->data->ServerTime>current->data->ServerTime)
					temp=current;				
			}
			
			printf("进程名:%c\n",temp->data->name);
			printf("到达时间:%d\n",time);
			printf("服务时间:%d\n",temp->data->ServerTime);
			time=temp->data->ComeTime+temp->data->ServerTime;
			DelectNode(PList,temp);	
		}else{
			while(current->next	!=NULL){
	 			current=current->next; 
	 			//优先权高的先服务 
		 		if(temp->data->Level<current->data->Level)
			 		temp=current;
		 		//相同优先权 先来先服务 
				 else if(temp->data->Level==current->data->Level&&temp->data->ComeTime>current->data->ComeTime)
				 	temp=current;
 			}
 			
			printf("\n进程名:%c\n",temp->data->name);
			printf("到达时间:%d\n",time);
			printf("服务时间:%d\n",temp->data->ServerTime);
			time = time+temp->data->ServerTime;
			DelectNode(PList,temp);  
		} 
		GetPriority(PList,time);
		temp = current = * PList;		
	}
	printf("进程名:%c\n",temp->data->name);
	printf("到达时间:%d\n",time);
	printf("服务时间:%d\n",temp->data->ServerTime);
	time=temp->data->ComeTime+temp->data->ServerTime;
	DelectNode(PList,temp);	
}
void GetPriority(List * PList,int time){
	Node * current;
	current=*PList;
	while (current->next!=NULL){
		if(current->data->ComeTime<=time){
			current->data->Level=1+(double)(time-current->data->ComeTime)/(double)(current->data->ServerTime);
			
		}else{
			current->data->Level=0.0;
		}
		current=current->next;
		
	} 
		if(current->data->ComeTime<=time){
			current->data->Level=1+(double)(time-current->data->ComeTime)/(double)(current->data->ServerTime);
			current=current->next;
		}else{
			current->data->Level=0.0;
		} 
} 
