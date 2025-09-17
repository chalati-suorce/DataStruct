#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100  // 定义最大项数

// 多项式的项结构定义
typedef struct {
    float coef;    // 系数
    int expn;      // 指数
} PolyTerm;

// 多项式的顺序表示
typedef struct {
    PolyTerm *data;   // 存储空间基址
    int length;       // 多项式项数
} SqPoly;

// 初始化多项式
SqPoly* InitPoly() {
    SqPoly* P = (SqPoly*)malloc(sizeof(SqPoly));
    P->data = (PolyTerm*)malloc(MAXSIZE * sizeof(PolyTerm));
    P->length = 0;
    return P;
}

// 按指数降序插入多项式项
void InsertTerm(SqPoly* P, float coef, int expn) {
    int i, j;
    
    // 查找插入位置
    for(i = 0; i < P->length && P->data[i].expn > expn; i++);
    
    // 后移元素
    for(j = P->length; j > i; j--) {
        P->data[j] = P->data[j-1];
    }
    
    // 插入新项
    P->data[i].coef = coef;
    P->data[i].expn = expn;
    P->length++;
}

// 多项式相加
SqPoly* AddPoly(SqPoly* P1, SqPoly* P2) {
    SqPoly* P = InitPoly();
    int i = 0, j = 0;
    
    while(i < P1->length && j < P2->length) {
        if(P1->data[i].expn == P2->data[j].expn) {
            float sum = P1->data[i].coef + P2->data[j].coef;
            if(sum != 0) {
                InsertTerm(P, sum, P1->data[i].expn);
            }
            i++;
            j++;
        }
        else if(P1->data[i].expn > P2->data[j].expn) {
            InsertTerm(P, P1->data[i].coef, P1->data[i].expn);
            i++;
        }
        else {
            InsertTerm(P, P2->data[j].coef, P2->data[j].expn);
            j++;
        }
    }
    
    // 处理剩余项
    while(i < P1->length) {
        InsertTerm(P, P1->data[i].coef, P1->data[i].expn);
        i++;
    }
    while(j < P2->length) {
        InsertTerm(P, P2->data[j].coef, P2->data[j].expn);
        j++;
    }
    
    return P;
}

// 打印多项式
void PrintPoly(SqPoly* P) {
    int i;
    int first = 1;
    
    for(i = 0; i < P->length; i++) {
        if(first) {
            printf("%.2fx^%d", P->data[i].coef, P->data[i].expn);
            first = 0;
        }
        else {
            if(P->data[i].coef > 0) printf(" + ");
            printf("%.2fx^%d", P->data[i].coef, P->data[i].expn);
        }
    }
    printf("\n");
}
SqPoly* CreatePolyFromInput() {
    SqPoly* P = InitPoly();
    int n;
    float coef;
    int expn;
    
    printf("请输入多项式的项数: ");
    scanf("%d", &n);
    
    printf("请按指数降序输入每一项的系数和指数\n");
    for(int i = 0; i < n; i++) {
        printf("第%d项 - 系数: ", i+1);
        scanf("%f", &coef);
        printf("第%d项 - 指数: ", i+1);
        scanf("%d", &expn);
        InsertTerm(P, coef, expn);
    }
    
    return P;
}

int main() {
    printf("创建第一个多项式:\n");
    SqPoly* P1 = CreatePolyFromInput();
    
    printf("\n创建第二个多项式:\n");
    SqPoly* P2 = CreatePolyFromInput();
    
    printf("\nP1 = ");
    PrintPoly(P1);
    printf("P2 = ");
    PrintPoly(P2);
    
    SqPoly* P = AddPoly(P1, P2);
    printf("P1 + P2 = ");
    PrintPoly(P);
    
    // 释放内存
    free(P1->data);
    free(P1);
    free(P2->data);
    free(P2);
    free(P->data);
    free(P);
    
    return 0;
}