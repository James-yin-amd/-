#include <stdio.h>  
#include <stdlib.h>  
#include <malloc.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int QElemType;  
typedef int Status;
typedef struct Qnode
{
    QElemType   data;
    struct Qnode  *next;
}QNode, *QueuePtr;
typedef struct
{
    QueuePtr front;  //front pointer
    QueuePtr rear;   //rear pointer
}LinkQueue; 
Status InitQueue(LinkQueue *Q)
{
    Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        return ERROR;
    Q->front->next=NULL;
    return OK;
}/*初始化链队列*/
Status QueueEmpty (LinkQueue Q)
{
    if(Q.front==Q.rear)
        return TRUE;
    else 
        return FALSE;
}/*判空*/
int QueueLength (LinkQueue Q)
{
    QueuePtr p;
    p=Q.front->next;
    int i=0;
    while(p!=Q.rear)
    {
        i++;
        p=p->next;
    }
    return i;
}
Status GetHead (LinkQueue Q, QElemType *e)
{
    QueuePtr p;
    p=Q.front->next;
    if(!p)
        return ERROR;
    *e=p->data;
    return OK;
}
Status DeQueue(LinkQueue *Q, QElemType *e)
{
    QueuePtr p;
    p=Q->front->next;
    if(!p)
        return ERROR;
    *e=p->data;
    Q->front->next=p->next;
    if(Q->rear==p)
        Q->rear=Q->front;
    free(p);
    return OK;
}
Status EnQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr p;
    p=(QueuePtr)malloc(sizeof(QNode));
    if(!p)
        return ERROR;
    p->data=e;
    p->next=NULL;
    Q->rear->next=p;
    Q->rear=p;
    return OK;
}
int PrintQueue (LinkQueue S)
{
    QueuePtr p;
    p=S.front->next;
    if(!p)
        return ERROR;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}
void PrintYangHuiTriangle(int N)
{
    LinkQueue s;
    InitQueue(&s);
    EnQueue(&s,1);
    int n,i,temp,x;
    for(n=2;n<=N;n++)
    {
        EnQueue(&s,1);
        for(i=1;i<=n-2;i++)
        {
            DeQueue(&s,&temp);
            GetHead(s,&x);
            temp=temp+x;
            EnQueue(&s,temp);
        }
        DeQueue(&s,&temp);
        EnQueue(&s,1);
    }
    while(!QueueEmpty(s))
    {
        DeQueue(&s,&x);
        printf("%d ",x);
    }
    printf("\n");
}
int main()
{
    int n;
    scanf("%d",&n);
    PrintYangHuiTriangle(n);
}