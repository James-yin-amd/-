#include <stdio.h>  
#include <stdlib.h>  
#include <malloc.h>
#include "string.h"
#include "math.h"
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int SElemType;  
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
    S->Head->next=NULL;
    S->length=0;
    return OK;
}
Status StackEmpty (LinkStack S)
{
    if(S.length==0)
        return TRUE;
    else 
        return FALSE;
}
int StackLength (LinkStack S)
{                   
    return (S.length);
}
Status GetTop(LinkStack S, SElemType *e)
{
    LinkList p;
    p=S.Head->next;
    if(!p)
        return ERROR;
    *e=p->data;
    return OK;
}
Status Pop(LinkStack *S, SElemType *e)
{
    LinkList p;
    p=S->Head->next;
    if(!p)
        return ERROR;
    *e=p->data;
    S->length--;
    S->Head->next=p->next;
    p->next=NULL;
    free(p);
    return OK;
}
Status Push(LinkStack *S, SElemType e)
{
    LinkList p;
    p=(LinkList)malloc(sizeof(LNode));
    if(!p)
        return OK;
    p->data=e;
    p->next=S->Head->next;
    S->Head->next=p;
    S->length++;
    return OK;
}
void PrintStack (LinkStack S)
{
    LinkList p;
    p=S.Head->next;
    while(p)
    {
        printf("%c ",p->data);
        p=p->next;
    }
    printf("\n");
}
void transfer(char *s,SElemType *a)
{
    int i=0,j=0;
    *a=0;
    int b=strlen(s);
    if(s[i]=='-')
    {
        for(i=b-1;i>0;i--)
        {
            *a=pow(10,j)*((int)s[i]-'0')+*a;
            j++;
        }
        *a=-(*a);
    }
    else
    for(i=b-1;i>=0;i--)
        {
            *a=pow(10,j)*((int)s[i]-'0')+*a;
            j++;
        }
}
int CalExpression(char s[][3], int nSize)
{
    LinkStack p;
    SElemType e,f;
    int a;
    if(!InitStack(&p))
        return OK;
    int i;
    for(i=0;i<nSize;i++)
    {
        if(s[i][0]=='-'&&s[i][1]!='\0')
        {
            transfer(s[i],&e);
            Push(&p,e);
        }
        else if(s[i][0]>='0'&&s[i][0]<='9')
        {
            transfer(s[i],&e);
            Push(&p,e);
        }
        else if(s[i][0]=='+')
        {
            Pop(&p,&e);
            Pop(&p,&f);
            a=e+f;
            Push(&p,a);
        }
        else if(s[i][0]=='-')
        {
            Pop(&p,&e);
            Pop(&p,&f);
            a=f-e;
            Push(&p,a);
        }
        else if(s[i][0]=='*')
        {
            Pop(&p,&e);
            Pop(&p,&f);
            a=e*f;
            Push(&p,a);
        }
        else if(s[i][0]=='/')
        {
            Pop(&p,&e);
            Pop(&p,&f);
            a=f/e;
            Push(&p,a);
        }
    }
    Pop(&p,&a);
    return a;
}
int main()
{
    char a[20][3];
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%s",a[i]);
    printf("%d",CalExpression(a,n));
}