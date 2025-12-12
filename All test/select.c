#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 顺序查找表结构
typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqSearchTable;

// 折半查找表结构（已排序）
typedef struct {
    int data[MAX_SIZE];
    int length;
} BinSearchTable;

// 函数声明
void initSeqTable(SeqSearchTable *table);
void initBinTable(BinSearchTable *table);
void inputSeqTable(SeqSearchTable *table);
void outputSeqTable(SeqSearchTable *table);
void inputBinTable(BinSearchTable *table);
void outputBinTable(BinSearchTable *table);
int seqSearch(SeqSearchTable *table, int key, int *count);
void sortBinTable(BinSearchTable *table);
int BiSearch(int *A, int key, int n, int *count);
int binSearch(BinSearchTable *table, int key, int *count);
void compareSearchEfficiency(SeqSearchTable *seqTable, BinSearchTable *binTable);

int main() {
    SeqSearchTable seqTable;
    BinSearchTable binTable;
    int choice, key, position, count;
    
    initSeqTable(&seqTable);
    initBinTable(&binTable);
    
    do {
        printf("1. 创建顺序查找表\n");
        printf("2. 顺序查找\n");
        printf("3. 创建折半查找表（自动排序）\n");
        printf("4. 折半查找\n");
        printf("5. 显示顺序查找表\n");
        printf("6. 显示折半查找表\n");
        printf("7. 查找效率对比\n");
        printf("0. 退出\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                inputSeqTable(&seqTable);
                printf("顺序查找表创建成功！\n");
                break;
                
            case 2:
                if (seqTable.length == 0) {
                    printf("顺序查找表为空，请先创建表！\n");
                    break;
                }
                printf("请输入要查找的关键字: ");
                scanf("%d", &key);
                count = 0;
                position = seqSearch(&seqTable, key, &count);
                if (position != -1) {
                    printf("查找成功！关键字 %d 在表中的位置是: %d\n", key, position + 1);
                } else {
                    printf("查找失败！关键字 %d 不在表中\n", key);
                }
                printf("查找次数: %d\n", count);
                break;
                
            case 3:
                inputBinTable(&binTable);
                sortBinTable(&binTable);
                printf("折半查找表创建并排序成功！\n");
                break;
                
            case 4: {
                if (binTable.length == 0) {
                    printf("折半查找表为空，请先创建表！\n");
                    break;
                }
                printf("请输入要查找的关键字: ");
                scanf("%d", &key);
                int binCount = 0;
                position = binSearch(&binTable, key, &binCount);
                if (position != -1) {
                    printf("查找成功！关键字 %d 在表中的位置是: %d\n", key, position + 1);
                } else {
                    printf("查找失败！关键字 %d 不在表中\n", key);
                }
                printf("折半查找次数: %d\n", binCount);
                printf("查找表长度: %d\n", binTable.length);
                break;
            }
                
            case 5:
                if (seqTable.length == 0) {
                    printf("顺序查找表为空！\n");
                } else {
                    printf("顺序查找表内容: ");
                    outputSeqTable(&seqTable);
                }
                break;
                
            case 6:
                if (binTable.length == 0) {
                    printf("折半查找表为空！\n");
                } else {
                    printf("折半查找表内容: ");
                    outputBinTable(&binTable);
                }
                break;
                
            case 7:
                compareSearchEfficiency(&seqTable, &binTable);
                break;
                
            case 0:
                printf("感谢使用，再见！\n");
                break;
                
            default:
                printf("无效的选择，请重新输入！\n");
        }
    } while (choice != 0);
    
    return 0;
}

// 初始化顺序查找表
void initSeqTable(SeqSearchTable *table) {
    table->length = 0;
}

void initBinTable(BinSearchTable *table) {
    table->length = 0;
}

// 输入顺序查找表
void inputSeqTable(SeqSearchTable *table) {
    int n, i;
    printf("请输入顺序查找表的元素个数（不超过%d）: ", MAX_SIZE);
    scanf("%d", &n);
    
    if (n > MAX_SIZE || n <= 0) {
        printf("元素个数无效！\n");
        return;
    }
    
    table->length = n;
    printf("请输入 %d 个整数元素:\n", n);
    for (i = 0; i < n; i++) {
        printf("元素[%d]: ", i + 1);
        scanf("%d", &table->data[i]);
    }
}

// 输出顺序查找表
void outputSeqTable(SeqSearchTable *table) {
    int i;
    for (i = 0; i < table->length; i++) {
        printf("%d ", table->data[i]);
    }
    printf("\n");
}

// 输入折半查找表
void inputBinTable(BinSearchTable *table) {
    int n, i;
    printf("请输入折半查找表的元素个数（不超过%d）: ", MAX_SIZE);
    scanf("%d", &n);
    
    if (n > MAX_SIZE || n <= 0) {
        printf("元素个数无效！\n");
        return;
    }
    
    table->length = n;
    printf("请输入 %d 个整数元素:\n", n);
    for (i = 0; i < n; i++) {
        printf("元素[%d]: ", i + 1);
        scanf("%d", &table->data[i]);
    }
}

// 输出折半查找表
void outputBinTable(BinSearchTable *table) {
    int i;
    for (i = 0; i < table->length; i++) {
        printf("%d ", table->data[i]);
    }
    printf("\n");
}

