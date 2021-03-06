//LINKED_QUEUE
//https://github.com/L-F-Z/ADT_Code
//Developed by UCAS ADT_Code Group

#ifndef LINKED_QUEUE_C 
#define LINKED_QUEUE_C

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//----------|Status|-----------
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//-----------------------------

//---------|Typedef|-----------
typedef int ElemType; //存储的数据类型
typedef struct QNode //链式队列节点
{
    ElemType data;      //数据域
    struct QNode *next; //指针域，指向下一个节点
} QNode, *QNodeptr;
typedef struct _LinkQueue_struct //链式队列头
{
    QNodeptr front;
    QNodeptr rear;
} * LinkQueue;//链式队列头节点指针
//-----------------------------
//定义的新的变量类型首字母大写

//---------|FuncList|----------
Status InitQueue(LinkQueue* Q);
//生成一个新的链式队列
Status DestoryQueue(LinkQueue Q);
//销毁一个链式队列
Status ClearQueue(LinkQueue Q);
//清空链式队列, 保留队列头
Status QueueEmpty(LinkQueue Q);
//返回队列是否为空, 若为空返回TRUE
int QueueLength(LinkQueue Q);
//返回链式队列长度
Status GetHead(LinkQueue Q, ElemType *E);
//返回队列头元素值
Status EnQueue(LinkQueue Q, ElemType E);
//将新元素进入队列尾
Status DeQueue(LinkQueue Q, ElemType *E);
//将首元素离开队列
Status QueueTraverse(LinkQueue Q, void visit(ElemType e));
//对队列的每个元素应用函数visit
//-----------------------------

Status InitQueue(LinkQueue* Q)
//生成一个新的链式队列
{
    *Q = (LinkQueue)malloc(sizeof(struct _LinkQueue_struct));
    (*Q)->front = (*Q)->rear = (QNodeptr)malloc(sizeof(QNode));
    if (!(*Q)->front)
        exit(OVERFLOW);
    (*Q)->front->next = NULL;
    return OK;
}

Status DestoryQueue(LinkQueue Q)
//销毁一个链式队列
{
    while (Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

Status ClearQueue(LinkQueue Q)
//清空链式队列, 保留队列头
{
    if (!Q)
        return OVERFLOW;
    QNodeptr t = Q->front;
    QNodeptr p = Q->front->next;
    while (p != 0)
    {
        t = p->next;
        free(p);
        p = t;
    }
    Q->rear = Q->front;
    Q->front->next = 0;
    return OK;
}

Status QueueEmpty(LinkQueue Q)
//返回队列是否为空, 若为空返回TRUE
{
    return Q->rear == Q->front;
}

int QueueLength(LinkQueue Q)
//返回链式队列长度
{
    if (!Q)
        return -1;
    QNodeptr t = Q->front;
    int cnt = 0;
    while (t != Q->rear)
    {
        t = t->next;
        cnt++;
    }
    return cnt;
}

Status GetHead(LinkQueue Q, ElemType *E)
//返回队列头元素值
{
    if (!Q || Q->rear == Q->front)
        return OVERFLOW;
    *E = Q->front->next->data;
    return OK;
}

Status EnQueue(LinkQueue Q, ElemType E)
//将新元素进入队列尾
{
    QNodeptr p = (QNodeptr)malloc(sizeof(QNode));
    if (!p)
        exit(OVERFLOW);
    p->data = E;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

Status DeQueue(LinkQueue Q, ElemType *E)
//将首元素离开队列
{
    if (Q->front == Q->rear)
        return ERROR;
    QNodeptr p = Q->front->next;
    *E = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return OK;
}

Status QueueTraverse(LinkQueue Q, void visit(ElemType e))
//对队列的每个元素应用函数visit
{
    if ((!Q) || (Q->front == Q->rear))
        return ERROR;
    QNodeptr p = Q->front->next;
    while (p != Q->rear)
    {
        visit(p->data);
        p = p->next;
    }
    return OK;
}

void _test(int i)
{
    printf("%d ", i);
}

// #include"lazy.h"
// int main()
// {
//     LinkQueue Q;
//     InitQueue(&Q);
//     CK(QueueEmpty(Q));
//     ClearQueue(Q);
//     CK(QueueLength(Q));  
//     EnQueue(Q, 1);
//     EnQueue(Q, 2);
//     EnQueue(Q, 3);
//     EnQueue(Q, 4);
//     int a;
//     GetHead(Q,&a);
//     CK(a);
//     DeQueue( Q,  &a);
//     DeQueue( Q,  &a);
//     CK(a);
//     QueueTraverse(Q, _test);
//     DestoryQueue(Q);
//     return 0;
// }

#endif