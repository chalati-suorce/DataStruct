#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 100  // 顺序表最大容量

// 多项式项：系数 + 指数
typedef struct {
    double coef;  // 系数
    int exp;      // 指数
} Term;

// 稀疏多项式的顺序表结构
typedef struct {
    Term data[MAX_TERMS];
    int length;  // 实际项数
} SparsePoly;

// 初始化多项式
void InitPoly(SparsePoly *poly) {
    poly->length = 0;
}

// 插入项（保持指数递增）
int InsertTerm(SparsePoly *poly, double coef, int exp) {
    if (poly->length >= MAX_TERMS) {
        printf("Error: 多项式项数超出最大容量！\n");
        return 0;
    }
    // 找到插入位置（保证指数从小到大）
    int i;
    for (i = poly->length - 1; i >= 0 && poly->data[i].exp > exp; i--) {
        poly->data[i + 1] = poly->data[i];
    }
    poly->data[i + 1].coef = coef;
    poly->data[i + 1].exp = exp;
    poly->length++;
    return 1;
}

// 多项式加法：C = A + B
void AddPoly(SparsePoly *A, SparsePoly *B, SparsePoly *C) {
    InitPoly(C);
    int i = 0, j = 0;
    while (i < A->length && j < B->length) {
        if (A->data[i].exp < B->data[j].exp) {
            InsertTerm(C, A->data[i].coef, A->data[i].exp);
            i++;
        } else if (A->data[i].exp > B->data[j].exp) {
            InsertTerm(C, B->data[j].coef, B->data[j].exp);
            j++;
        } else {
            double sum = A->data[i].coef + B->data[j].coef;
            if (sum != 0) {
                InsertTerm(C, sum, A->data[i].exp);
            }
            i++;
            j++;
        }
    }
    // 处理A剩余项
    while (i < A->length) {
        InsertTerm(C, A->data[i].coef, A->data[i].exp);
        i++;
    }
    // 处理B剩余项
    while (j < B->length) {
        InsertTerm(C, B->data[j].coef, B->data[j].exp);
        j++;
    }
}

// 打印多项式
void PrintPoly(SparsePoly *poly) {
    if (poly->length == 0) {
        printf("0\n");
        return;
    }
    for (int i = 0; i < poly->length; i++) {
        // 处理系数的符号和显示
        if (i == 0) {
            if (poly->data[i].coef != 1 && poly->data[i].coef != -1) {
                printf("%.1f", poly->data[i].coef);
            } else if (poly->data[i].coef == -1) {
                printf("-");
            }
        } else {
            if (poly->data[i].coef > 0) printf("+");
            if (poly->data[i].coef != 1 && poly->data[i].coef != -1) {
                printf("%.1f", fabs(poly->data[i].coef));
            } else if (poly->data[i].coef == -1) {
                printf("-");
            }
        }
        // 处理指数的显示
        if (poly->data[i].exp == 0) {
            continue;
        } else if (poly->data[i].exp == 1) {
            printf("x");
        } else {
            printf("x^%d", poly->data[i].exp);
        }
    }
    printf("\n");
}

int main() {
    SparsePoly poly1, poly2, polySum;
    InitPoly(&poly1);
    InitPoly(&poly2);
    
    // 构造多项式1: S(x) = 1 + 3x^10000 + 2x^20000
    InsertTerm(&poly1, 1, 0);
    InsertTerm(&poly1, 3, 10000);
    InsertTerm(&poly1, 2, 20000);
    
    // 构造多项式2: P(x) = 2x + 5x^10000 - 3x^30000
    InsertTerm(&poly2, 2, 1);
    InsertTerm(&poly2, 5, 10000);
    InsertTerm(&poly2, -3, 30000);
    
    printf("多项式1: ");
    PrintPoly(&poly1);
    printf("多项式2: ");
    PrintPoly(&poly2);
    
    // 多项式相加
    AddPoly(&poly1, &poly2, &polySum);
    printf("多项式1 + 多项式2 = ");
    PrintPoly(&polySum);
    
    return 0;
}