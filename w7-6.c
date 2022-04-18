#include <stdio.h>  
#include <stdlib.h>  
#include <malloc.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef struct
{
    char name;    //元素名称
    int arriveTime;  //到达时间
}QElemType;
typedef int Status;
#define MAXQSIZE  100   // maximum length
typedef struct 
{
   QElemType *base;   //pointer the allocated memory
   int front;                    //front indicator
   int rear;                     //rear indicator
}SqQueue;
Status InitQueue (SqQueue *Q)
{   
    Q->base=(QElemType *)malloc(MAXQSIZE*sizeof(SqQueue));
    if(!Q->base)
        return ERROR;
    Q->front=Q->rear=0;
    return OK;
}
Status QueueEmpty (SqQueue Q)
{
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}
int QueueLength (SqQueue Q)
{
    return ((Q.rear-Q.front+MAXQSIZE)%MAXQSIZE);
}
Status GetHead (SqQueue Q, QElemType *e)
{
    if(Q.front==Q.rear)
        return ERROR;
    *e=Q.base[Q.front];
    return OK;
}
Status DeQueue(SqQueue *Q,QElemType *e)
{
    if(Q->front==Q->rear)
        return ERROR;
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAXQSIZE;
    return OK;
}
Status EnQueue (SqQueue *Q, QElemType e)
{
    if((Q->rear+1)%MAXQSIZE==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXQSIZE;
    return OK;
}
Status ClearQueue (SqQueue *Q)
{
    Q->front=Q->rear=0;
    return OK;
}
void PrintQueue (SqQueue S)
{
    int i;
    for(i=S.front;i<S.rear;i=(i+1)%MAXQSIZE)
        printf("(%c,%d)\n",S.base[i].name,S.base[i].arriveTime);
}
void mergeQueue(SqQueue Q1, SqQueue Q2, SqQueue *Q3)
{
    QElemType e;
    while((Q1.front!=Q1.rear)&&(Q2.front!=Q2.rear))
    {
        if(Q1.base[Q1.front].arriveTime<=Q2.base[Q2.front].arriveTime)
        {   
            DeQueue(&Q1,&e);
            EnQueue(Q3,e);
        }
        else 
        {
            DeQueue(&Q2,&e);
            EnQueue(Q3,e);
        }
    }
    while(Q1.front!=Q1.rear)
    {
        DeQueue(&Q1,&e);
        EnQueue(Q3,e);
    }
    while(Q2.front!=Q2.rear)
    {
        DeQueue(&Q2,&e);
        EnQueue(Q3,e);
    }
    free(Q2.base);
    free(Q1.base);
}
int main()
{
    int i,n;
    SqQueue q1,q2,q3;
    if(!InitQueue(&q1)||!InitQueue(&q2)||!InitQueue(&q3))
        return ERROR;
    scanf("%d",&n);
    QElemType a;
    for(i=0;i<n;i++)
    {
        getchar();
        scanf("%c %d",&a.name,&a.arriveTime);
        EnQueue(&q1,a);
    }
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        getchar();
        scanf("%c %d",&a.name,&a.arriveTime);
        EnQueue(&q2,a);
    }
    mergeQueue(q1,q2,&q3);
    printf("%d\n",QueueLength(q3));
    PrintQueue(q3);
}