#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// 栈结构体
typedef struct
{
    char data[MAX_SIZE]; // 字符栈数据
    int top;             // 栈顶指针
} CharStack;

// 1. 初始化字符栈
void InitCharStack(CharStack *S)
{
    S->top = -1;
}

// 2. 判断字符栈是否为空
int IsCharStackEmpty(CharStack *S)
{
    return S->top == -1;
}

// 3. 判断字符栈是否已满
int IsCharStackFull(CharStack *S)
{
    return S->top == MAX_SIZE - 1;
}

// 4. 字符栈入栈
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

// 5. 字符栈出栈
char PopChar(CharStack *S)
{
    if (IsCharStackEmpty(S))
    {
        printf("字符栈为空，无法出栈！\n");
        return '\0';
    }
    return S->data[(S->top)--];
}

// 6. 十进制转二进制
void DecimalToBinary(int decimal)
{
    CharStack stack;
    InitCharStack(&stack);
    
    printf("十进制数 %d 转换为二进制: ", decimal);
    
    if (decimal == 0) {
        printf("0\n");
        return;
    }
    
    // 将余数入栈
    while (decimal > 0) {
        int remainder = decimal % 2;
        PushChar(&stack, remainder + '0'); // 将数字转换为字符
        decimal = decimal / 2;
    }
    
    // 出栈得到二进制结果
    while (!IsCharStackEmpty(&stack)) {
        printf("%c", PopChar(&stack));
    }
    printf("\n");
}

// 7. 十进制转八进制
void DecimalToOctal(int decimal)
{
    CharStack stack;
    InitCharStack(&stack);
    
    printf("十进制数 %d 转换为八进制: ", decimal);
    
    if (decimal == 0) {
        printf("0\n");
        return;
    }
    
    // 将余数入栈
    while (decimal > 0) {
        int remainder = decimal % 8;
        PushChar(&stack, remainder + '0'); // 将数字转换为字符
        decimal = decimal / 8;
    }
    
    // 出栈得到八进制结果
    while (!IsCharStackEmpty(&stack)) {
        printf("%c", PopChar(&stack));
    }
    printf("\n");
}

// 8. 十进制转十六进制
void DecimalToHexadecimal(int decimal)
{
    CharStack stack;
    InitCharStack(&stack);
    
    printf("十进制数 %d 转换为十六进制: ", decimal);
    
    if (decimal == 0) {
        printf("0\n");
        return;
    }
    
    // 将余数入栈
    while (decimal > 0) {
        int remainder = decimal % 16;
        char hexChar;
        
        if (remainder < 10) {
            hexChar = remainder + '0'; // 0-9
        } else {
            hexChar = remainder - 10 + 'A'; // A-F
        }
        
        PushChar(&stack, hexChar);
        decimal = decimal / 16;
    }
    
    // 出栈得到十六进制结果
    while (!IsCharStackEmpty(&stack)) {
        printf("%c", PopChar(&stack));
    }
    printf("\n");
}

// 9. 显示进制转换菜单
void ShowConversionMenu()
{
    printf("\n进制转换系统\n");
    printf("1. 十进制转二进制\n");
    printf("2. 十进制转八进制\n");
    printf("3. 十进制转十六进制\n");
    printf("4. 退出系统\n");
    printf("请选择操作: ");
}

// 10. 进制转换系统
void NumberConversionSystem()
{
    int choice;
    int decimal;
    
    while (1) {
        ShowConversionMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("请输入十进制正整数: ");
                scanf("%d", &decimal);
                if (decimal < 0) {
                    printf("错误：请输入正整数！\n");
                } else {
                    DecimalToBinary(decimal);
                }
                break;
                
            case 2:
                printf("请输入十进制正整数: ");
                scanf("%d", &decimal);
                if (decimal < 0) {
                    printf("错误：请输入正整数！\n");
                } else {
                    DecimalToOctal(decimal);
                }
                break;
                
            case 3:
                printf("请输入十进制正整数: ");
                scanf("%d", &decimal);
                if (decimal < 0) {
                    printf("错误：请输入正整数！\n");
                } else {
                    DecimalToHexadecimal(decimal);
                }
                break;
                
            case 4:
                printf("感谢使用进制转换系统！\n");
                return;
                
            default:
                printf("无效的选择，请重新输入！\n");
                break;
        }
        printf("\n");
    }
}

// 11. 主函数
int main()
{
    printf("进制转换系统\n");
    printf("使用栈实现十进制到二进制、八进制、十六进制的转换\n\n");
    
    NumberConversionSystem();
    
    return 0;
}
