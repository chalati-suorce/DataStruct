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

// 13. 判断字符是否为运算符
int IsOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')';
}

// 14. 获取运算符优先级
int GetPriority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case '(':
        return 0;
    default:
        return -1;
    }
}

// 15. 执行运算
double Calculate(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            printf("错误：除数不能为零！\n");
            return 0;
        }
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return 0;
    }
}

// 16. 中缀表达式转后缀表达式
char *InfixToPostfix(char *infix)
{
    CharStack opStack;
    InitCharStack(&opStack);

    char *postfix = (char *)malloc(strlen(infix) * 2);
    int postfixIndex = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        // 跳过空格
        if (ch == ' ')
        {
            continue;
        }

        // 如果是数字，直接输出到后缀表达式
        if (isdigit(ch) || ch == '.')
        {
            while (isdigit(infix[i]) || infix[i] == '.')
            {
                postfix[postfixIndex++] = infix[i++];
            }
            postfix[postfixIndex++] = ' ';
            i--; // 回退一个字符
        }
        // 如果是左括号，直接入栈
        else if (ch == '(')
        {
            PushChar(&opStack, ch);
        }
        // 如果是右括号，弹出栈中运算符直到遇到左括号
        else if (ch == ')')
        {
            while (!IsCharStackEmpty(&opStack) && GetCharTop(&opStack) != '(')
            {
                postfix[postfixIndex++] = PopChar(&opStack);
                postfix[postfixIndex++] = ' ';
            }
            if (!IsCharStackEmpty(&opStack) && GetCharTop(&opStack) == '(')
            {
                PopChar(&opStack); // 弹出左括号
            }
        }
        // 如果是运算符
        else if (IsOperator(ch))
        {
            while (!IsCharStackEmpty(&opStack) &&
                   GetPriority(GetCharTop(&opStack)) >= GetPriority(ch))
            {
                postfix[postfixIndex++] = PopChar(&opStack);
                postfix[postfixIndex++] = ' ';
            }
            PushChar(&opStack, ch);
        }
    }

    // 将栈中剩余的运算符弹出
    while (!IsCharStackEmpty(&opStack))
    {
        postfix[postfixIndex++] = PopChar(&opStack);
        postfix[postfixIndex++] = ' ';
    }

    postfix[postfixIndex] = '\0';
    return postfix;
}

// 17. 计算后缀表达式
double EvaluatePostfix(char *postfix)
{
    DoubleStack numStack;
    InitDoubleStack(&numStack);

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];

        // 跳过空格
        if (ch == ' ')
        {
            continue;
        }

        // 如果是数字，解析并压入栈
        if (isdigit(ch) || ch == '.')
        {
            char numStr[20];
            int numIndex = 0;

            while (isdigit(postfix[i]) || postfix[i] == '.')
            {
                numStr[numIndex++] = postfix[i++];
            }
            numStr[numIndex] = '\0';
            i--; // 回退一个字符

            double num = atof(numStr);
            PushDouble(&numStack, num);
        }
        // 如果是运算符，弹出两个操作数进行计算
        else if (IsOperator(ch))
        {
            double b = PopDouble(&numStack);
            double a = PopDouble(&numStack);
            double result = Calculate(a, b, ch);
            PushDouble(&numStack, result);
        }
    }

    return PopDouble(&numStack);
}

// 18. 直接计算中缀表达式
double EvaluateInfix(char *infix)
{
    CharStack opStack;
    DoubleStack numStack;
    InitCharStack(&opStack);
    InitDoubleStack(&numStack);

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        // 跳过空格
        if (ch == ' ')
        {
            continue;
        }

        // 如果是数字，解析并压入数字栈
        if (isdigit(ch) || ch == '.')
        {
            char numStr[20];
            int numIndex = 0;

            while (isdigit(infix[i]) || infix[i] == '.')
            {
                numStr[numIndex++] = infix[i++];
            }
            numStr[numIndex] = '\0';
            i--; // 回退一个字符

            double num = atof(numStr);
            PushDouble(&numStack, num);
        }
        // 如果是左括号，直接入运算符栈
        else if (ch == '(')
        {
            PushChar(&opStack, ch);
        }
        // 如果是右括号，进行计算直到遇到左括号
        else if (ch == ')')
        {
            while (!IsCharStackEmpty(&opStack) && GetCharTop(&opStack) != '(')
            {
                char op = PopChar(&opStack);
                double b = PopDouble(&numStack);
                double a = PopDouble(&numStack);
                double result = Calculate(a, b, op);
                PushDouble(&numStack, result);
            }
            if (!IsCharStackEmpty(&opStack) && GetCharTop(&opStack) == '(')
            {
                PopChar(&opStack); // 弹出左括号
            }
        }
        // 如果是运算符
        else if (IsOperator(ch))
        {
            while (!IsCharStackEmpty(&opStack) &&
                   GetPriority(GetCharTop(&opStack)) >= GetPriority(ch))
            {
                char op = PopChar(&opStack);
                double b = PopDouble(&numStack);
                double a = PopDouble(&numStack);
                double result = Calculate(a, b, op);
                PushDouble(&numStack, result);
            }
            PushChar(&opStack, ch);
        }
    }

    // 处理剩余的运算符
    while (!IsCharStackEmpty(&opStack))
    {
        char op = PopChar(&opStack);
        double b = PopDouble(&numStack);
        double a = PopDouble(&numStack);
        double result = Calculate(a, b, op);
        PushDouble(&numStack, result);
    }

    return PopDouble(&numStack);
}

