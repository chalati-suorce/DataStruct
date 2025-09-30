#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 100  // 椤哄簭琛ㄦ渶澶у閲?

// 澶氶」寮忛」锛氱郴鏁?+ 鎸囨暟
typedef struct {
    double coef;  // 绯绘暟
    int exp;      // 鎸囨暟
} Term;

// 绋€鐤忓椤瑰紡鐨勯『搴忚〃缁撴瀯
typedef struct {
    Term data[MAX_TERMS];
    int length;  // 瀹為檯椤规暟
} SparsePoly;

// 鍒濆鍖栧椤瑰紡
void InitPoly(SparsePoly *poly) {
    poly->length = 0;
}

// 鎻掑叆椤癸紙淇濇寔鎸囨暟閫掑锛?
int InsertTerm(SparsePoly *poly, double coef, int exp) {
    if (poly->length >= MAX_TERMS) {
        printf("Error: 澶氶」寮忛」鏁拌秴鍑烘渶澶у閲忥紒\n");
        return 0;
    }
    // 鎵惧埌鎻掑叆浣嶇疆锛堜繚璇佹寚鏁颁粠灏忓埌澶э級
    int i;
    for (i = poly->length - 1; i >= 0 && poly->data[i].exp > exp; i--) {
        poly->data[i + 1] = poly->data[i];
    }
    poly->data[i + 1].coef = coef;
    poly->data[i + 1].exp = exp;
    poly->length++;
    return 1;
}

// 澶氶」寮忓姞娉曪細C = A + B
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
    // 澶勭悊A鍓╀綑椤?
    while (i < A->length) {
        InsertTerm(C, A->data[i].coef, A->data[i].exp);
        i++;
    }
    // 澶勭悊B鍓╀綑椤?
    while (j < B->length) {
        InsertTerm(C, B->data[j].coef, B->data[j].exp);
        j++;
    }
}

// 鎵撳嵃澶氶」寮?
void PrintPoly(SparsePoly *poly) {
    if (poly->length == 0) {
        printf("0\n");
        return;
    }
    for (int i = 0; i < poly->length; i++) {
        // 澶勭悊绯绘暟鐨勭鍙峰拰鏄剧ず
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
        // 澶勭悊鎸囨暟鐨勬樉绀?
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
    
    // 鏋勯€犲椤瑰紡1: S(x) = 1 + 3x^10000 + 2x^20000
    InsertTerm(&poly1, 1, 0);
    InsertTerm(&poly1, 3, 10000);
    InsertTerm(&poly1, 2, 20000);
    
    // 鏋勯€犲椤瑰紡2: P(x) = 2x + 5x^10000 - 3x^30000
    InsertTerm(&poly2, 2, 1);
    InsertTerm(&poly2, 5, 10000);
    InsertTerm(&poly2, -3, 30000);
    
    printf("澶氶」寮?: ");
    PrintPoly(&poly1);
    printf("澶氶」寮?: ");
    PrintPoly(&poly2);
    
    // 澶氶」寮忕浉鍔?
    AddPoly(&poly1, &poly2, &polySum);
    printf("澶氶」寮? + 澶氶」寮? = ");
    PrintPoly(&polySum);
    
    return 0;
}
