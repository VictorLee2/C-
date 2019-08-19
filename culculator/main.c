#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calculate.h"
#include "polan.h"

#define MAXBUFFER 50

int main(void)
{
    culStack s; //��׺���ʽ��ջ���洢�������
    Stack r;    //������ջ�����洢����
    char c, d;
    double e, f;
    char str[MAXBUFFER];    //���ڴ洢��׺���ʽ
    char strg[MAXBUFFER];   //���ڴ洢С�����ߴ���һλ������
    int i = 0, j = 0;

    CulInitStack(&s);   //��ʼ��������ջ

    printf("Please enter an expression and enter # to end:\n");
    scanf("%c", &c);

    while('#' != c)
    {
        //�����������Ϊ���ֻ���С���㣬ֱ�Ӵ�������
        while(isdigit(c) || '.' == c)
        {
            str[i++] = c;
            scanf("%c", &c);
        }

        //�����������Ϊ���ţ������ж�
        //������Ϊ')'ʱ����'('֮ǰ�ķ��ų�ջ
        if(')' == c)
        {
            CulPop(&s, &d);
            while('(' != d)
            {
                str[i++] = ' '; //����֮���ÿո����
                str[i++] = d;
                CulPop(&s, &d);
            }
        }
        //������Ϊ'+'��'-'ʱ����ջ���Ƿ��������Լ�'('�����ж�
        else if('+' == c || '-' == c)
        {
            if(!CulStackLen(s))
            {
                CulPush(&s, c);
            }
            else
            {
                do
                {
                    CulPop(&s, &d);
                    if('(' == d)
                    {
                        CulPush(&s, d);
                    }
                    else
                    {
                        str[i++] = ' ';
                        str[i++] = d;
                    }
                }while(CulStackLen(s) && '(' != d);
                CulPush(&s, c);
            }
        }
        else if('*' == c || '/' == c || '(' == c)
        {
            CulPush(&s, c);
        }
        else if('#' == c)
        {
            break;
        }
        else
        {
            printf("Error: Illegal input!\n");
        }
        str[i++] = ' ';
        scanf("%c", &c);
    }

    //��˳�����ջ�ڵķ���
    while(CulStackLen(s))
    {
        CulPop(&s, &d);
        str[i++] = ' ';
        str[i++] = d;
    }
    str[i] = '\0';  //�ַ�����'\0'��β

    i = 0;
    //���ת����ĺ�׺���ʽ
    while('\0' != str[i])
    {
        printf("%c", str[i]);
        i++;
    }
    printf("\n");

    InitStack(&r);
    i = 0;

    while('\0' != str[i])
    {
        //��������������ִ洢��һ���ַ�����
        while(isdigit(str[i]) || '.' == str[i])
        {
            strg[j++] = str[i++];
            strg[j] = '\0';
            if( j >= MAXBUFFER)
            {
                printf("Error: The single data entered is too large!\n");
                return -1;
            }
            if(' ' == str[i])
            {
                e = atof(strg);    //���ַ����ķ�������ת��Ϊ����
                Push(&r, e);       //�����ִ���ջ
                j = 0;
                i++;
                break;
            }
        }
        //������Ӧ�ķ��Ž��м���
        switch( str[i] )
        {
        case '+':
            Pop(&r, &f);
            Pop(&r, &e);
            Push(&r, e+f);
            i++;
            break;
        case '-':
            Pop(&r, &f);
            Pop(&r, &e);
            Push(&r, e-f);
            i++;
            break;
        case '*':
            Pop(&r, &f);
            Pop(&r, &e);
            Push(&r, e*f);
            i++;
            break;
        case '/':
            Pop(&r, &f);
            Pop(&r, &e);
            if( f != 0)
            {
                Push(&r, e/f);
                i++;
            }
            else
            {
                printf("Error: Divisor is 0!\n");
                return -1;
            }
            break;
        case ' ':
            i++;
            break;
        default:
            break;
        }
    }

    Pop(&r, &e);
    printf("\nThe final calculation result is: %f\n", e);

    return 0;
}
