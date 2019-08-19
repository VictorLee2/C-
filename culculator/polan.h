#ifndef POLAN_H

#define POLAN_H
typedef struct
{
    double *base;
    double *top;
    int stackSize;
}Stack;
void InitStack(Stack *s);
void Push(Stack *s, double e);
void Pop(Stack *s, double *e);
int StackLen(Stack s);

#endif // POLAN_H
