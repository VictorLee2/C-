#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calculate.h"
#include "polan.h"

#define MAXBUFFER 50

int main(void)
{
    culStack s; //后缀表达式用栈，存储计算符号
    Stack r;    //计算用栈，仅存储数字
    char c, d;
    double e, f;
    char str[MAXBUFFER];    //用于存储后缀表达式
    char strg[MAXBUFFER];   //用于存储小数或者大于一位的数字
    int i = 0, j = 0;

    CulInitStack(&s);   //初始化计算用栈

    printf("Please enter an expression and enter # to end:\n");
    scanf("%c", &c);

    while('#' != c)
    {
        //如果输入数据为数字或者小数点，直接存入数组
        while(isdigit(c) || '.' == c)
        {
            str[i++] = c;
            scanf("%c", &c);
        }

        //如果输入数据为符号，进行判断
        //当数据为')'时，将'('之前的符号出栈
        if(')' == c)
        {
            CulPop(&s, &d);
            while('(' != d)
            {
                str[i++] = ' '; //符号之间用空格隔开
                str[i++] = d;
                CulPop(&s, &d);
            }
        }
        //当数据为'+'或'-'时，对栈内是否有数据以及'('进行判断
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

    //按顺序清空栈内的符号
    while(CulStackLen(s))
    {
        CulPop(&s, &d);
        str[i++] = ' ';
        str[i++] = d;
    }
    str[i] = '\0';  //字符串以'\0'结尾

    i = 0;
    //输出转换后的后缀表达式
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
        //将数组的连续数字存储在一个字符串中
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
                e = atof(strg);    //将字符串的符号整体转换为数字
                Push(&r, e);       //将数字存入栈
                j = 0;
                i++;
                break;
            }
        }
        //根据相应的符号进行计算
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
