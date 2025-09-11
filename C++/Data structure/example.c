#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 100    // 初始容量
#define INCREMENT 10     // 扩容增量

typedef int ElemType;    // 元素类型

typedef struct {
    ElemType *data;      // 动态分配的数组
    int length;          // 当前长度
    int capacity;        // 总容量
} SeqList;

// 初始化顺序表
void InitList(SeqList *list) {
    list->data = (ElemType *)malloc(INIT_SIZE * sizeof(ElemType));
    if (!list->data) {
        printf("内存分配失败！\n");
        exit(1);
    }
    list->length = 0;
    list->capacity = INIT_SIZE;
}

// 插入元素到指定位置
int ListInsert(SeqList *list, int pos, ElemType e) {
    if (pos < 1 || pos > list->length + 1) return 0;  // 位置不合法
    if (list->length >= list->capacity) {  // 容量不足，需要扩容
        ElemType *newData = (ElemType *)realloc(
            list->data, (list->capacity + INCREMENT) * sizeof(ElemType));
        if (!newData) return 0;  // 扩容失败
        list->data = newData;
        list->capacity += INCREMENT;
    }
    // 移动元素
    for (int i = list->length; i >= pos; i--) {
        list->data[i] = list->data[i-1];
    }
    list->data[pos-1] = e;
    list->length++;
    return 1;
}

// 删除指定位置元素
int ListDelete(SeqList *list, int pos, ElemType *e) {
    if (pos < 1 || pos > list->length) return 0;  // 位置不合法
    *e = list->data[pos-1];
    // 移动元素
    for (int i = pos; i < list->length; i++) {
        list->data[i-1] = list->data[i];
    }
    list->length--;
    return 1;
}

// 查找元素位置
int LocateElem(SeqList *list, ElemType e) {
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] == e) return i + 1;  // 返回逻辑位置
    }
    return 0;  // 未找到
}

// 获取指定位置元素
int GetElem(SeqList *list, int pos, ElemType *e) {
    if (pos < 1 || pos > list->length) return 0;  // 位置不合法
    *e = list->data[pos-1];
    return 1;
}

// 打印顺序表
void PrintList(SeqList *list) {
    printf("顺序表内容：");
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n长度：%d，容量：%d\n", list->length, list->capacity);
}

// 释放顺序表内存
void DestroyList(SeqList *list) {
    free(list->data);
    list->data = NULL;
    list->length = 0;
    list->capacity = 0;
}

int main() {
    SeqList list;
    ElemType e;
    
    // 初始化
    InitList(&list);
    
    // 插入元素
    ListInsert(&list, 1, 10);
    ListInsert(&list, 2, 20);
    ListInsert(&list, 3, 30);
    ListInsert(&list, 2, 15);
    
    // 打印
    PrintList(&list);
    
    // 查找元素
    int pos = LocateElem(&list, 20);
    printf("元素20的位置是：%d\n", pos);
    
    // 删除元素
    ListDelete(&list, 2, &e);
    printf("删除的元素是：%d\n", e);
    
    // 再次打印
    PrintList(&list);
    
    // 释放内存
    DestroyList(&list);
    
    return 0;
}