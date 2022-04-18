#include <stdio.h>  
#include <stdlib.h>  
#include <malloc.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int QElemType;  
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
    Q->base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
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
    *e=*(Q.base+Q.front);
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
        printf("%d ",S.base[i]);
    printf("\n");
}
int main()
{
    SqQueue s;
    int i=0,p,q;
    if(!InitQueue(&s))
        return ERROR;
    while(i!=-1)
    {
        scanf("%d",&i);
        if(i!=-1)
            EnQueue(&s,i);
    }
    scanf("%d",&p);
    scanf("%d",&q);
    PrintQueue(s);
    printf("%d\n",QueueLength(s));
    EnQueue(&s,p);
    PrintQueue(s);
    for(i=0;i<q;i++)
        DeQueue(&s,&p);
    PrintQueue(s);
}