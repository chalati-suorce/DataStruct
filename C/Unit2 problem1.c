#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 多项式项的结构定义
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

// 输入多项式
void InputPoly(SqPoly* P) {
    int n;
    printf("请输入多项式的项数: ");
    scanf("%d", &n);
    
    printf("请按指数升序输入每一项的系数和指数\n");
    for(int i = 0; i < n; i++) {
        printf("第%d项 - 系数: ", i+1);
        scanf("%f", &P->data[i].coef);
        printf("第%d项 - 指数: ", i+1);
        scanf("%d", &P->data[i].expn);
    }
    P->length = n;
}

// 打印多项式
void PrintPoly(SqPoly* P) {
    if(P->length == 0) {
        printf("0\n");
        return;
    }
    
    for(int i = 0; i < P->length; i++) {
        if(i > 0 && P->data[i].coef > 0) printf("+");
        
        if(P->data[i].expn == 0)
            printf("%.2f", P->data[i].coef);
        else if(P->data[i].expn == 1)
            printf("%.2fx", P->data[i].coef);
        else
            printf("%.2fx^%d", P->data[i].coef, P->data[i].expn);
    }
    printf("\n");
}

// 多项式相加
SqPoly* AddPoly(SqPoly* P1, SqPoly* P2) {
    SqPoly* P = InitPoly();
    int i = 0, j = 0, k = 0;
    
    while(i < P1->length && j < P2->length) {
        if(P1->data[i].expn < P2->data[j].expn) {
            P->data[k] = P1->data[i];
            i++; k++;
        }
        else if(P1->data[i].expn > P2->data[j].expn) {
            P->data[k] = P2->data[j];
            j++; k++;
        }
        else {
            P->data[k].expn = P1->data[i].expn;
            P->data[k].coef = P1->data[i].coef + P2->data[j].coef;
            if(P->data[k].coef != 0) k++;
            i++; j++;
        }
    }
    
    while(i < P1->length) { P->data[k] = P1->data[i]; i++; k++; }
    while(j < P2->length) { P->data[k] = P2->data[j]; j++; k++; }
    
    P->length = k;
    return P;
}

// 多项式相减
SqPoly* SubPoly(SqPoly* P1, SqPoly* P2) {
    SqPoly* P = InitPoly();
    // 将P2的系数取反，然后调用加法
    SqPoly* temp = InitPoly();
    temp->length = P2->length;
    for(int i = 0; i < P2->length; i++) {
        temp->data[i].coef = -P2->data[i].coef;
        temp->data[i].expn = P2->data[i].expn;
    }
    P = AddPoly(P1, temp);
    free(temp->data);
    free(temp);
    return P;
}

// 多项式相乘
SqPoly* MulPoly(SqPoly* P1, SqPoly* P2) {
    SqPoly* P = InitPoly();
    if(P1->length == 0 || P2->length == 0) return P;
    
    // 用于临时存储乘积项
    PolyTerm temp[MAXSIZE];
    int k = 0;
    
    // 计算所有项的乘积
    for(int i = 0; i < P1->length; i++) {
        for(int j = 0; j < P2->length; j++) {
            temp[k].coef = P1->data[i].coef * P2->data[j].coef;
            temp[k].expn = P1->data[i].expn + P2->data[j].expn;
            k++;
        }
    }
    
    // 合并同类项
    for(int i = 0; i < k; i++) {
        if(temp[i].coef != 0) {
            float sum = temp[i].coef;
            for(int j = i + 1; j < k; j++) {
                if(temp[j].expn == temp[i].expn) {
                    sum += temp[j].coef;
                    temp[j].coef = 0;
                }
            }
            if(sum != 0) {
                P->data[P->length].coef = sum;
                P->data[P->length].expn = temp[i].expn;
                P->length++;
            }
        }
    }
    
    // 按指数升序排序
    for(int i = 0; i < P->length - 1; i++) {
        for(int j = 0; j < P->length - 1 - i; j++) {
            if(P->data[j].expn > P->data[j+1].expn) {
                PolyTerm t = P->data[j];
                P->data[j] = P->data[j+1];
                P->data[j+1] = t;
            }
        }
    }
    
    return P;
}

int main() {
    SqPoly *P1 = InitPoly();
    SqPoly *P2 = InitPoly();
    
    printf("输入第一个多项式：\n");
    InputPoly(P1);
    printf("输入第二个多项式：\n");
    InputPoly(P2);
    
    printf("\n第一个多项式：");
    PrintPoly(P1);
    printf("第二个多项式：");
    PrintPoly(P2);
    
    SqPoly *sum = AddPoly(P1, P2);
    printf("\n相加结果：");
    PrintPoly(sum);
    
    SqPoly *diff = SubPoly(P1, P2);
    printf("相减结果：");
    PrintPoly(diff);
    
    SqPoly *prod = MulPoly(P1, P2);
    printf("相乘结果：");
    PrintPoly(prod);
    
    // 释放内存
    free(P1->data); free(P1);
    free(P2->data); free(P2);
    free(sum->data); free(sum);
    free(diff->data); free(diff);
    free(prod->data); free(prod);
    
    return 0;
}