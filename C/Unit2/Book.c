#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_STR_LEN 50
#define elemtype int

typedef struct {
    char isbn[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    float price;
} Book;

typedef struct {
    Book data[MAX_BOOKS];
    int length;
} BookList;

// 初始化顺序表
void InitBookList(BookList *list) {
    list->length = 0;
}

// 文件读取
int ReadFromFile(BookList *list, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;
    while (list->length < MAX_BOOKS &&
           fscanf(fp, "%s %s %f",
                  list->data[list->length].isbn,
                  list->data[list->length].name,
                  &list->data[list->length].price) != EOF) {
        list->length++;
    }
    fclose(fp);
    return 1;
}

// 文件保存
int SaveToFile(BookList *list, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return 0;
    for (int i = 0; i < list->length; i++)
        fprintf(fp, "%s %s %.2f\n",
                list->data[i].isbn,
                list->data[i].name,
                list->data[i].price);
    fclose(fp);
    return 1;
}

// 查找
int FindBook(BookList *list, const char *key, int isbnFlag) {
    for (int i = 0; i < list->length; i++) {
        if (isbnFlag && strcmp(list->data[i].isbn, key) == 0)
            return i;
        else if (!isbnFlag && strcmp(list->data[i].name, key) == 0)
            return i;
    }
    return -1;
}

// 插入
int InsertBook(BookList *list, Book *newBook) {
    if (list->length >= MAX_BOOKS) return 0;
    list->data[list->length++] = *newBook;
    return 1;
}

// 删除
int DeleteBook(BookList *list, int index) {
    if (index < 0 || index >= list->length) return 0;
    for (int i = index; i < list->length - 1; i++)
        list->data[i] = list->data[i + 1];
    list->length--;
    return 1;
}

// 修改价格
int ModifyPrice(BookList *list, const char *isbn, float newPrice) {
    int idx = FindBook(list, isbn, 1);
    if (idx == -1) return 0;
    list->data[idx].price = newPrice;
    return 1;
}

// 排序
void SortByPrice(BookList *list) {
    for (int i = 0; i < list->length - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < list->length; j++)
            if (list->data[j].price < list->data[minIdx].price)
                minIdx = j;
        Book tmp = list->data[i];
        list->data[i] = list->data[minIdx];
        list->data[minIdx] = tmp;
    }
}

// 显示所有
void ShowAllBooks(BookList *list) {
    printf("\n===== 所有图书信息 =====\n");
    for (int i = 0; i < list->length; i++)
        printf("[%d] ISBN: %s, 书名: %s, 价格: %.2f\n",
               i + 1, list->data[i].isbn, list->data[i].name, list->data[i].price);
}

// 菜单
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

int main() {
    BookList list;
    InitBookList(&list);
    ReadFromFile(&list, "book.txt");

    int choice, index, flag;
    char key[MAX_STR_LEN];
    float price;
    Book newBook;

    while (1) {
        PrintMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("请选择查找方式（1: ISBN, 2: 书名）：");
                scanf("%d", &flag);
                printf("请输入关键词：");
                scanf("%s", key);
                index = FindBook(&list, key, flag == 1);
                if (index != -1) {
                    printf("找到图书，位置为 %d\n", index + 1);
                    printf("ISBN: %s, 书名: %s, 价格: %.2f\n",
                           list.data[index].isbn, list.data[index].name, list.data[index].price);
                } else {
                    printf("未找到该图书\n");
                }
                break;
            case 2:
                printf("请输入新图书的ISBN、书名、价格：");
                scanf("%s %s %f", newBook.isbn, newBook.name, &newBook.price);
                if (InsertBook(&list, &newBook))
                    printf("插入图书成功\n");
                else
                    printf("插入失败，已达上限\n");
                break;
            case 3:
                ShowAllBooks(&list);
                printf("请输入要删除的图书位置：");
                scanf("%d", &index);
                if (DeleteBook(&list, index - 1))
                    printf("删除成功\n");
                else
                    printf("删除失败\n");
                break;
            case 4:
                printf("请输入图书ISBN和新价格：");
                scanf("%s %f", key, &price);
                if (ModifyPrice(&list, key, price))
                    printf("修改价格成功\n");
                else
                    printf("未找到该ISBN\n");
                break;
            case 5:
                SortByPrice(&list);
                printf("已按价格排序\n");
                break;
            case 6:
                printf("当前图书数量：%d\n", list.length);
                break;
            case 7:
                ShowAllBooks(&list);
                break;
            case 0:
                SaveToFile(&list, "book.txt");
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("输入无效，请重新选择\n");
        }
    }
    return 0;
}
