#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct
{
    char data[MAX_SIZE]; 
    int top;             
} CharStack;

typedef struct
{
    int data[MAX_SIZE]; 
    int top;            
} IntStack;


void InitCharStack(CharStack *S)
{
    S->top = -1;
}


void InitIntStack(IntStack *S)
{
    S->top = -1;
}

//判断两个栈是否为空
int IsCharStackEmpty(CharStack *S)
{
    return S->top == -1;
}

int IsIntStackEmpty(IntStack *S)
{
    return S->top == -1;
}

//判断两个栈是否已满
int IsCharStackFull(CharStack *S)
{
    return S->top == MAX_SIZE - 1;
}

int IsIntStackFull(IntStack *S)
{
    return S->top == MAX_SIZE - 1;
}

//入栈
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

int PushInt(IntStack *S, int num)
{
    if (IsIntStackFull(S))
    {
        printf("整数栈已满，无法入栈！\n");
        return 0;
    }
    S->data[++(S->top)] = num;
    return 1;
}

//出栈
char PopChar(CharStack *S)
{
    if (IsCharStackEmpty(S))
    {
        printf("字符栈为空，无法出栈！\n");
        return '\0';
    }
    return S->data[(S->top)--];
}

int PopInt(IntStack *S)
{
    if (IsIntStackEmpty(S))
    {
        printf("整数栈为空，无法出栈！\n");
        return 0;
    }
    return S->data[(S->top)--];
}

//获取栈顶元素
char GetCharTop(CharStack *S)
{
    if (IsCharStackEmpty(S))
    {
        return '\0';
    }
    return S->data[S->top];
}

int GetIntTop(IntStack *S)
{
    if (IsIntStackEmpty(S))
    {
        return 0;
    }
    return S->data[S->top];
}

//十进制转其他进制（使用栈）
void DecimalToBase(int decimal, int base)
{
    if (decimal == 0)
    {
        printf("转换结果: 0\n");
        return;
    }

    CharStack stack;
    InitCharStack(&stack);

    int isNegative = 0;
    if (decimal < 0)
    {
        isNegative = 1;
        decimal = -decimal;
    }

    while (decimal > 0)
    {
        int remainder = decimal % base;
        char digit;

        if (remainder < 10)
        {
            digit = '0' + remainder;
        }
        else
        {
            digit = 'A' + (remainder - 10);
        }

        PushChar(&stack, digit);
        decimal /= base;
    }

    printf("转换结果: ");
    if (isNegative)
    {
        printf("-");
    }

    while (!IsCharStackEmpty(&stack))
    {
        printf("%c", PopChar(&stack));
    }
    printf("\n");
}

//其他进制转十进制（使用栈）
int BaseToDecimal(char *number, int base)
{
    IntStack stack;
    InitIntStack(&stack);

    int len = strlen(number);
    int result = 0;
    int power = 1;

    // 从右向左处理，使用栈来存储中间结果
    for (int i = len - 1; i >= 0; i--)
    {
        char digit = number[i];
        int value;

        if (isdigit(digit))
        {
            value = digit - '0';
        }
        else if (isalpha(digit))
        {
            value = toupper(digit) - 'A' + 10;
        }
        else
        {
            printf("错误：无效的数字字符 '%c'\n", digit);
            return -1;
        }

        if (value >= base)
        {
            printf("错误：数字 '%c' 在 %d 进制中无效\n", digit, base);
            return -1;
        }

        PushInt(&stack, value * power);
        power *= base;
    }

    // 计算总和
    while (!IsIntStackEmpty(&stack))
    {
        result += PopInt(&stack);
    }

    return result;
}

//任意进制之间的转换
void ConvertBetweenBases(char *number, int fromBase, int toBase)
{
    // 先转换为十进制
    int decimal = BaseToDecimal(number, fromBase);
    if (decimal == -1)
    {
        return;
    }

    printf("中间十进制值: %d\n", decimal);

    // 再从十进制转换为目标进制
    printf("转换结果: ");
    DecimalToBase(decimal, toBase);
}

//验证数字在给定进制下是否有效
int ValidateNumberInBase(char *number, int base)
{
    for (int i = 0; number[i] != '\0'; i++)
    {
        char digit = number[i];
        int value;

        if (isdigit(digit))
        {
            value = digit - '0';
        }
        else if (isalpha(digit))
        {
            value = toupper(digit) - 'A' + 10;
        }
        else
        {
            printf("错误：无效字符 '%c'\n", digit);
            return 0;
        }

        if (value >= base)
        {
            printf("错误：数字 '%c' 在 %d 进制中无效\n", digit, base);
            return 0;
        }
    }
    return 1;
}

