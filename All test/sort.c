#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000

int original[MAX_SIZE];
int arr[MAX_SIZE];
int tempArr[MAX_SIZE];
int n = 0;
int print_steps = 1;

void printMenu();
void inputData();
void resetArray();
void printArray(const char* prefix);
void swap(int *a, int *b);

void DirectInsertSort();
void BinaryInsertSort();
void ShellSort();
void BubbleSort();
void QuickSort();
void SelectSort();
void HeapSort();
void MergeSort();
void EfficiencyCompare();

// --- 主函数 ---
int main() {
    int choice;
    srand((unsigned)time(NULL)); 

    while (1) {
        printMenu();
        printf("请选择：");
        scanf("%d", &choice);

        if (choice >= 2 && choice <= 9 && n == 0) {
            printf("请先执行 [1] 录入数据！\n");
            system("pause");
            continue;
        }

        switch (choice) {
            case 0: system("cls"); break;
            case 1: inputData(); break;
            case 2: resetArray(); DirectInsertSort(); break;
            case 3: resetArray(); BinaryInsertSort(); break;
            case 4: resetArray(); ShellSort(); break;
            case 5: resetArray(); BubbleSort(); break;
            case 6: resetArray(); QuickSort(); break;
            case 7: resetArray(); SelectSort(); break;
            case 8: resetArray(); HeapSort(); break;
            case 9: resetArray(); MergeSort(); break;
            case 10: EfficiencyCompare(); break;
            case 886: printf("退出程序。\n"); return 0;
            default: printf("输入错误，请重新选择。\n");
        }
        
        if (choice != 0 && choice != 1 && choice != 10) {
            printf("\n排序完成，按回车键继续...");
            getchar(); getchar();
        }
    }
    return 0;
}

// --- 辅助函数 ---

void printMenu() {
    printf("        0 清    屏        \n");
    printf("        1 录入数据        \n");
    printf("        2 直接插入排序    \n");
    printf("        3 折半插入排序    \n");
    printf("        4 希尔排序        \n");
    printf("        5 冒泡排序        \n");
    printf("        6 快速排序        \n");
    printf("        7 选择排序        \n");
    printf("        8 堆排序          \n");
    printf("        9 二路归并排序    \n");
    printf("        10 效率比较       \n");
    printf("        886 退   出       \n");
}

void inputData() {
    printf("请输入数组元素的个数 (范围: [1, %d]): ", MAX_SIZE);
    scanf("%d", &n);
    if (n > MAX_SIZE || n < 1) {
        printf("数量超出范围！\n"); n = 0; return;
    }
    printf("请输入%d个整数:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &original[i]);
    }
    resetArray();
    printf("数据录入完毕。\n");
}

void resetArray() {
    for (int i = 0; i < n; i++) arr[i] = original[i];
    print_steps = 1; // 默认开启打印
}

void printArray(const char* prefix) {
    if (!print_steps) return; // 如果是静默模式，不打印
    printf("%s", prefix);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a; *a = *b; *b = temp;
}

// --- 2. 直接插入排序 ---
void DirectInsertSort() {
    printArray("原数组: ");
    int i, j, temp;
    for (i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            temp = arr[i];
            for (j = i - 1; j >= 0 && arr[j] > temp; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = temp;
        }
        if (print_steps) { printf("第%d趟排序后: ", i); printArray(""); }
    }
}

// --- 3. 折半插入排序 ---
void BinaryInsertSort() {
    printArray("原数组: ");
    int i, j, temp, low, high, mid;
    for (i = 1; i < n; i++) {
        temp = arr[i];
        low = 0; high = i - 1;
        while (low <= high) {
            mid = (low + high) / 2;
            if (arr[mid] > temp) high = mid - 1;
            else low = mid + 1;
        }
        for (j = i - 1; j >= high + 1; j--) arr[j + 1] = arr[j];
        arr[high + 1] = temp;
        
        if (print_steps) { printf("第%d趟排序后: ", i); printArray(""); }
    }
}

// --- 4. 希尔排序 ---
void ShellSort() {
    printArray("原数组: ");
    int i, j, gap, temp, pass = 1;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];
            for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = temp;
        }
        if (print_steps) { printf("第%d趟(增量%d): ", pass++, gap); printArray(""); }
    }
}

// --- 5. 冒泡排序 ---
void BubbleSort() {
    printArray("原数组: ");
    int i, j, flag;
    for (i = 0; i < n - 1; i++) {
        flag = 0;
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                flag = 1;
            }
        }
        if (print_steps) { printf("第%d趟排序后: ", i + 1); printArray(""); }
        if (flag == 0) break; // 优化：如果一趟没有交换，说明已经有序
    }
}