// 19. 验证表达式合法性
int ValidateExpression(char *expression)
{
    CharStack bracketStack;
    InitCharStack(&bracketStack);

    for (int i = 0; expression[i] != '\0'; i++)
    {
        char ch = expression[i];

        // 跳过空格
        if (ch == ' ')
        {
            continue;
        }

        // 检查括号匹配
        if (ch == '(')
        {
            PushChar(&bracketStack, ch);
        }
        else if (ch == ')')
        {
            if (IsCharStackEmpty(&bracketStack))
            {
                printf("错误：括号不匹配！\n");
                return 0;
            }
            PopChar(&bracketStack);
        }

        // 检查运算符使用
        if (IsOperator(ch))
        {
            if (i > 0 && IsOperator(expression[i - 1]) && expression[i - 1] != '(')
            {
                printf("错误：连续运算符！\n");
                return 0;
            }
        }
    }

    if (!IsCharStackEmpty(&bracketStack))
    {
        printf("错误：括号不匹配！\n");
        return 0;
    }

    return 1;
}

// 20. 显示菜单
void ShowMenu()
{
    printf("\n栈的表达式求值系统\n");
    printf("1. 中缀表达式转后缀表达式\n");
    printf("2. 计算后缀表达式\n");
    printf("3. 直接计算中缀表达式\n");
    printf("4. 验证表达式合法性\n");
    printf("5. 清屏\n");
    printf("0. 退出系统\n");
    printf("请选择操作: ");
}

int main()
{
    char expression[100];
    int choice;

    printf("栈的表达式求值系统\n");
    printf("支持的运算符: +, -, *, /, ^, (, )\n");
    printf("注意：请使用空格分隔数字和运算符\n");

    while (1)
    {
        ShowMenu();
        scanf("%d", &choice);
        getchar(); // 清除输入缓冲区

        switch (choice)
        {
        case 0:
            printf("感谢使用表达式求值系统！\n");
            return 0;

        case 1:
            printf("请输入中缀表达式: ");
            fgets(expression, sizeof(expression), stdin);
            expression[strcspn(expression, "\n")] = '\0'; // 去除换行符

            if (ValidateExpression(expression))
            {
                char *postfix = InfixToPostfix(expression);
                printf("后缀表达式: %s\n", postfix);
                free(postfix);
            }
            else
            {
                printf("表达式不合法！\n");
            }
            break;

        case 2:
            printf("请输入后缀表达式: ");
            fgets(expression, sizeof(expression), stdin);
            expression[strcspn(expression, "\n")] = '\0'; // 去除换行符

            double result = EvaluatePostfix(expression);
            printf("计算结果: %.2f\n", result);
            break;

        case 3:
            printf("请输入中缀表达式: ");
            fgets(expression, sizeof(expression), stdin);
            expression[strcspn(expression, "\n")] = '\0'; // 去除换行符

            if (ValidateExpression(expression))
            {
                double result = EvaluateInfix(expression);
                printf("计算结果: %.2f\n", result);
            }
            else
            {
                printf("表达式不合法！\n");
            }
            break;

        case 4:
            printf("请输入表达式: ");
            fgets(expression, sizeof(expression), stdin);
            expression[strcspn(expression, "\n")] = '\0'; // 去除换行符

            if (ValidateExpression(expression))
            {
                printf("表达式合法！\n");
            }
            else
            {
                printf("表达式不合法！\n");
            }
            break;

        case 5:
            system("cls"); // Windows系统清屏
            // system("clear"); // Linux/Mac系统清屏
            break;

        default:
            printf("无效的选择，请重新输入！\n");
            break;
        }

        printf("\n");
    }

    return 0;
}
