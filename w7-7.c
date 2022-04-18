#include <stdio.h>   
#include <stdlib.h>   
#include <malloc.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;
typedef struct L_node
{   
    ElemType data;           // data field 
    struct L_node *next;       // pointer field
}LNode, *LinkList;
Status InitList_L(LinkList *L)
{
    (*L)=(LinkList)malloc(sizeof(LNode));
    if(!(*L))
        return ERROR;
    (*L)->next=NULL;
    return OK;
}
Status CreateList_L(LinkList *L,ElemType a[],int n)
{
    int i;
    LinkList p;
    for(i=n-1;i>=0;i--)
    {
        p=(LinkList)malloc(sizeof(LNode));
        if(!p)
            return ERROR;
        p->data=a[i];
        p->next=(*L)->next;
        (*L)->next=p;
    }
    return OK;
}
void MoveMaxNode_L(LinkList *L, ElemType *maxval)
{
    LinkList p,q,m;
    ElemType e;
    p=*L;
    q=p->next;
    e=q->data;
    while(q)
    {
        if(e>=q->data)
        {
            e=q->data;
            m=p;
        }
        q=q->next;
        p=p->next;
    }
    p=m->next;
    m->next=p->next;
    p->next=(*L)->next;
    (*L)->next=p;
    *maxval=p->data;
}
void printfl(LinkList l)
{
    LinkList p;
    p=l->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
int main()
{
    int i,n,a[10];
    LinkList s;
    ElemType e;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    if(!InitList_L(&s))
        return ERROR;
    CreateList_L(&s,a,n);
    MoveMaxNode_L(&s,&e);
    printf("%d\n",e);
    printfl(s);
}