// --- 6. 快速排序 ---
int Partition(int low, int high) {
    int pivot = arr[low];
    while (low < high) {
        while (low < high && arr[high] >= pivot) high--;
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) low++;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void QSort(int low, int high) {
    if (low < high) {
        int pivotLoc = Partition(low, high);
        // 递归调用
        QSort(low, pivotLoc - 1);
        QSort(pivotLoc + 1, high);
    }
}

void QuickSort() {
    printArray("原数组: ");
    QSort(0, n - 1);
    printArray("最终结果: "); // 递归过程不好打印每一趟，直接打印结果
}

// --- 7. 选择排序 ---
void SelectSort() {
    printArray("原数组: ");
    int i, j, minIdx;
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(&arr[i], &arr[minIdx]);
        
        if (print_steps) { printf("第%d趟排序后: ", i + 1); printArray(""); }
    }
}

// --- 8. 堆排序 ---
void HeapAdjust(int s, int m) {
    int rc = arr[s];
    for (int j = 2 * s + 1; j <= m; j = j * 2 + 1) { // 0-based index: 左孩子是 2*s+1
        if (j < m && arr[j] < arr[j + 1]) j++;
        if (rc >= arr[j]) break;
        arr[s] = arr[j]; s = j;
    }
    arr[s] = rc;
}

void HeapSort() {
    printArray("原数组: ");
    // 建堆
    for (int i = n / 2 - 1; i >= 0; i--) HeapAdjust(i, n - 1);
    
    // 排序
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        HeapAdjust(0, i - 1);
        if (print_steps) { printf("第%d趟排序后: ", n - i); printArray(""); }
    }
}

// --- 9. 二路归并排序 ---
void Merge(int low, int mid, int high) {
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) tempArr[k++] = arr[i++];
        else tempArr[k++] = arr[j++];
    }
    while (i <= mid) tempArr[k++] = arr[i++];
    while (j <= high) tempArr[k++] = arr[j++];
    
    for (i = 0; i < k; i++) arr[low + i] = tempArr[i];
}

void MSort(int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MSort(low, mid);
        MSort(mid + 1, high);
        Merge(low, mid, high);
    }
}

void MergeSort() {
    printArray("原数组: ");
    MSort(0, n - 1);
    printArray("最终结果: ");
}

// --- 10. 效率比较 ---
void EfficiencyCompare() {
    printf("\n正在生成 50 个随机数用于效率测试...\n");
    int testN = 50;
    // 临时备份 n 和 original
    int savedN = n;
    int savedOriginal[MAX_SIZE];
    for(int i=0; i<n; i++) savedOriginal[i] = original[i];

    // 生成随机数据
    n = testN;
    for(int i=0; i<n; i++) original[i] = rand() % 10000;

    print_steps = 0; // 关闭打印，只测时间
    clock_t start, end;
    double duration;

    printf("\n%-15s\t%-15s\n", "排序算法", "耗时(ms)");

    // 1. 直接插入
    resetArray(); start = clock(); DirectInsertSort(); end = clock();
    printf("%-15s\t%.2f ms\n", "直接插入排序", (double)(end - start));

    // 2. 折半插入
    resetArray(); start = clock(); BinaryInsertSort(); end = clock();
    printf("%-15s\t%.2f ms\n", "折半插入排序", (double)(end - start));

    // 3. 希尔
    resetArray(); start = clock(); ShellSort(); end = clock();
    printf("%-15s\t%.2f ms\n", "希尔排序", (double)(end - start));

    // 4. 冒泡
    resetArray(); start = clock(); BubbleSort(); end = clock();
    printf("%-15s\t%.2f ms\n", "冒泡排序", (double)(end - start));

    // 5. 快速
    resetArray(); start = clock(); QuickSort(); end = clock();
    printf("%-15s\t%.2f ms\n", "快速排序", (double)(end - start));

    // 6. 选择
    resetArray(); start = clock(); SelectSort(); end = clock();
    printf("%-15s\t%.2f ms\n", "选择排序", (double)(end - start));

    // 7. 堆排序
    resetArray(); start = clock(); HeapSort(); end = clock();
    printf("%-15s\t%.2f ms\n", "堆排序", (double)(end - start));

    // 8. 归并
    resetArray(); start = clock(); MergeSort(); end = clock();
    printf("%-15s\t%.2f ms\n", "归并排序", (double)(end - start));

    // 恢复原来的数据
    n = savedN;
    for(int i=0; i<n; i++) original[i] = savedOriginal[i];
    print_steps = 1;
    
    printf("\n测试完成。按回车返回菜单...");
    getchar(); getchar();
}