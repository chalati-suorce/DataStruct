#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 一元多项式节点结构体
typedef struct PolyNode {
    float coef;           // 系数
    int exp;              // 指数
    struct PolyNode *next; // 指向下一个节点的指针
} PolyNode, *Polynomial;

// 1、初始化单链表，构造一个带头结点的单链表L
Polynomial InitPolynomial() {
    Polynomial L = (Polynomial)malloc(sizeof(PolyNode));
    if (L == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    L->coef = 0;
    L->exp = -1;  // 头节点指数设为-1表示无效
    L->next = NULL;
    printf("一元多项式链表初始化成功！\n");
    return L;
}

// 按指数降序插入节点（保持多项式有序）
void InsertNode(Polynomial poly, float coef, int exp) {
    if (coef == 0) return; // 系数为0不插入
    
    PolyNode *p = poly->next;
    PolyNode *prev = poly;
    
    // 查找插入位置（按指数降序排列）
    while (p != NULL && p->exp > exp) {
        prev = p;
        p = p->next;
    }
    
    // 如果找到相同指数的节点，合并系数
    if (p != NULL && p->exp == exp) {
        p->coef += coef;
        if (p->coef == 0) {
            // 如果合并后系数为0，删除该节点
            prev->next = p->next;
            free(p);
        }
        return;
    }
    
    // 创建新节点并插入
    PolyNode *newNode = (PolyNode*)malloc(sizeof(PolyNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = p;
    prev->next = newNode;
}

// 2、建立长度为n的单链表并输出，创建过程中，对结点数值进行判断，形成一个有序表
void CreatePolynomial(Polynomial L, int n) {
    if (n <= 0) {
        printf("多项式项数必须大于0！\n");
        return;
    }
    
    printf("请依次输入%d个项的系数和指数（格式：系数 指数）：\n", n);
    for (int i = 0; i < n; i++) {
        float coef;
        int exp;
        scanf("%f %d", &coef, &exp);
        InsertNode(L, coef, exp);
    }
    printf("一元多项式创建成功！\n");
}

// 显示多项式
void DisplayPolynomial(Polynomial L) {
    if (L->next == NULL) {
        printf("0\n");
        return;
    }
    
    PolyNode *p = L->next;
    int firstTerm = 1;
    
    printf("多项式：");
    while (p != NULL) {
        if (p->coef > 0 && !firstTerm) {
            printf(" + ");
        } else if (p->coef < 0) {
            printf(" - ");
        }
        
        // 输出系数（绝对值）
        if (p->exp == 0 || fabs(p->coef) != 1) {
            printf("%.1f", fabs(p->coef));
        }
        
        // 输出指数部分
        if (p->exp > 0) {
            printf("x");
            if (p->exp > 1) {
                printf("^%d", p->exp);
            }
        }
        
        firstTerm = 0;
        p = p->next;
    }
    printf("\n");
}

// 3、查找元素e，返回其序号（这里查找特定指数的项）
int LocateExp(Polynomial L, int exp) {
    PolyNode *p = L->next;
    int pos = 1;
    
    while (p != NULL) {
        if (p->exp == exp) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    
    return -1; // 未找到返回-1
}

// 4、在第i个位置插入新元素e（插入新的多项式项）
int PolyInsert(Polynomial L, int i, float coef, int exp) {
    if (i < 1) {
        printf("插入位置无效！\n");
        return 0;
    }
    
    PolyNode *p = L;
    int j = 0;
    
    // 找到第i-1个节点
    while (p != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    
    if (p == NULL) {
        printf("插入位置超出链表长度！\n");
        return 0;
    }
    
    // 创建新节点
    PolyNode *newNode = (PolyNode*)malloc(sizeof(PolyNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }
    newNode->coef = coef;
    newNode->exp = exp;
    
    // 插入节点
    newNode->next = p->next;
    p->next = newNode;
    
    printf("项 %.1fx^%d 已插入到第%d个位置\n", coef, exp, i);
    return 1;
}

// 5、删除第i个位置的元素，并由e返回其值
int PolyDelete(Polynomial L, int i, float *coef, int *exp) {
    if (i < 1) {
        printf("删除位置无效！\n");
        return 0;
    }
    
    PolyNode *p = L;
    int j = 0;
    
    // 找到第i-1个节点
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    
    if (p->next == NULL) {
        printf("删除位置超出链表长度！\n");
        return 0;
    }
    
    // 删除节点
    PolyNode *q = p->next;
    *coef = q->coef;
    *exp = q->exp;
    p->next = q->next;
    free(q);
    
    printf("第%d个位置的项 %.1fx^%d 已被删除\n", i, *coef, *exp);
    return 1;
}

// 6、依次取出两张单链表的结点，对数值进行判断和计算，完成两张有序单链表的合并
// 这里实现两个多项式的相加
Polynomial AddPolynomials(Polynomial La, Polynomial Lb) {
    Polynomial Lc = InitPolynomial();
    PolyNode *pa = La->next;
    PolyNode *pb = Lb->next;
    
    // 遍历两个多项式，按指数降序合并
    while (pa != NULL && pb != NULL) {
        if (pa->exp > pb->exp) {
            InsertNode(Lc, pa->coef, pa->exp);
            pa = pa->next;
        } else if (pa->exp < pb->exp) {
            InsertNode(Lc, pb->coef, pb->exp);
            pb = pb->next;
        } else {
            // 指数相同，系数相加
            float sumCoef = pa->coef + pb->coef;
            if (sumCoef != 0) {
                InsertNode(Lc, sumCoef, pa->exp);
            }
            pa = pa->next;
            pb = pb->next;
        }
    }
    
    // 处理剩余节点
    while (pa != NULL) {
        InsertNode(Lc, pa->coef, pa->exp);
        pa = pa->next;
    }
    
    while (pb != NULL) {
        InsertNode(Lc, pb->coef, pb->exp);
        pb = pb->next;
    }
    
    printf("两个多项式相加完成！\n");
    return Lc;
}

// 释放多项式内存
void FreePolynomial(Polynomial L) {
    PolyNode *p = L;
    while (p != NULL) {
        PolyNode *temp = p;
        p = p->next;
        free(temp);
    }
}

// 计算多项式在x处的值
float EvaluatePolynomial(Polynomial L, float x) {
    float result = 0.0;
    PolyNode *p = L->next;
    
    while (p != NULL) {
        result += p->coef * pow(x, p->exp);
        p = p->next;
    }
    
    return result;
}

// 主函数 - 演示一元多项式运算系统
int main() {
    printf("基于链表的一元多项式运算系统\n\n");
    
    // 1、初始化单链表
    Polynomial poly1 = InitPolynomial();
    
    // 2、建立长度为n的单链表
    int n;
    printf("请输入第一个多项式的项数：");
    scanf("%d", &n);
    CreatePolynomial(poly1, n);
    DisplayPolynomial(poly1);
    
    // 3、查找元素
    int searchExp;
    printf("\n请输入要查找的指数：");
    scanf("%d", &searchExp);
    int pos = LocateExp(poly1, searchExp);
    if (pos != -1) {
        printf("指数为%d的项在多项式中的位置是：%d\n", searchExp, pos);
    } else {
        printf("指数为%d的项不在多项式中\n", searchExp);
    }
    
    // 4、插入元素
    int insertPos;
    float insertCoef;
    int insertExp;
    printf("\n请输入要插入的位置、系数和指数（格式：位置 系数 指数）：");
    scanf("%d %f %d", &insertPos, &insertCoef, &insertExp);
    if (PolyInsert(poly1, insertPos, insertCoef, insertExp)) {
        DisplayPolynomial(poly1);
    }
    
    // 5、删除元素
    int deletePos;
    float deletedCoef;
    int deletedExp;
    printf("\n请输入要删除的位置：");
    scanf("%d", &deletePos);
    if (PolyDelete(poly1, deletePos, &deletedCoef, &deletedExp)) {
        DisplayPolynomial(poly1);
    }
    
    // 6、创建第二个多项式并相加
    printf("\n创建第二个多项式用于相加\n");
    Polynomial poly2 = InitPolynomial();
    int n2;
    printf("请输入第二个多项式的项数：");
    scanf("%d", &n2);
    CreatePolynomial(poly2, n2);
    printf("第二个多项式：");
    DisplayPolynomial(poly2);
    
    // 多项式相加
    Polynomial polySum = AddPolynomials(poly1, poly2);
    printf("相加结果：");
    DisplayPolynomial(polySum);
    
    // 计算多项式值
    float x;
    printf("\n请输入x的值来计算多项式：");
    scanf("%f", &x);
    float value1 = EvaluatePolynomial(poly1, x);
    float value2 = EvaluatePolynomial(poly2, x);
    float valueSum = EvaluatePolynomial(polySum, x);
    printf("多项式1在x=%.1f处的值：%.2f\n", x, value1);
    printf("多项式2在x=%.1f处的值：%.2f\n", x, value2);
    printf("和多项式在x=%.1f处的值：%.2f\n", x, valueSum);
    
    // 验证相加结果
    if (fabs(value1 + value2 - valueSum) < 0.001) {
        printf("多项式相加验证正确！\n");
    } else {
        printf("多项式相加验证有误！\n");
    }
    
    // 释放内存
    FreePolynomial(poly1);
    FreePolynomial(poly2);
    FreePolynomial(polySum);
    
    printf("\n一元多项式运算系统演示完毕！\n");
    return 0;
}
