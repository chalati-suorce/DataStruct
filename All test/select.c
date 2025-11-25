#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 顺序查找函数
int sequentialSearch(int *A, int key, int n, int *count) {
    *count = 0; // 初始化查找次数
    for (int i = 0; i < n; i++) {
        (*count)++; // 每次比较计数
        if (A[i] == key) {
            return i; // 找到返回位置序号
        }
    }
    return -1; // 未找到返回-1
}

// 折半查找函数
int BiSearch(int *A, int key, int n) {
    int low = 0, high = n - 1;
    int count = 0; // 查找次数
    
    while (low <= high) {
        count++;
        int mid = (low + high) / 2;
        
        if (A[mid] == key) {
            printf("折半查找次数: %d\n", count);
            return mid; // 找到返回位置序号
        } else if (A[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    printf("折半查找次数: %d\n", count);
    return -1; // 未找到返回-1
}

// 输入函数
void input(int *A, int *n) {
    printf("请输入顺序表的元素个数 (最大%d): ", MAX_SIZE);
    scanf("%d", n);
    
    if (*n > MAX_SIZE || *n <= 0) {
        printf("输入错误！元素个数应在1到%d之间\n", MAX_SIZE);
        *n = 0;
        return;
    }
    
    printf("请输入%d个整数:\n", *n);
    for (int i = 0; i < *n; i++) {
        scanf("%d", &A[i]);
    }
}

// 输出函数
void output(int *A, int n) {
    if (n == 0) {
        printf("顺序表为空\n");
        return;
    }
    
    printf("顺序表内容: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// 冒泡排序函数（用于折半查找前的排序）
void bubbleSort(int *A, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                // 交换元素
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

int main() {
    int A[MAX_SIZE]; // 定义一维数组存储顺序表
    int n = 0;       // 顺序表长度
    int choice, key, position, count;
    
    printf("=== 顺序查找和折半查找演示程序 ===\n");
    
    while (1) {
        printf("\n请选择操作:\n");
        printf("1. 输入顺序表\n");
        printf("2. 显示顺序表\n");
        printf("3. 顺序查找\n");
        printf("4. 创建折半查找表（排序）\n");
        printf("5. 折半查找\n");
        printf("6. 退出\n");
        printf("请输入选择 (1-6): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                input(A, &n);
                break;
                
            case 2:
                output(A, n);
                break;
                
            case 3:
                if (n == 0) {
                    printf("请先输入顺序表！\n");
                    break;
                }
                printf("请输入要查找的关键字: ");
                scanf("%d", &key);
                position = sequentialSearch(A, key, n, &count);
                if (position != -1) {
                    printf("顺序查找成功！位置: %d, 查找次数: %d\n", position, count);
                } else {
                    printf("顺序查找失败！未找到关键字 %d, 查找次数: %d\n", key, count);
                }
                break;
                
            case 4:
                if (n == 0) {
                    printf("请先输入顺序表！\n");
                    break;
                }
                bubbleSort(A, n);
                printf("顺序表已按增序排序，可用于折半查找\n");
                printf("排序后的顺序表: ");
                output(A, n);
                printf("查找表长度: %d\n", n);
                break;
                
            case 5:
                if (n == 0) {
                    printf("请先输入顺序表！\n");
                    break;
                }
                printf("请输入要查找的关键字: ");
                scanf("%d", &key);
                position = BiSearch(A, key, n);
                if (position != -1) {
                    printf("折半查找成功！位置: %d\n", position);
                } else {
                    printf("折半查找失败！未找到关键字 %d\n", key);
                }
                break;
                
            case 6:
                printf("程序退出，谢谢使用！\n");
                return 0;
                
            default:
                printf("无效选择，请重新输入！\n");
        }
    }
    
    return 0;
}
