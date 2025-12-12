#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 10000


typedef struct {
    int weight; 
    int parent;  
    int lchild;    
    int rchild;    
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

// 在 HT[1...end] 中选择两个 parent 为 0 且权值最小的结点
// 保证 s1 的权值 <= s2 的权值
void Select(HuffmanTree HT, int end, int *s1, int *s2) {
    int min1 = MAX_VALUE;
    int min2 = MAX_VALUE;
    *s1 = 0;
    *s2 = 0;

    for (int i = 1; i <= end; i++) {
        if (HT[i].parent == 0 && HT[i].weight < min1) {
            min1 = HT[i].weight;
            *s1 = i;
        }
    }

    for (int i = 1; i <= end; i++) {
        if (HT[i].parent == 0 && i != *s1 && HT[i].weight < min2) {
            min2 = HT[i].weight;
            *s2 = i;
        }
    }
}

// 构造哈夫曼树（以结点值左小右大的原则）
void CreateHuffmanTree(HuffmanTree *HT, int *w, int n) {
    if (n <= 1) return;
    int m = 2 * n - 1;
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); 

    for (int i = 1; i <= n; i++) {
        (*HT)[i].weight = w[i - 1];
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
    }

    for (int i = n + 1; i <= m; i++) {
        (*HT)[i].weight = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
    }

    int s1, s2;
    for (int i = n + 1; i <= m; i++) {
        Select(*HT, i - 1, &s1, &s2);

        if ((*HT)[s1].weight > (*HT)[s2].weight) {
            int temp = s1;
            s1 = s2;
            s2 = temp;
        }
        
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;  // 左孩子为权值较小的
        (*HT)[i].rchild = s2;  // 右孩子为权值较大的
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

// 生成哈夫曼编码
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n) {
    *HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
    char *cd = (char *)malloc(n * sizeof(char)); 
    cd[n - 1] = '\0'; 

    for (int i = 1; i <= n; i++) {
        int start = n - 1;
        int c = i;
        int f = HT[i].parent;

        while (f != 0) {
            start--;
            if (HT[f].lchild == c)
                cd[start] = '0'; // 左孩子为 0
            else
                cd[start] = '1'; // 右孩子为 1
            
            c = f;
            f = HT[f].parent;
        }
        
        (*HC)[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy((*HC)[i], &cd[start]);
    }
    free(cd);
}

// 打印哈夫曼树形态（以缩进方式显示）
void PrintHuffmanTree(HuffmanTree HT, int root, int level) {
    if (root == 0) return;

    PrintHuffmanTree(HT, HT[root].rchild, level + 1);
    
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    
    if (HT[root].lchild == 0 && HT[root].rchild == 0) {
        printf("叶结点[%d]: %d\n", root, HT[root].weight);
    } else {
        printf("内部结点[%d]: %d\n", root, HT[root].weight);
    }

    PrintHuffmanTree(HT, HT[root].lchild, level + 1);
}

// 计算WPL（带权路径长度）
int CalculateWPL(HuffmanTree HT, HuffmanCode HC, int n) {
    int wpl = 0;
    for (int i = 1; i <= n; i++) {
        int len = strlen(HC[i]);
        wpl += HT[i].weight * len;
    }
    return wpl;
}

// 计算WPL的递归方法（从根结点开始）
int CalculateWPLRecursive(HuffmanTree HT, int root, int depth) {
    if (root == 0) return 0;

    if (HT[root].lchild == 0 && HT[root].rchild == 0) {
        return HT[root].weight * depth;
    }

    return CalculateWPLRecursive(HT, HT[root].lchild, depth + 1) + 
           CalculateWPLRecursive(HT, HT[root].rchild, depth + 1);
}

int main() {
    HuffmanTree HT;
    HuffmanCode HC;
    int n;

    printf(" 哈夫曼树构造与编码 \n\n");
    
    printf("输入节点的个数:\n");
    if(scanf("%d", &n) != 1) return 0;

    int *weights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("输入第%d个叶节点的权值:\n", i + 1);
        scanf("%d", &weights[i]);
    }

    printf("\n 构造哈夫曼树 \n");
    
    CreateHuffmanTree(&HT, weights, n);
    

    printf("\n哈夫曼树形态（左小右大原则）：\n");
    printf("说明：缩进表示层级，右子树在上，左子树在下\n");
    PrintHuffmanTree(HT, 2 * n - 1, 0); 

    CreateHuffmanCode(HT, &HC, n);

    printf("\n哈夫曼编码:\n");
    for (int i = 1; i <= n; i++) {
        printf("权值 %d 的编码: %s\n", HT[i].weight, HC[i]);
    }

    printf("\n 计算WPL（带权路径长度） \n");

    int wpl1 = CalculateWPL(HT, HC, n);
    printf("方法1（通过编码计算）: WPL = %d\n", wpl1);

    int wpl2 = CalculateWPLRecursive(HT, 2 * n - 1, 0);
    printf("方法2（递归计算）: WPL = %d\n", wpl2);

    if (wpl1 == wpl2) {
        printf("验证: 两种计算方法结果一致，WPL = %d\n", wpl1);
    } else {
        printf("警告: 两种计算方法结果不一致！\n");
    }
    
    printf("\n详细计算过程:\n");
    for (int i = 1; i <= n; i++) {
        int len = strlen(HC[i]);
        printf("权值 %d × 编码长度 %d = %d", HT[i].weight, len, HT[i].weight * len);
        if (i < n) printf(" + ");
    }
    printf(" = %d\n", wpl1);

    printf("\n程序执行完成！\n");
    system("pause");

    free(weights);
    free(HT);
    for(int i = 1; i <= n; i++) free(HC[i]);
    free(HC);

    return 0;
}
