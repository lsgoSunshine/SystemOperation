#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


typedef struct PCB  
{  
    int ID;                         //标识符 
	char name;                     //名字 
    double Level;                   //优先级  
    int ComeTime;                   //到达时间  
    int ServerTime;                 //服务时间  
    int FinishTime;                 //完成时间  
    int TurnoverTime;               //周转时间  
    double WeightedTurnoverTime;    //带权周转时间  
} PCB;  

typedef struct Node{
	PCB *data;
	struct Node *next;
} Node;
typedef struct Node *List;





//添加PCB 
PCB * InsertPCB(char name,int ComeTime,int ServerTime){
	PCB *p=(PCB*)malloc(sizeof(PCB));
	//p->name=name;
	p->name=name;
	p->ComeTime=ComeTime;
	p->ServerTime=ServerTime;
	return p;
} 


//添加节点 
void InsertNode(PCB *p,List *PList){
	Node *current=*PList;
	Node *temp=(Node*)malloc(sizeof(Node));
	temp->data=p;
	temp->next=NULL;
	if(*PList==NULL){
		*PList=temp;
	}else{
		while(current->next!=NULL){
			current=current->next;
		}
		current->next=temp;
	}
		
} 
//删除节点 
bool DelectNode(List * PList,Node *node){
	Node *current = *PList;
	if(current->data->name==node->data->name){
		*PList=node->next;
		free(node);
		return true; 
	}
	while(current->next!=NULL){
		
		if(current->next->data->name==node->data->name){
			current->next=node->next;
			free(node);
			return true;	
		}
		free(node);
	}
}