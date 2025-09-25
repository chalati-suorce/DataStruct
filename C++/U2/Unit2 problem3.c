#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100  // 顺序表最大容量
#define MAX_STR_LEN 50 // 字符串最大长度

// 图书结构：ISBN、书名、价格
typedef struct {
    char isbn[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    float price;
} Book;

// 图书顺序表结构
typedef struct {
    Book data[MAX_BOOKS];
    int length; // 实际图书数量
} BookList;

// 初始化图书顺序表
void InitBookList(BookList *list) {
    list->length = 0;
}

// 从文件读取图书数据到顺序表
int ReadFromFile(BookList *list, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }
    // 逐个读取图书信息（假设文件格式：ISBN 书名 价格）
    while (list->length < MAX_BOOKS && 
           fscanf(fp, "%s %s %f", 
                  list->data[list->length].isbn, 
                  list->data[list->length].name, 
                  &list->data[list->length].price) != EOF) {
        list->length++;
    }
    fclose(fp);
    printf("成功从文件读取 %d 本图书\n", list->length);
    return 1;
}

// 保存顺序表数据到文件
int SaveToFile(BookList *list, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }
    for (int i = 0; i < list->length; i++) {
        fprintf(fp, "%s %s %.2f\n", 
                list->data[i].isbn, 
                list->data[i].name, 
                list->data[i].price);
    }
    fclose(fp);
    printf("成功保存数据到文件\n");
    return 1;
}

// 查找图书：isbnFlag=1 按ISBN查，否则按书名查；返回位置，-1表示未找到
int FindBook(BookList *list, const char *key, int isbnFlag) {
    for (int i = 0; i < list->length; i++) {
        if (isbnFlag && strcmp(list->data[i].isbn, key) == 0) {
            return i;
        } else if (!isbnFlag && strcmp(list->data[i].name, key) == 0) {
            return i;
        }
    }
    return -1; // 未找到
}

// 打印单本图书信息
void PrintOneBook(Book *book) {
    printf("ISBN: %s, 书名: %s, 价格: %.2f\n", 
           book->isbn, book->name, book->price);
}

// 插入图书（在末尾插入）
int InsertBook(BookList *list, Book *newBook) {
    if (list->length >= MAX_BOOKS) {
        printf("图书数量已达上限，无法插入\n");
        return 0;
    }
    list->data[list->length] = *newBook;
    list->length++;
    printf("插入图书成功\n");
    return 1;
}

// 删除图书（根据位置index）
int DeleteBook(BookList *list, int index) {
    if (index < 0 || index >= list->length) {
        printf("位置无效，删除失败\n");
        return 0;
    }
    // 移动后续元素覆盖被删除项
    for (int i = index; i < list->length - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    printf("删除图书成功\n");
    return 1;
}

// 修改图书价格（根据ISBN）
int ModifyPrice(BookList *list, const char *isbn, float newPrice) {
    int index = FindBook(list, isbn, 1);
    if (index == -1) {
        printf("未找到ISBN为 %s 的图书\n", isbn);
        return 0;
    }
    list->data[index].price = newPrice;
    printf("修改价格成功\n");
    return 1;
}

// 按价格从低到高排序（选择排序）
void SortByPrice(BookList *list) {
    for (int i = 0; i < list->length - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < list->length; j++) {
            if (list->data[j].price < list->data[minIdx].price) {
                minIdx = j;
            }
        }
        // 交换
        Book temp = list->data[i];
        list->data[i] = list->data[minIdx];
        list->data[minIdx] = temp;
    }
    printf("已按价格从低到高排序\n");
}

void PrintMenu() {
    printf("\n===== 图书信息管理系统 =====\n");
    printf("1. 查找图书（ISBN/书名）\n");
    printf("2. 插入图书\n");
    printf("3. 删除图书（按位置）\n");
    printf("4. 修改图书价格（按ISBN）\n");
    printf("5. 按价格排序\n");
    printf("6. 统计图书数量\n");
    printf("7. 显示所有图书\n");
    printf("0. 退出系统\n");
    printf("请输入选择：");
}

// 显示所有图书
void ShowAllBooks(BookList *list) {
    printf("\n===== 所有图书信息 =====\n");
    for (int i = 0; i < list->length; i++) {
        printf("[%d] ISBN: %s, 书名: %s, 价格: %.2f\n", 
               i + 1, list->data[i].isbn, list->data[i].name, list->data[i].price);
    }
}

int main() {
    BookList list;
    InitBookList(&list);
    ReadFromFile(&list, "book.txt"); // 从文件读取初始数据
    
    int choice;
    char key[MAX_STR_LEN];
    int index;
    float price;
    Book newBook;
    
    while (1) {
        PrintMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: // 查找
                printf("请选择查找方式（1: ISBN, 2: 书名）：");
                int flag;
                scanf("%d", &flag);
                printf("请输入关键词：");
                scanf("%s", key);
                index = FindBook(&list, key, flag == 1);
                if (index != -1) {
                    printf("找到图书，位置为 %d\n", index + 1);
                    PrintOneBook(&list.data[index]);
                } else {
                    printf("未找到该图书\n");
                }
                break;
            case 2: // 插入
                printf("请输入新图书的ISBN、书名、价格：");
                scanf("%s %s %f", newBook.isbn, newBook.name, &newBook.price);
                InsertBook(&list, &newBook);
                break;
            case 3: // 删除
                ShowAllBooks(&list);
                printf("请输入要删除的图书位置：");
                scanf("%d", &index);
                DeleteBook(&list, index - 1); // 位置从1开始，转换为数组下标
                break;
            case 4: // 修改价格
                printf("请输入图书ISBN和新价格：");
                scanf("%s %f", key, &price);
                ModifyPrice(&list, key, price);
                break;
            case 5: // 排序
                SortByPrice(&list);
                break;
            case 6: // 统计数量
                printf("当前图书数量：%d\n", list.length);
                break;
            case 7: // 显示所有图书
                ShowAllBooks(&list);
                break;
            case 0: // 退出
                SaveToFile(&list, "book.txt"); // 退出前保存数据
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("输入无效，请重新选择\n");
        }
    }
    return 0;
}

