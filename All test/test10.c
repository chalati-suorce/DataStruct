#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 10000 // 用于查找最小值的初始化大数

// 哈夫曼树结点结构
typedef struct {
    int weight;     // 权值
    int parent;     // 父结点下标
    int lchild;     // 左孩子下标
    int rchild;     // 右孩子下标
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

// 在 HT[1...end] 中选择两个 parent 为 0 且权值最小的结点
// 保证 s1 的权值 <= s2 的权值
void Select(HuffmanTree HT, int end, int *s1, int *s2) {
    int min1 = MAX_VALUE;
    int min2 = MAX_VALUE;
    *s1 = 0;
    *s2 = 0;

    // 第一次遍历，找最小 (s1)
    for (int i = 1; i <= end; i++) {
        if (HT[i].parent == 0 && HT[i].weight < min1) {
            min1 = HT[i].weight;
            *s1 = i;
        }
    }

    // 第二次遍历，找次小 (s2)
    for (int i = 1; i <= end; i++) {
        if (HT[i].parent == 0 && i != *s1 && HT[i].weight < min2) {
            min2 = HT[i].weight;
            *s2 = i;
        }
    }
}

// 构造哈夫曼树
void CreateHuffmanTree(HuffmanTree *HT, int *w, int n) {
    if (n <= 1) return;
    int m = 2 * n - 1; // 结点总数
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); 

    // 初始化前 n 个单元（叶子结点）
    for (int i = 1; i <= n; i++) {
        (*HT)[i].weight = w[i - 1];
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
    }

    // 初始化后 m-n 个单元
    for (int i = n + 1; i <= m; i++) {
        (*HT)[i].weight = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
    }

    // 构建树
    int s1, s2;
    for (int i = n + 1; i <= m; i++) {
        Select(*HT, i - 1, &s1, &s2);
        
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
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

int main() {
    HuffmanTree HT;
    HuffmanCode HC;
    int n;

    // 1. 输入部分：严格模仿截图格式
    printf("输入节点的个数:\n");
    if(scanf("%d", &n) != 1) return 0;

    int *weights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("输入第%d个叶节点的权值:\n", i);
        scanf("%d", &weights[i]);
    }

    // 2. 核心算法调用
    CreateHuffmanTree(&HT, weights, n);
    CreateHuffmanCode(HT, &HC, n);

    // 3. 输出部分：只输出编码
    printf("哈夫曼编码:\n");
    for (int i = 1; i <= n; i++) {
        printf("%s\n", HC[i]);
    }

    // 4. 模拟系统暂停
    // 这会在 Windows 命令行显示 "Press any key to continue . . ."
    system("pause");

    // 释放内存
    free(weights);
    free(HT);
    for(int i = 1; i <= n; i++) free(HC[i]);
    free(HC);

    return 0;
}