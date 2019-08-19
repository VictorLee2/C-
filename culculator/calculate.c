//#include "calculate.h"
#include <stdio.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10

typedef struct
{
    char *base;
    char *top;
    int stackSize;
}culStack;

void CulInitStack(culStack *s)
{
    s->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));

    if(!s->base)
    {
        exit(0);
    }

    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

void CulPush(culStack *s, char d)
{
    if(s->top - s->base >= s->stackSize)
    {
        s->base = (char *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(char));

        if(!s->base)
        {
            exit(0);
        }

        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }

    *(s->top) = d;
    s->top++;
}

void CulPop(culStack *s, char *d)
{
    if(s->top == s->base)
    {
        return;
    }
    *d = *--(s->top);
}

int CulStackLen(culStack s)
{
    return (s.top - s.base);
}