// 顺序查找算法
// 返回查找到的位置序号（从0开始），否则返回-1，统计查找次数
int seqSearch(SeqSearchTable *table, int key, int *count) {
    int i;
    *count = 0;
    
    for (i = 0; i < table->length; i++) {
        (*count)++;
        if (table->data[i] == key) {
            return i;
        }
    }
    
    return -1;
}

// 对折半查找表进行排序（增序）
void sortBinTable(BinSearchTable *table) {
    int i, j, temp;
    
    for (i = 0; i < table->length - 1; i++) {
        for (j = 0; j < table->length - 1 - i; j++) {
            if (table->data[j] > table->data[j + 1]) {
                temp = table->data[j];
                table->data[j] = table->data[j + 1];
                table->data[j + 1] = temp;
            }
        }
    }
}

int BiSearch(int *A, int key, int n, int *count) {
    int low = 0, high = n - 1, mid;
    *count = 0;
    
    while (low <= high) {
        (*count)++;
        mid = (low + high) / 2;
        
        if (A[mid] == key) {
            return mid; // 找到，返回位置索引
        } else if (A[mid] < key) {
            low = mid + 1; // 在右半部分查找
        } else {
            high = mid - 1; // 在左半部分查找
        }
    }
    
    return -1; // 未找到
}

// 折半查找（包装函数）
int binSearch(BinSearchTable *table, int key, int *count) {
    return BiSearch(table->data, key, table->length, count);
}

// 查找效率对比函数
void compareSearchEfficiency(SeqSearchTable *seqTable, BinSearchTable *binTable) {
    // 检查两个表是否都已创建
    if (seqTable->length == 0) {
        printf("顺序查找表为空，请先创建顺序查找表！\n");
        return;
    }
    
    if (binTable->length == 0) {
        printf("折半查找表为空，请先创建折半查找表！\n");
        return;
    }
    
    // 检查两个表的长度是否相同（为了公平比较）
    if (seqTable->length != binTable->length) {
        printf("注意：两个查找表的长度不同（顺序表长度：%d，折半表长度：%d）\n", 
               seqTable->length, binTable->length);
        printf("这可能会影响效率对比的公平性。\n");
    }
    
    int key;
    printf("请输入要查找的关键字: ");
    scanf("%d", &key);
    
    printf("\n 查找效率对比 \n");
    printf("查找关键字: %d\n", key);
    printf("顺序查找表长度: %d\n", seqTable->length);
    printf("折半查找表长度: %d\n", binTable->length);
    
    // 顺序查找
    int seqCount = 0;
    int seqPosition = seqSearch(seqTable, key, &seqCount);
    
    printf("1. 顺序查找结果:\n");
    if (seqPosition != -1) {
        printf("   查找成功！位置: %d\n", seqPosition + 1);
    } else {
        printf("   查找失败！关键字不在表中\n");
    }
    printf("   查找次数: %d\n", seqCount);
    printf("   平均查找长度(ASL): %.2f\n", (float)(seqCount) / (seqPosition != -1 ? 1 : seqTable->length));
    
    // 折半查找
    int binCount = 0;
    int binPosition = binSearch(binTable, key, &binCount);
    
    printf("\n2. 折半查找结果:\n");
    if (binPosition != -1) {
        printf("   查找成功！位置: %d\n", binPosition + 1);
    } else {
        printf("   查找失败！关键字不在表中\n");
    }
    printf("   查找次数: %d\n", binCount);
    printf("   平均查找长度(ASL): %.2f\n", (float)(binCount) / (binPosition != -1 ? 1 : binTable->length));
    
    printf("\n 效率对比分析 \n");
    
    // 比较查找次数
    if (seqPosition == -1 && binPosition == -1) {
        printf("两种查找算法都未找到关键字。\n");
        printf("顺序查找需要遍历整个表，查找次数: %d\n", seqCount);
        printf("折半查找需要 log2(n) 次比较，查找次数: %d\n", binCount);
    } else if (seqPosition != -1 && binPosition != -1) {
        printf("两种查找算法都成功找到关键字。\n");
        
        if (seqCount < binCount) {
            printf("顺序查找更快，少用了 %d 次比较\n", binCount - seqCount);
            printf("说明：当关键字在表的前部时，顺序查找可能比折半查找更快\n");
        } else if (seqCount > binCount) {
            printf("折半查找更快，少用了 %d 次比较\n", seqCount - binCount);
            printf("说明：折半查找的时间复杂度为 O(log n)，通常比顺序查找的 O(n) 更快\n");
        } else {
            printf("两种查找算法的查找次数相同\n");
        }
    } else {
        printf("一种算法找到关键字，另一种未找到\n");
    }
    
    // 理论复杂度对比
    printf("\n理论复杂度对比:\n");
    printf("顺序查找: O(n) - 线性时间复杂度\n");
    printf("折半查找: O(log n) - 对数时间复杂度\n");
    
    // 实际效率比
    if (seqCount > 0 && binCount > 0) {
        float efficiencyRatio = (float)seqCount / binCount;
        printf("\n实际效率比 (顺序查找次数/折半查找次数): %.2f\n", efficiencyRatio);
        
        if (efficiencyRatio > 1.0) {
            printf("折半查找效率是顺序查找的 %.2f 倍\n", efficiencyRatio);
        } else if (efficiencyRatio < 1.0) {
            printf("顺序查找效率是折半查找的 %.2f 倍\n", 1.0 / efficiencyRatio);
        }
    }
    
}
