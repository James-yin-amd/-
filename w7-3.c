#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAXQSIZE  100
typedef char SElemType;
typedef char QElemType;
typedef int Status;
typedef struct L_node
{
    SElemType data;  //data field
    struct L_node *next;   //pointer field
}LNode, *LinkList;
typedef struct
{
   LinkList  Head;  //head pointer
   int  length;  //length
}LinkStack;
Status InitStack(LinkStack *S)
{
    S->Head=(LinkList)malloc(sizeof(LNode));
    if(!S->Head)
        return ERROR;
    S->length=0;
    S->Head->next=NULL;
    return OK;
}
Status StackEmpty (LinkStack S)
{
    if(S.Head->next==NULL)
        return TRUE;
    else
        return FALSE;
}/*判空*/
int StackLength (LinkStack S)
{
    return S.length;
}/*长度*/
Status GetTop(LinkStack S, SElemType *e)
{
    LinkList p;
    p=S.Head->next;
    if(!p)
        return ERROR;
    *e=p->data;
    return OK;
}/*取栈顶元素*/
Status Pop(LinkStack *S, SElemType *e)
{
    LinkList p;
    p=S->Head->next;
    if(!p)
        return ERROR;
    *e=p->data;
    S->length--;
    S->Head->next=p->next;
    free(p);
    return OK;
}/*出栈*/
Status Push(LinkStack *S, SElemType e)
{
    LinkList p;
    p=(LinkList)malloc(sizeof(LNode));
    if(!p)
        return ERROR;
    p->next=S->Head->next;
    S->Head->next=p;
    p->data=e;
    S->length++;
    return OK;
}/*入栈*/
void PrintStack(LinkStack S)
{
    LinkList p;
    p=S.Head->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
typedef struct 
{
   QElemType *base;   //pointer the allocated memory
   int front;                    //front indicator
   int rear;                     //rear indicator
}SqQueue;
Status InitQueue(SqQueue *Q)
{
    Q->base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
    if(!Q->base)
        return ERROR;
    Q->front=Q->rear=0;
    return OK;
}
Status QueueEmpty(SqQueue Q)
{
    if(Q.front==Q.rear)
        return TRUE;
    else 
        return FALSE;
}
int QueueLength(SqQueue Q)
{
    return ((Q.rear-Q.front+MAXQSIZE)%MAXQSIZE);
}
Status GetHead(SqQueue Q,QElemType *e)
{
    if(Q.front==Q.rear)
        return ERROR;
    *e=Q.base[Q.front];
    return OK;
}
Status DeQueue(SqQueue *Q,QElemType *e)
{
    if(Q->rear==Q->front)
        return ERROR;
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAXQSIZE;
    return OK;
}/*出队*/
Status EnQueue (SqQueue *Q, QElemType e)
{
    if((Q->rear+1)%MAXQSIZE==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXQSIZE;
    return OK;
}/*入队*/
Status ClearQueue (SqQueue *Q)
{
    Q->front=Q->rear=0;
    return OK;
}/*清空队列*/
void PrintQueue (SqQueue S)
{
    int i;
    for(i=S.front;i<S.rear;i=(i+1)%MAXQSIZE)
        printf("%d ",S.base[i]);
    printf("\n");
}
Status JudgePalindrome(char s[])
{
    LinkStack p;
    SElemType e1;
    if(!InitStack(&p))
        return ERROR;
    SqQueue q;
    QElemType e2;
    if(!InitQueue(&q))
        return ERROR;
    int i,n=strlen(s);
    for(i=0;i<n;i++)
    {
        Push(&p,s[i]);
        EnQueue(&q,s[i]);
    }
    for(i=0;i<n;i++)
    {
        GetTop(p,&e1);
        GetHead(q,&e2);
        if(e1==e2)
        {
            Pop(&p,&e1);
            DeQueue(&q,&e2);
        }
        else
            break;
    }
    if(StackEmpty(p))
        return TRUE;
    else 
        return FALSE;
}
int main()
{
    char a[10];
    int f;
    scanf("%s",a);
    f=JudgePalindrome(a);
    if(f==1)
        printf("True\n");
    else
        printf("False\n");
}