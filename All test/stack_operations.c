#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

// 栈结构体
typedef struct
{
    char data[MAX_SIZE]; // 字符栈数据
    int top;             // 栈顶指针
} CharStack;

typedef struct
{
    double data[MAX_SIZE]; // 数字栈数据
    int top;               // 栈顶指针
} DoubleStack;

// 1. 初始化字符栈
void InitCharStack(CharStack *S)
{
    S->top = -1;
}

// 2. 初始化数字栈
void InitDoubleStack(DoubleStack *S)
{
    S->top = -1;
}

// 3. 判断字符栈是否为空
int IsCharStackEmpty(CharStack *S)
{
    return S->top == -1;
}

// 4. 判断数字栈是否为空
int IsDoubleStackEmpty(DoubleStack *S)
{
    return S->top == -1;
}

// 5. 判断字符栈是否已满
int IsCharStackFull(CharStack *S)
{
    return S->top == MAX_SIZE - 1;
}

// 6. 判断数字栈是否已满
int IsDoubleStackFull(DoubleStack *S)
{
    return S->top == MAX_SIZE - 1;
}

// 7. 字符栈入栈
int PushChar(CharStack *S, char ch)
{
    if (IsCharStackFull(S))
    {
        printf("字符栈已满，无法入栈！\n");
        return 0;
    }
    S->data[++(S->top)] = ch;
    return 1;
}

// 8. 数字栈入栈
int PushDouble(DoubleStack *S, double num)
{
    if (IsDoubleStackFull(S))
    {
        printf("数字栈已满，无法入栈！\n");
        return 0;
    }
    S->data[++(S->top)] = num;
    return 1;
}

// 9. 字符栈出栈
char PopChar(CharStack *S)
{
    if (IsCharStackEmpty(S))
    {
        printf("字符栈为空，无法出栈！\n");
        return '\0';
    }
    return S->data[(S->top)--];
}

// 10. 数字栈出栈
double PopDouble(DoubleStack *S)
{
    if (IsDoubleStackEmpty(S))
    {
        printf("数字栈为空，无法出栈！\n");
        return 0.0;
    }
    return S->data[(S->top)--];
}

// 11. 获取字符栈栈顶元素
char GetCharTop(CharStack *S)
{
    if (IsCharStackEmpty(S))
    {
        return '\0';
    }
    return S->data[S->top];
}

// 12. 获取数字栈栈顶元素
double GetDoubleTop(DoubleStack *S)
{
    if (IsDoubleStackEmpty(S))
    {
        return 0.0;
    }
    return S->data[S->top];
}

// 13. 获取字符栈长度
int GetCharStackLength(CharStack *S)
{
    return S->top + 1;
}

// 14. 获取数字栈长度
int GetDoubleStackLength(DoubleStack *S)
{
    return S->top + 1;
}