//显示进制转换结果（使用栈反转顺序）
void DisplayConversionResult(int decimal, int base)
{
    CharStack stack;
    InitCharStack(&stack);

    if (decimal == 0)
    {
        printf("0");
        return;
    }

    while (decimal > 0)
    {
        int remainder = decimal % base;
        char digit;

        if (remainder < 10)
        {
            digit = '0' + remainder;
        }
        else
        {
            digit = 'A' + (remainder - 10);
        }

        PushChar(&stack, digit);
        decimal /= base;
    }

    while (!IsCharStackEmpty(&stack))
    {
        printf("%c", PopChar(&stack));
    }
}

//显示进制转换菜单
void ShowConversionMenu()
{
    printf("\n基于栈操作的进制转换系统\n");
    printf("1. 十进制转其他进制\n");
    printf("2. 其他进制转十进制\n");
    printf("3. 任意进制之间转换\n");
    printf("4. 验证数字在进制下的有效性\n");
    printf("5. 显示支持的进制范围\n");
    printf("6. 返回主菜单\n");
    printf("请选择操作: ");
}

//显示支持的进制范围
void ShowSupportedBases()
{
    printf("\n支持的进制范围: 2-36\n");
    printf("说明:\n");
    printf("- 2进制: 使用数字 0-1\n");
    printf("- 8进制: 使用数字 0-7\n");
    printf("- 10进制: 使用数字 0-9\n");
    printf("- 16进制: 使用数字 0-9 和字母 A-F\n");
    printf("- 最高36进制: 使用数字 0-9 和字母 A-Z\n");
}

//进制转换系统主函数
void NumberConversionSystem()
{
    int choice;
    char number[100];
    int base, fromBase, toBase;
    int decimal;

    while (1)
    {
        ShowConversionMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("请输入十进制数: ");
            scanf("%d", &decimal);
            printf("请输入目标进制(2-36): ");
            scanf("%d", &base);

            if (base < 2 || base > 36)
            {
                printf("错误：进制必须在2-36之间！\n");
                break;
            }

            printf("转换过程:\n");
            printf("十进制 %d 转换为 %d 进制: ", decimal, base);
            DecimalToBase(decimal, base);
            break;

        case 2:
            printf("请输入数字: ");
            fgets(number, sizeof(number), stdin);
            number[strcspn(number, "\n")] = '\0'; 

            printf("请输入原进制(2-36): ");
            scanf("%d", &base);

            if (base < 2 || base > 36)
            {
                printf("错误：进制必须在2-36之间！\n");
                break;
            }

            if (ValidateNumberInBase(number, base))
            {
                decimal = BaseToDecimal(number, base);
                if (decimal != -1)
                {
                    printf("%s(%d) = %d(10)\n", number, base, decimal);
                }
            }
            break;

        case 3:
            printf("请输入数字: ");
            fgets(number, sizeof(number), stdin);
            number[strcspn(number, "\n")] = '\0'; 

            printf("请输入原进制(2-36): ");
            scanf("%d", &fromBase);
            printf("请输入目标进制(2-36): ");
            scanf("%d", &toBase);

            if (fromBase < 2 || fromBase > 36 || toBase < 2 || toBase > 36)
            {
                printf("错误：进制必须在2-36之间！\n");
                break;
            }

            if (ValidateNumberInBase(number, fromBase))
            {
                printf("转换过程:\n");
                printf("%s(%d) -> ", number, fromBase);
                ConvertBetweenBases(number, fromBase, toBase);
            }
            break;

        case 4:
            printf("请输入数字: ");
            fgets(number, sizeof(number), stdin);
            number[strcspn(number, "\n")] = '\0';

            printf("请输入进制(2-36): ");
            scanf("%d", &base);

            if (base < 2 || base > 36)
            {
                printf("错误：进制必须在2-36之间！\n");
                break;
            }

            if (ValidateNumberInBase(number, base))
            {
                printf("数字 %s 在 %d 进制下是有效的\n", number, base);
            }
            else
            {
                printf("数字 %s 在 %d 进制下是无效的\n", number, base);
            }
            break;

        case 5:
            ShowSupportedBases();
            break;

        case 6:
            return;

        default:
            printf("无效的选择，请重新输入！\n");
            break;
        }
        printf("\n");
    }
}

int main()
{
    printf("\n运行完整进制转换系统:\n");
    NumberConversionSystem();

    return 0;
}
