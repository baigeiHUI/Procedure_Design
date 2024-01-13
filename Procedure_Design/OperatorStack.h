
#ifndef _OPERATORSTACK_H
#define _OPERATORSTACK_H
#endif
#define maxsize 100
#include<stdio.h>
typedef struct Operator_Stack
{
    char Data[maxsize];   // 存储元素的数组
    int top;            //栈顶指针
    void Init();
    void Pop();
    void Push(char elem);
    int IsEmpty();
    int IsFull();
    char Get_Top();
    void Clear();

} Operator_Stack;
