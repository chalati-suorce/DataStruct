#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 澶氶」寮忛」鐨勭粨鏋勫畾涔?
typedef struct {
    float coef;    // 绯绘暟
    int expn;      // 鎸囨暟
} PolyTerm;

// 澶氶」寮忕殑椤哄簭琛ㄧず
typedef struct {
    PolyTerm *data;   // 瀛樺偍绌洪棿鍩哄潃
    int length;       // 澶氶」寮忛」鏁?
} SqPoly;

// 鍒濆鍖栧椤瑰紡
SqPoly* InitPoly() {
    SqPoly* P = (SqPoly*)malloc(sizeof(SqPoly));
    P->data = (PolyTerm*)malloc(MAXSIZE * sizeof(PolyTerm));
    P->length = 0;
    return P;
}

// 杈撳叆澶氶」寮?
void InputPoly(SqPoly* P) {
    int n;
    printf("璇疯緭鍏ュ椤瑰紡鐨勯」鏁? ");
    scanf("%d", &n);
    
    printf("璇锋寜鎸囨暟鍗囧簭杈撳叆姣忎竴椤圭殑绯绘暟鍜屾寚鏁癨n");
    for(int i = 0; i < n; i++) {
        printf("绗?d椤?- 绯绘暟: ", i+1);
        scanf("%f", &P->data[i].coef);
        printf("绗?d椤?- 鎸囨暟: ", i+1);
        scanf("%d", &P->data[i].expn);
    }
    P->length = n;
}

// 鎵撳嵃澶氶」寮?
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

// 澶氶」寮忕浉鍔?
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

// 澶氶」寮忕浉鍑?
SqPoly* SubPoly(SqPoly* P1, SqPoly* P2) {
    SqPoly* P = InitPoly();
    // 灏哖2鐨勭郴鏁板彇鍙嶏紝鐒跺悗璋冪敤鍔犳硶
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

// 澶氶」寮忕浉涔?
SqPoly* MulPoly(SqPoly* P1, SqPoly* P2) {
    SqPoly* P = InitPoly();
    if(P1->length == 0 || P2->length == 0) return P;
    
    // 鐢ㄤ簬涓存椂瀛樺偍涔樼Н椤?
    PolyTerm temp[MAXSIZE];
    int k = 0;
    
    // 璁＄畻鎵€鏈夐」鐨勪箻绉?
    for(int i = 0; i < P1->length; i++) {
        for(int j = 0; j < P2->length; j++) {
            temp[k].coef = P1->data[i].coef * P2->data[j].coef;
            temp[k].expn = P1->data[i].expn + P2->data[j].expn;
            k++;
        }
    }
    
    // 鍚堝苟鍚岀被椤?
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
    
    // 鎸夋寚鏁板崌搴忔帓搴?
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
    
    printf("杈撳叆绗竴涓椤瑰紡锛歕n");
    InputPoly(P1);
    printf("杈撳叆绗簩涓椤瑰紡锛歕n");
    InputPoly(P2);
    
    printf("\n绗竴涓椤瑰紡锛?);
    PrintPoly(P1);
    printf("绗簩涓椤瑰紡锛?);
    PrintPoly(P2);
    
    SqPoly *sum = AddPoly(P1, P2);
    printf("\n鐩稿姞缁撴灉锛?);
    PrintPoly(sum);
    
    SqPoly *diff = SubPoly(P1, P2);
    printf("鐩稿噺缁撴灉锛?);
    PrintPoly(diff);
    
    SqPoly *prod = MulPoly(P1, P2);
    printf("鐩镐箻缁撴灉锛?);
    PrintPoly(prod);
    
    // 閲婃斁鍐呭瓨
    free(P1->data); free(P1);
    free(P2->data); free(P2);
    free(sum->data); free(sum);
    free(diff->data); free(diff);
    free(prod->data); free(prod);
    
    return 0;
}


