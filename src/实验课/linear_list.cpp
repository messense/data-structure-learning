/*
 * ���Ա�ʵ��
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

//��ʼ��˳���
PSeqList Init_SeqList(void){
	PSeqList p;
	p=(PSeqList)malloc(sizeof(SeqList));
	if (p)  
		p->length=0;
	return p;
}

//����˳���
void  Destroy_SeqList(PSeqList *p){
	if (*p)  
		free(*p);
	*p=NULL;
}

//��λԪ��
int Location_SeqList(PSeqList p,DataType x){
	int i=0;
	if (p->length == 0) {
		printf("������\n");
		return -1;
	}
	while(i < p->length && p->data[i] != x)
		i++;
	if(i >= p->length)
		return 0;
	else
		return i+1;
}

//����
int Insert_SeqList(PSeqList p, int i, DataType x){	
	if (!p) {
		printf("������\n");
		return -2;
	} 
	if (p->length>=MAXSIZE) {    /*�ռ�����*/
		printf("�������ռ�����\n");
		return -1;
	}	
	if (i < 1 || i > p->length+1) {
		/*λ�ò�����*/
		printf("����λ�ò�����\n");		
		return(0);
	}
	int j;
	for (j = p->length-1; j >= i-1; j--) 
		p->data[j+1]= p->data[j];
	/*����ƶ�Ԫ��*/
	p->data[i-1]=x;        /*����Ԫ��*/
	p->length++;            /*���ȼ�1*/
	return  1 ;	
}

//ɾ��
int Delete_SeqList(PSeqList p, int i){
	if (!p) {
		/*������*/
		printf("������\n");
		return -1;
	} 
	if (i<1||i>p->length) {
		/*λ�ò�����*/
		//printf("ɾ��λ�ò�����\n");		
		return(0);
	}         
	int j;
	for (j=i;j<p->length;j++)	
		p->data[j-1]= p->data[j];
		/*��ǰ�ƶ�Ԫ��*/	
    p->length--;		 /*���ȼ�1 */
    return  1;
}

//��ת��
void Reverse_SeqList(PSeqList p){
	int i,j;
    DataType x;
    for(i=0,j=p->length-1; i<j;  i++,j--) {
		x=p->data[i];
		p->data[i]=p->data[j];
		p->data[j] =x;
	}
}

//�ϲ����������
void Merge_SeqList(PSeqList La, PSeqList Lb, PSeqList Lc){
    int i=0,j=0,k=0;
	if(!Lc) {
       printf("Lc������\n");
       return;
	}
    if(La->length+Lb->length>=MAXSIZE) {   
		printf("Lc��ռ䲻��\n");
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
		//����La��ʣ��Ԫ��
	while(j<Lb->length) 
	     Lc->data[k++]=Lb->data[j++]; 
		//����Lb��ʣ��Ԫ��
	Lc->length=k;
}

//��������Ĳ���
void Union_SeqList(PSeqList La, PSeqList Lb, PSeqList Lc){
	int i=0,j=0,k=0;
	if(!Lc) {
       printf("Lc������\n");
       return;
	}
	//��� Lc
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

//��ӡ����Ԫ��ֵ
void PrintList(PSeqList L)
{
	int i;
	for(i=0;i<L->length;i++)
		cout<<L->data[i]<<ends;
	cout<<endl;
}

//������
void main()
{
	  PSeqList La,Lb,Lc;
	  int i;
	  cout<<"\n\n-------------------List Demo is running...----------------\n\n";
	  cout<<"First is InsertList function. "<<endl;
	  //������һ����
	  La=Init_SeqList();
	  cout<<endl<<"��La���в������Ԫ�أ�1,2,3,4,5��"<<endl;
	  for(i=1;i<=5;i++)
		 Insert_SeqList(La,i,i);
	  PrintList(La);
	  cout<<"List A length now is "<<La->length<<endl;
	  getch();  //��Ļ��ͣ���Ⱥ��κμ�����
	  //�����ڶ�����
	  Lb=Init_SeqList();
	  cout<<endl<<"��Lb���в������Ԫ�أ�1,3,5,7,9��"<<endl;
	  for(i=1;i<=5;i++)
		Insert_SeqList(Lb,i,2*i-1);
	  PrintList(Lb);
	  cout<<"List B length now is "<<Lb->length<<endl;
	  getch();

	  //�ϲ������
	  cout<<endl<<"�ϲ��� La �� Lb.....\n";
	  Lc=Init_SeqList();
	  Merge_SeqList(La,Lb,Lc);
	  if(!Lc) return;
	  PrintList(Lc);
	  cout<<"List A length now is "<<Lc->length<<endl;
	  getch();

	  //��ת��
	  cout<<endl<<"��תLc��"<<endl;
	  Reverse_SeqList(Lc);
	  PrintList(Lc);
	  getch();

	  //�󲢼�
	  cout<<endl<<"�󲢼�"<<endl;
      Union_SeqList(La,Lb,Lc);
	  PrintList(Lc);
	  cout<<"List C length now is "<<Lc->length<<endl;
	  getch();

	  Destroy_SeqList(&La);
	  Destroy_SeqList(&Lb);
	  Destroy_SeqList(&Lc);
}