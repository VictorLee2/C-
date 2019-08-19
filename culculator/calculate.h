#ifndef CALCULATE_H

#define CALCULATE_H
typedef struct
{
    char *base;
    char *top;
    int stackSize;
}culStack;
void CulInitStack(culStack *s);
void CulPush(culStack *s, char d);
void CulPop(culStack *s, char *d);
int CulStackLen(culStack s);

#endif // CALCULATE_H
