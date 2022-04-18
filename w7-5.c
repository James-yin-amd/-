#include <stdio.h>  
#include <stdlib.h>  
#include <malloc.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef struct 
{
    char name;
    int arrivetime;
}QElemType;
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
}
Status QueueEmpty (LinkQueue Q)
{
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}
int QueueLength (LinkQueue Q)
{
    QueuePtr p;
    p=Q.front->next;
    int i=0;
    while(p)
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
        printf("(%c,%d)\n",p->data.name,p->data.arrivetime);
        p=p->next;
    }
    return OK;
}
void mergeQueue(LinkQueue Q1,LinkQueue Q2,LinkQueue *Q3)
{
    QueuePtr pa,pb,pc;
    pa=Q1.front->next;
    pb=Q2.front->next;
    pc=Q3->front=Q1.front;
    while(pa&&pb)
    {
        if(pa->data.arrivetime<=pb->data.arrivetime)
        {
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else if(pa->data.arrivetime>pb->data.arrivetime)
        {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
    if(pb)
    {
        pc->next=pb;
        Q3->rear=Q2.rear;
    }
    else if(pa)
    {
        pc->next=pa;
        Q3->rear=Q1.rear;
    }
    free(Q2.front);
}
int main()
{
    LinkQueue q1,q2,q3;
    if((!InitQueue(&q1))||(!InitQueue(&q2))||(!InitQueue(&q3)))
        return ERROR;
    int n,i;
    QElemType a,b;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        getchar();
        scanf("%c %d",&a.name,&a.arrivetime);
        EnQueue(&q1,a);
    }
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        getchar();
        scanf("%c %d",&b.name,&b.arrivetime);
        EnQueue(&q2,b);
    }
    mergeQueue(q1,q2,&q3);
    printf("%d\n",QueueLength(q3));
    PrintQueue(q3);
}