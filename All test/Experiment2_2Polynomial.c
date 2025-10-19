#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 多项式项结构体
typedef struct PolyNode
{
    float coef;            // 系数
    int exp;               // 指数
    struct PolyNode *next; // 指向下一项的指针
} PolyNode, *Polynomial;

// 1. 创建多项式项
PolyNode *CreateNode(float coef, int exp)
{
    PolyNode *node = (PolyNode *)malloc(sizeof(PolyNode));
    if (node == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    node->coef = coef;
    node->exp = exp;
    node->next = NULL;
    return node;
}

// 2. 初始化多项式
void InitPolynomial(Polynomial *P)
{
    *P = NULL;
    printf("多项式初始化成功！\n");
}

// 12. 清空多项式
void ClearPolynomial(Polynomial *P)
{
    PolyNode *current = *P;
    PolyNode *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *P = NULL;
    printf("多项式已清空！\n");
}

// 3. 在多项式尾部插入项
int InsertTerm(Polynomial *P, float coef, int exp)
{
    PolyNode *newNode = CreateNode(coef, exp);
    if (newNode == NULL)
    {
        return 0;
    }

    // 检查指数是否重复
    PolyNode *current = *P;
    PolyNode *prev = NULL;
    while (current != NULL)
    {
        if (current->exp == exp)
        {
            printf("指数 %d 已存在，无法插入！\n", exp);
            free(newNode);
            return 0;
        }
        prev = current;
        current = current->next;
    }

    if (*P == NULL)
    {
        *P = newNode;
    }
    else
    {
        prev->next = newNode;
    }

    printf("项 %.2fx^%d 插入成功！\n", coef, exp);
    return 1;
}

// 4. 按指数降序插入项（保持有序）
int InsertTermOrdered(Polynomial *P, float coef, int exp)
{
    if (coef == 0)
    {
        printf("系数为0，不插入！\n");
        return 0;
    }

    PolyNode *newNode = CreateNode(coef, exp);
    if (newNode == NULL)
    {
        return 0;
    }

    PolyNode *current = *P;
    PolyNode *prev = NULL;

    // 查找插入位置
    while (current != NULL && current->exp > exp)
    {
        prev = current;
        current = current->next;
    }

    // 检查指数是否重复
    if (current != NULL && current->exp == exp)
    {
        printf("指数 %d 已存在，无法插入！\n", exp);
        free(newNode);
        return 0;
    }

    // 插入新节点
    if (prev == NULL)
    {
        newNode->next = *P;
        *P = newNode;
    }
    else
    {
        newNode->next = current;
        prev->next = newNode;
    }

    printf("项 %.2fx^%d 插入成功！\n", coef, exp);
    return 1;
}

// 5. 删除指定指数的项
int DeleteTerm(Polynomial *P, int exp)
{
    PolyNode *current = *P;
    PolyNode *prev = NULL;

    while (current != NULL)
    {
        if (current->exp == exp)
        {
            if (prev == NULL)
            {
                *P = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            printf("删除项: %.2fx^%d\n", current->coef, current->exp);
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }

    printf("未找到指数为 %d 的项！\n", exp);
    return 0;
}

// 6. 输出多项式
void PrintPolynomial(Polynomial P)
{
    if (P == NULL)
    {
        printf("多项式为空！\n");
        return;
    }

    printf("多项式: ");
    PolyNode *current = P;
    int firstTerm = 1;

    while (current != NULL)
    {
        if (current->coef > 0 && !firstTerm)
        {
            printf(" + ");
        }
        else if (current->coef < 0)
        {
            printf(" - ");
        }

        if (current->exp == 0)
        {
            printf("%.2f", fabs(current->coef));
        }
        else if (current->exp == 1)
        {
            if (fabs(current->coef) == 1)
            {
                printf("x");
            }
            else
            {
                printf("%.2fx", fabs(current->coef));
            }
        }
        else
        {
            if (fabs(current->coef) == 1)
            {
                printf("x^%d", current->exp);
            }
            else
            {
                printf("%.2fx^%d", fabs(current->coef), current->exp);
            }
        }

        firstTerm = 0;
        current = current->next;
    }
    printf("\n");
}

// 7. 多项式求值
float EvaluatePolynomial(Polynomial P, float x)
{
    float result = 0.0;
    PolyNode *current = P;

    while (current != NULL)
    {
        result += current->coef * pow(x, current->exp);
        current = current->next;
    }

    return result;
}

// 8. 多项式相加
Polynomial AddPolynomials(Polynomial P1, Polynomial P2)
{
    Polynomial result = NULL;
    PolyNode *current1 = P1;
    PolyNode *current2 = P2;
    PolyNode *tail = NULL;

    while (current1 != NULL && current2 != NULL)
    {
        PolyNode *newNode;

        if (current1->exp > current2->exp)
        {
            newNode = CreateNode(current1->coef, current1->exp);
            current1 = current1->next;
        }
        else if (current1->exp < current2->exp)
        {
            newNode = CreateNode(current2->coef, current2->exp);
            current2 = current2->next;
        }
        else
        {
            float sum = current1->coef + current2->coef;
            if (sum != 0)
            {
                newNode = CreateNode(sum, current1->exp);
            }
            else
            {
                newNode = NULL;
            }
            current1 = current1->next;
            current2 = current2->next;
        }

        if (newNode != NULL)
        {
            if (result == NULL)
            {
                result = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    // 处理剩余项
    while (current1 != NULL)
    {
        PolyNode *newNode = CreateNode(current1->coef, current1->exp);
        if (result == NULL)
        {
            result = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        current1 = current1->next;
    }

    while (current2 != NULL)
    {
        PolyNode *newNode = CreateNode(current2->coef, current2->exp);
        if (result == NULL)
        {
            result = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        current2 = current2->next;
    }

    return result;
}

// 9. 多项式相减
Polynomial SubtractPolynomials(Polynomial P1, Polynomial P2)
{
    Polynomial result = NULL;
    PolyNode *current1 = P1;
    PolyNode *current2 = P2;
    PolyNode *tail = NULL;

    while (current1 != NULL && current2 != NULL)
    {
        PolyNode *newNode;

        if (current1->exp > current2->exp)
        {
            newNode = CreateNode(current1->coef, current1->exp);
            current1 = current1->next;
        }
        else if (current1->exp < current2->exp)
        {
            newNode = CreateNode(-current2->coef, current2->exp);
            current2 = current2->next;
        }
        else
        {
            float diff = current1->coef - current2->coef;
            if (diff != 0)
            {
                newNode = CreateNode(diff, current1->exp);
            }
            else
            {
                newNode = NULL;
            }
            current1 = current1->next;
            current2 = current2->next;
        }

        if (newNode != NULL)
        {
            if (result == NULL)
            {
                result = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    // 处理剩余项
    while (current1 != NULL)
    {
        PolyNode *newNode = CreateNode(current1->coef, current1->exp);
        if (result == NULL)
        {
            result = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        current1 = current1->next;
    }

    while (current2 != NULL)
    {
        PolyNode *newNode = CreateNode(-current2->coef, current2->exp);
        if (result == NULL)
        {
            result = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        current2 = current2->next;
    }

    return result;
}

// 10. 多项式相乘
Polynomial MultiplyPolynomials(Polynomial P1, Polynomial P2)
{
    if (P1 == NULL || P2 == NULL)
    {
        return NULL;
    }

    Polynomial result = NULL;
    PolyNode *current1 = P1;

    while (current1 != NULL)
    {
        PolyNode *current2 = P2;
        Polynomial tempResult = NULL;
        PolyNode *tempTail = NULL;

        while (current2 != NULL)
        {
            float coef = current1->coef * current2->coef;
            int exp = current1->exp + current2->exp;

            if (coef != 0)
            {
                PolyNode *newNode = CreateNode(coef, exp);

                // 插入到临时结果中（保持有序）
                PolyNode *tempCurrent = tempResult;
                PolyNode *tempPrev = NULL;

                while (tempCurrent != NULL && tempCurrent->exp > exp)
                {
                    tempPrev = tempCurrent;
                    tempCurrent = tempCurrent->next;
                }

                if (tempCurrent != NULL && tempCurrent->exp == exp)
                {
                    tempCurrent->coef += coef;
                    free(newNode);
                }
                else
                {
                    if (tempPrev == NULL)
                    {
                        newNode->next = tempResult;
                        tempResult = newNode;
                    }
                    else
                    {
                        newNode->next = tempCurrent;
                        tempPrev->next = newNode;
                    }
                }
            }
            current2 = current2->next;
        }

        // 将临时结果加到最终结果中
        result = AddPolynomials(result, tempResult);

        // 释放临时结果
        ClearPolynomial(&tempResult);

        current1 = current1->next;
    }

    return result;
}

// 11. 多项式求导
Polynomial DerivativePolynomial(Polynomial P)
{
    Polynomial result = NULL;
    PolyNode *current = P;
    PolyNode *tail = NULL;

    while (current != NULL)
    {
        if (current->exp > 0)
        {
            float coef = current->coef * current->exp;
            int exp = current->exp - 1;

            PolyNode *newNode = CreateNode(coef, exp);

            if (result == NULL)
            {
                result = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
        current = current->next;
    }

    return result;
}

// 13. 获取多项式长度
int GetPolynomialLength(Polynomial P)
{
    int length = 0;
    PolyNode *current = P;

    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    return length;
}

// 14. 判断多项式是否为空
int IsPolynomialEmpty(Polynomial P)
{
    return P == NULL;
}

// 15. 输入多项式项
void InputTerm(float *coef, int *exp)
{
    printf("请输入项的系数: ");
    scanf("%f", coef);
    printf("请输入项的指数: ");
    scanf("%d", exp);
}

// 16. 显示菜单
void ShowMenu()
{
    printf("\n一元多项式运算系统\n");
    printf("1. 初始化多项式\n");
    printf("2. 插入项（无序）\n");
    printf("3. 插入项（有序）\n");
    printf("4. 删除项\n");
    printf("5. 输出多项式\n");
    printf("6. 多项式求值\n");
    printf("7. 多项式相加\n");
    printf("8. 多项式相减\n");
    printf("9. 多项式相乘\n");
    printf("10. 多项式求导\n");
    printf("11. 清空多项式\n");
    printf("12. 获取多项式长度\n");
    printf("13. 判断多项式是否为空\n");
    printf("0. 退出系统\n");
    printf("请选择操作: ");
}

int main()
{
    Polynomial poly1 = NULL, poly2 = NULL, result = NULL;
    int choice;
    float coef, x;
    int exp;

    // 初始化多项式
    InitPolynomial(&poly1);

    while (1)
    {
        ShowMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            // 释放所有内存
            ClearPolynomial(&poly1);
            ClearPolynomial(&poly2);
            ClearPolynomial(&result);
            printf("感谢使用一元多项式运算系统！\n");
            return 0;

        case 1:
            ClearPolynomial(&poly1);
            InitPolynomial(&poly1);
            break;

        case 2:
            InputTerm(&coef, &exp);
            InsertTerm(&poly1, coef, exp);
            break;

        case 3:
            InputTerm(&coef, &exp);
            InsertTermOrdered(&poly1, coef, exp);
            break;

        case 4:
            printf("请输入要删除的指数: ");
            scanf("%d", &exp);
            DeleteTerm(&poly1, exp);
            break;

        case 5:
            PrintPolynomial(poly1);
            break;

        case 6:
            printf("请输入x的值: ");
            scanf("%f", &x);
            printf("多项式在 x=%.2f 时的值为: %.2f\n", x, EvaluatePolynomial(poly1, x));
            break;

        case 7:
            printf("请输入第二个多项式:\n");
            InitPolynomial(&poly2);
            printf("输入第二个多项式的项数: ");
            int n;
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                InputTerm(&coef, &exp);
                InsertTermOrdered(&poly2, coef, exp);
            }
            printf("第一个多项式: ");
            PrintPolynomial(poly1);
            printf("第二个多项式: ");
            PrintPolynomial(poly2);
            result = AddPolynomials(poly1, poly2);
            printf("相加结果: ");
            PrintPolynomial(result);
            ClearPolynomial(&poly2);
            ClearPolynomial(&result);
            break;

        case 8:
            printf("请输入第二个多项式:\n");
            InitPolynomial(&poly2);
            printf("输入第二个多项式的项数: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                InputTerm(&coef, &exp);
                InsertTermOrdered(&poly2, coef, exp);
            }
            printf("第一个多项式: ");
            PrintPolynomial(poly1);
            printf("第二个多项式: ");
            PrintPolynomial(poly2);
            result = SubtractPolynomials(poly1, poly2);
            printf("相减结果: ");
            PrintPolynomial(result);
            ClearPolynomial(&poly2);
            ClearPolynomial(&result);
            break;

        case 9:
            printf("请输入第二个多项式:\n");
            InitPolynomial(&poly2);
            printf("输入第二个多项式的项数: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                InputTerm(&coef, &exp);
                InsertTermOrdered(&poly2, coef, exp);
            }
            printf("第一个多项式: ");
            PrintPolynomial(poly1);
            printf("第二个多项式: ");
            PrintPolynomial(poly2);
            result = MultiplyPolynomials(poly1, poly2);
            printf("相乘结果: ");
            PrintPolynomial(result);
            ClearPolynomial(&poly2);
            ClearPolynomial(&result);
            break;

        case 10:
            printf("原多项式: ");
            PrintPolynomial(poly1);
            result = DerivativePolynomial(poly1);
            printf("求导结果: ");
            PrintPolynomial(result);
            ClearPolynomial(&result);
            break;

        case 11:
            ClearPolynomial(&poly1);
            break;

        case 12:
            printf("多项式当前长度: %d\n", GetPolynomialLength(poly1));
            break;

        case 13:
            if (IsPolynomialEmpty(poly1))
            {
                printf("多项式为空\n");
            }
            else
            {
                printf("多项式不为空\n");
            }
            break;

        default:
            printf("无效的选择，请重新输入！\n");
            break;
        }
    }

    return 0;
}
