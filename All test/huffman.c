#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 256
#define MAX_CODE_LEN 100

// 1. 定义哈夫曼树结点结构
typedef struct HuffmanNode {
    char data;              // 字符
    int weight;             // 权重
    struct HuffmanNode *left;   // 左孩子
    struct HuffmanNode *right;  // 右孩子
} HuffmanNode;

// 哈夫曼编码表结构
typedef struct HuffmanCode {
    char data;              // 字符
    char code[MAX_CODE_LEN]; // 对应的哈夫曼编码
} HuffmanCode;

// 最小堆结构（用于构造哈夫曼树）
typedef struct MinHeap {
    HuffmanNode **nodes;    // 结点指针数组
    int size;               // 当前堆大小
    int capacity;           // 堆容量
} MinHeap;

// 创建新结点
HuffmanNode* createNode(char data, int weight) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->data = data;
    node->weight = weight;
    node->left = node->right = NULL;
    return node;
}

// 创建最小堆
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->nodes = (HuffmanNode**)malloc(capacity * sizeof(HuffmanNode*));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// 交换两个结点
void swapNodes(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

// 最小堆化
void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left]->weight < heap->nodes[smallest]->weight)
        smallest = left;

    if (right < heap->size && heap->nodes[right]->weight < heap->nodes[smallest]->weight)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&heap->nodes[smallest], &heap->nodes[idx]);
        minHeapify(heap, smallest);
    }
}

// 提取最小结点
HuffmanNode* extractMin(MinHeap* heap) {
    if (heap->size == 0)
        return NULL;

    HuffmanNode* minNode = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return minNode;
}

// 插入结点到最小堆
void insertMinHeap(MinHeap* heap, HuffmanNode* node) {
    if (heap->size == heap->capacity) {
        printf("Heap is full!\n");
        return;
    }

    heap->size++;
    int i = heap->size - 1;
    heap->nodes[i] = node;

    // 上浮调整
    while (i != 0 && heap->nodes[(i - 1) / 2]->weight > heap->nodes[i]->weight) {
        swapNodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 构建最小堆
void buildMinHeap(MinHeap* heap) {
    int n = heap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
        minHeapify(heap, i);
}

// 4. 构造哈夫曼树
HuffmanNode* buildHuffmanTree(char data[], int weights[], int n) {
    MinHeap* heap = createMinHeap(n);
    
    // 创建叶子结点并插入堆中
    for (int i = 0; i < n; i++) {
        heap->nodes[i] = createNode(data[i], weights[i]);
    }
    heap->size = n;
    buildMinHeap(heap);

    // 构造哈夫曼树
    while (heap->size > 1) {
        // 提取两个最小权重的结点
        HuffmanNode* left = extractMin(heap);
        HuffmanNode* right = extractMin(heap);
        
        // 创建新结点，权重为两个子结点权重之和
        HuffmanNode* parent = createNode('$', left->weight + right->weight);
        
        // 按照左小右大的原则连接
        if (left->weight <= right->weight) {
            parent->left = left;
            parent->right = right;
        } else {
            parent->left = right;
            parent->right = left;
        }
        
        // 将新结点插入堆中
        insertMinHeap(heap, parent);
    }
    
    HuffmanNode* root = extractMin(heap);
    free(heap->nodes);
    free(heap);
    return root;
}

// 5. 生成哈夫曼编码
void generateHuffmanCodes(HuffmanNode* root, char* code, int depth, HuffmanCode* codes, int* codeCount) {
    if (root == NULL) return;

    // 如果是叶子结点，保存编码
    if (root->left == NULL && root->right == NULL) {
        codes[*codeCount].data = root->data;
        strncpy(codes[*codeCount].code, code, depth);
        codes[*codeCount].code[depth] = '\0';
        (*codeCount)++;
        return;
    }

    // 左子树编码为0
    if (root->left != NULL) {
        code[depth] = '0';
        generateHuffmanCodes(root->left, code, depth + 1, codes, codeCount);
    }

    // 右子树编码为1
    if (root->right != NULL) {
        code[depth] = '1';
        generateHuffmanCodes(root->right, code, depth + 1, codes, codeCount);
    }
}

// 打印哈夫曼树（中序遍历）
void printHuffmanTree(HuffmanNode* root, int level) {
    if (root == NULL) return;

    printHuffmanTree(root->right, level + 1);
    
    for (int i = 0; i < level; i++)
        printf("    ");
    
    if (root->data == '$')
        printf("(%d)\n", root->weight);
    else
        printf("%c(%d)\n", root->data, root->weight);
    
    printHuffmanTree(root->left, level + 1);
}

// 计算WPL（带权路径长度）
int calculateWPL(HuffmanNode* root, int depth) {
    if (root == NULL) return 0;
    
    // 如果是叶子结点，返回权重×深度
    if (root->left == NULL && root->right == NULL)
        return root->weight * depth;
    
    // 递归计算左右子树的WPL
    return calculateWPL(root->left, depth + 1) + calculateWPL(root->right, depth + 1);
}

// 主函数
int main() {
    // 示例序列：A:5, B:9, C:12, D:13, E:16, F:45
    char data[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int weights[] = {5, 9, 12, 13, 16, 45};
    int n = sizeof(data) / sizeof(data[0]);

    printf("=== 哈夫曼树构造与编码 ===\n\n");
    
    // 1. 显示原始数据
    printf("1. 原始字符序列及其权重：\n");
    for (int i = 0; i < n; i++) {
        printf("   %c: %d\n", data[i], weights[i]);
    }
    printf("\n");

    // 2. 构造哈夫曼树
    printf("2. 构造哈夫曼树...\n");
    HuffmanNode* root = buildHuffmanTree(data, weights, n);
    
    // 3. 打印哈夫曼树形态（左小右大原则）
    printf("3. 哈夫曼树形态（左小右大原则）：\n");
    printf("   (括号内为权重，$表示内部结点)\n");
    printHuffmanTree(root, 0);
    printf("\n");

    // 4. 生成哈夫曼编码
    printf("4. 哈夫曼编码：\n");
    HuffmanCode codes[MAX_NODES];
    int codeCount = 0;
    char codeBuffer[MAX_CODE_LEN];
    generateHuffmanCodes(root, codeBuffer, 0, codes, &codeCount);
    
    for (int i = 0; i < codeCount; i++) {
        printf("   %c: %s\n", codes[i].data, codes[i].code);
    }
    printf("\n");

    // 5. 计算WPL
    printf("5. 编码的WPL（带权路径长度）：\n");
    int wpl = calculateWPL(root, 0);
    printf("   WPL = %d\n", wpl);
    
    // 验证WPL计算
    printf("   验证：");
    for (int i = 0; i < codeCount; i++) {
        int len = strlen(codes[i].code);
        for (int j = 0; j < n; j++) {
            if (codes[i].data == data[j]) {
                printf("%c(%d×%d)", codes[i].data, weights[j], len);
                if (i < codeCount - 1) printf(" + ");
                break;
            }
        }
    }
    printf(" = %d\n", wpl);

    // 释放内存（在实际应用中应该实现完整的释放函数）
    printf("\n程序执行完成！\n");
    
    return 0;
}
