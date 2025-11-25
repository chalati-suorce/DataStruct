#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 直接插入排序
void insertionSort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        // 将比key大的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 希尔排序
void shellSort(int arr[], int n) {
    // 使用希尔增量序列：n/2, n/4, ..., 1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // 对每个间隔进行插入排序
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            
            // 对间隔为gap的元素进行插入排序
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 复制数组
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

// 生成随机数组
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // 生成0-999的随机数
    }
}

// 从键盘输入数组
void inputArray(int arr[], int n) {
    printf("请输入 %d 个整数:\n", n);
    for (int i = 0; i < n; i++) {
        printf("第 %d 个数: ", i + 1);
        scanf("%d", &arr[i]);
    }
}

int main() {
    int choice, n;
    clock_t start, end;
    double cpu_time_used;
    
    printf("=== 排序算法比较程序 ===\n");
    printf("1. 手动输入数据进行排序\n");
    printf("2. 自动生成数据进行性能比较\n");
    printf("请选择模式 (1 或 2): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("请输入要排序的元素个数: ");
        scanf("%d", &n);
        
        int *arr = (int*)malloc(n * sizeof(int));
        int *arr_copy = (int*)malloc(n * sizeof(int));
        
        if (arr == NULL || arr_copy == NULL) {
            printf("内存分配失败!\n");
            return 1;
        }
        
        // 输入数据
        inputArray(arr, n);
        
        printf("\n原始数组: ");
        printArray(arr, n);
        
        // 直接插入排序
        copyArray(arr, arr_copy, n);
        start = clock();
        insertionSort(arr_copy, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("\n直接插入排序结果: ");
        printArray(arr_copy, n);
        printf("排序耗时: %f 秒\n", cpu_time_used);
        
        // 希尔排序
        copyArray(arr, arr_copy, n);
        start = clock();
        shellSort(arr_copy, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("\n希尔排序结果: ");
        printArray(arr_copy, n);
        printf("排序耗时: %f 秒\n", cpu_time_used);
        
        free(arr);
        free(arr_copy);
        
    } else if (choice == 2) {
        printf("请输入要生成的测试数据规模: ");
        scanf("%d", &n);
        
        int *arr = (int*)malloc(n * sizeof(int));
        int *arr_copy = (int*)malloc(n * sizeof(int));
        
        if (arr == NULL || arr_copy == NULL) {
            printf("内存分配失败!\n");
            return 1;
        }
        
        // 生成随机数据
        srand(time(NULL));
        generateRandomArray(arr, n);
        
        printf("\n生成 %d 个随机数进行性能测试...\n", n);
        
        // 测试直接插入排序性能
        copyArray(arr, arr_copy, n);
        start = clock();
        insertionSort(arr_copy, n);
        end = clock();
        double insertion_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // 测试希尔排序性能
        copyArray(arr, arr_copy, n);
        start = clock();
        shellSort(arr_copy, n);
        end = clock();
        double shell_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("\n=== 性能比较结果 ===\n");
        printf("数据规模: %d 个元素\n", n);
        printf("直接插入排序耗时: %f 秒\n", insertion_time);
        printf("希尔排序耗时: %f 秒\n", shell_time);
        printf("性能提升: %.2f%%\n", (insertion_time - shell_time) / insertion_time * 100);
        
        // 显示前10个元素验证排序正确性
        printf("\n排序后前10个元素: ");
        for (int i = 0; i < 10 && i < n; i++) {
            printf("%d ", arr_copy[i]);
        }
        printf("\n");
        
        free(arr);
        free(arr_copy);
        
    } else {
        printf("无效的选择!\n");
        return 1;
    }
    
    return 0;
}
