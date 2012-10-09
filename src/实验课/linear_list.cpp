/*
 * 线性表实验
 */
#include <iostream.h>
#include "stdio.h"
#include <malloc.h>
#include <conio.h>
#define MAXSIZE 100
typedef int DataType;

typedef struct 
{
  DataType data[MAXSIZE];
  int length;
} SeqList,* PSeqList;

//初始化顺序表
PSeqList Init_SeqList(void){
	PSeqList p;
	p=(PSeqList)malloc(sizeof(SeqList));
	if (p)  
		p->length=0;
	return p;
}

//销毁顺序表
void  Destroy_SeqList(PSeqList *p){
	if (*p)  
		free(*p);
	*p=NULL;
}

//定位元素
int Location_SeqList(PSeqList p,DataType x){
	int i=0;
	if (p->length == 0) {
		printf("表不存在\n");
		return -1;
	}
	while(i < p->length && p->data[i] != x)
		i++;
	if(i >= p->length)
		return 0;
	else
		return i+1;
}

//插入
int Insert_SeqList(PSeqList p, int i, DataType x){	
	if (!p) {
		printf("表不存在\n");
		return -2;
	} 
	if (p->length>=MAXSIZE) {    /*空间已满*/
		printf("溢出错！表空间已满\n");
		return -1;
	}	
	if (i < 1 || i > p->length+1) {
		/*位置不合理*/
		printf("插入位置不合理\n");		
		return(0);
	}
	int j;
	for (j = p->length-1; j >= i-1; j--) 
		p->data[j+1]= p->data[j];
	/*向后移动元素*/
	p->data[i-1]=x;        /*插入元素*/
	p->length++;            /*表长度加1*/
	return  1 ;	
}

//删除
int Delete_SeqList(PSeqList p, int i){
	if (!p) {
		/*表不存在*/
		printf("表不存在\n");
		return -1;
	} 
	if (i<1||i>p->length) {
		/*位置不合理*/
		//printf("删除位置不合理\n");		
		return(0);
	}         
	int j;
	for (j=i;j<p->length;j++)	
		p->data[j-1]= p->data[j];
		/*向前移动元素*/	
    p->length--;		 /*长度减1 */
    return  1;
}

//翻转表
void Reverse_SeqList(PSeqList p){
	int i,j;
    DataType x;
    for(i=0,j=p->length-1; i<j;  i++,j--) {
		x=p->data[i];
		p->data[i]=p->data[j];
		p->data[j] =x;
	}
}

//合并两个有序表
void Merge_SeqList(PSeqList La, PSeqList Lb, PSeqList Lc){
    int i=0,j=0,k=0;
	if(!Lc) {
       printf("Lc表不存在\n");
       return;
	}
    if(La->length+Lb->length>=MAXSIZE) {   
		printf("Lc表空间不足\n");
		return ;
	}
	while((i<La->length)&&(j<=Lb->length)){
         if(La->data[i]<=Lb->data[j])  
		      Lc->data[k++]=La->data[i++];
         else
			 Lc->data[k++]=Lb->data[j++];
	}
	while (i<La->length) 
         Lc->data[k++]=La->data[i++]; 
		//插入La中剩余元素
	while(j<Lb->length) 
	     Lc->data[k++]=Lb->data[j++]; 
		//插入Lb中剩余元素
	Lc->length=k;
}

//求两个表的并集
void Union_SeqList(PSeqList La, PSeqList Lb, PSeqList Lc){
	int i=0,j=0,k=0;
	if(!Lc) {
       printf("Lc表不存在\n");
       return;
	}
	//清空 Lc
	if(Lc->length > 0) {
		for(i = Lc->length; i>=0; i--)
			Delete_SeqList(Lc,i);
	}
	// Lc = La
	for(i = 0; i < La->length; i++)
		Lc->data[i] = La->data[i];
	// handle Lb
	j = Lc->length = La->length;
	for(i = 0; i < Lb->length; i++) {
		if(Location_SeqList(La, Lb->data[i])) {
			continue;
		} else {
			Lc->data[j] = Lb->data[i];
			j++;
			Lc->length++;
		}
	}
}

//打印表中元素值
void PrintList(PSeqList L)
{
	int i;
	for(i=0;i<L->length;i++)
		cout<<L->data[i]<<ends;
	cout<<endl;
}

//主函数
void main()
{
	  PSeqList La,Lb,Lc;
	  int i;
	  cout<<"\n\n-------------------List Demo is running...----------------\n\n";
	  cout<<"First is InsertList function. "<<endl;
	  //创建第一个表
	  La=Init_SeqList();
	  cout<<endl<<"往La表中插入五个元素｛1,2,3,4,5｝"<<endl;
	  for(i=1;i<=5;i++)
		 Insert_SeqList(La,i,i);
	  PrintList(La);
	  cout<<"List A length now is "<<La->length<<endl;
	  getch();  //屏幕暂停，等候按任何键继续
	  //创建第二个表
	  Lb=Init_SeqList();
	  cout<<endl<<"往Lb表中插入五个元素｛1,3,5,7,9｝"<<endl;
	  for(i=1;i<=5;i++)
		Insert_SeqList(Lb,i,2*i-1);
	  PrintList(Lb);
	  cout<<"List B length now is "<<Lb->length<<endl;
	  getch();

	  //合并有序表
	  cout<<endl<<"合并表 La 和 Lb.....\n";
	  Lc=Init_SeqList();
	  Merge_SeqList(La,Lb,Lc);
	  if(!Lc) return;
	  PrintList(Lc);
	  cout<<"List A length now is "<<Lc->length<<endl;
	  getch();

	  //翻转表
	  cout<<endl<<"翻转Lc表"<<endl;
	  Reverse_SeqList(Lc);
	  PrintList(Lc);
	  getch();

	  //求并集
	  cout<<endl<<"求并集"<<endl;
      Union_SeqList(La,Lb,Lc);
	  PrintList(Lc);
	  cout<<"List C length now is "<<Lc->length<<endl;
	  getch();

	  Destroy_SeqList(&La);
	  Destroy_SeqList(&Lb);
	  Destroy_SeqList(&Lc);
}