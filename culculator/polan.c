//#include "polan.h"
#include <stdio.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10

typedef struct
{
    double *base;
    double *top;
    int stackSize;
}Stack;

void InitStack(Stack *s)
{
    s->base = (double *)malloc(STACK_INIT_SIZE * sizeof(double));       //以base指针动态分配10个类型的内存空间

    if(!s->base)
    {
        exit(0);
    }

    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

void Push(Stack *s, double e)
{
    if( s->top - s->base >= s->stackSize )
    {
        s->base = (double *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(double));

        if(!s->base)
        {
            exit(0);
        }

        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }

    *(s->top) = e;
    s->top++;
}

void Pop(Stack *s, double *e)
{
    if( s->top == s->base )
    {
        return;
    }

    *e = *--(s->top);
}

int StackLen(Stack s)
{
    return (s.top - s.base);
}

