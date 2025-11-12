#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100  // 顺序表最大容量

// 图书信息结构体
typedef struct {
    char bookId[20];      // 图书编号
    char title[50];       // 书名
    char author[30];      // 作者
    char publisher[50];   // 出版社
    float price;          // 价格
    int year;             // 出版年份
} Book;

// 顺序表结构体
typedef struct {
    Book data[MAX_SIZE];  // 存储图书数据的数组
    int length;           // 当前顺序表长度
} SeqList;

// 初始化顺序表
void initList(SeqList *list) {
    list->length = 0;
    printf("顺序表初始化成功！\n");
}

// 1. 输出顺序表
void printList(SeqList *list) {
    if (list->length == 0) {
        printf("顺序表为空！\n");
        return;
    }
    
    printf("\n当前图书信息列表\n");
    printf("序号\t图书编号\t\t书名\t\t\t作者\t\t出版社\t\t价格\t年份\n");
    
    for (int i = 0; i < list->length; i++) {
        printf("%d\t%-15s\t%-20s\t%-15s\t%-15s\t%.2f\t%d\n", 
               i + 1,
               list->data[i].bookId,
               list->data[i].title,
               list->data[i].author,
               list->data[i].publisher,
               list->data[i].price,
               list->data[i].year);
    }
    printf("总共有 %d 本图书\n", list->length);
}

// 2. 找到第i个元素并输出
int getElement(SeqList *list, int i) {
    if (i < 1 || i > list->length) {
        printf("位置 %d 无效！有效范围：1-%d\n", i, list->length);
        return 0;
    }
    
    Book *book = &list->data[i - 1];
    printf("\n第 %d 个图书的信息：\n", i);
    printf("图书编号：%s\n", book->bookId);
    printf("书名：%s\n", book->title);
    printf("作者：%s\n", book->author);
    printf("出版社：%s\n", book->publisher);
    printf("价格：%.2f 元\n", book->price);
    printf("出版年份：%d\n", book->year);
    
    return 1;
}

// 3. 在顺序表中查找图书并返回位置（按图书编号）
int findElementById(SeqList *list, char *bookId) {
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->data[i].bookId, bookId) == 0) {
            printf("\n找到图书信息：\n");
            printf("位置：%d\n", i + 1);
            printf("图书编号：%s\n", list->data[i].bookId);
            printf("书名：%s\n", list->data[i].title);
            printf("作者：%s\n", list->data[i].author);
            printf("出版社：%s\n", list->data[i].publisher);
            printf("价格：%.2f 元\n", list->data[i].price);
            printf("出版年份：%d\n", list->data[i].year);
            return i + 1;  // 返回位置（从1开始）
        }
    }
    
    printf("未找到编号为 %s 的图书！\n", bookId);
    return -1;
}

// 按书名查找图书并返回位置
int findElementByTitle(SeqList *list, char *title) {
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->data[i].title, title) == 0) {
            printf("\n找到图书信息：\n");
            printf("位置：%d\n", i + 1);
            printf("图书编号：%s\n", list->data[i].bookId);
            printf("书名：%s\n", list->data[i].title);
            printf("作者：%s\n", list->data[i].author);
            printf("出版社：%s\n", list->data[i].publisher);
            printf("价格：%.2f 元\n", list->data[i].price);
            printf("出版年份：%d\n", list->data[i].year);
            return i + 1;
        }
    }
    
    printf("未找到书名为 \"%s\" 的图书！\n", title);
    return -1;
}

// 4. 在第i个元素之前插入数据
int insertElement(SeqList *list, int i, Book book) {
    // 检查顺序表是否已满
    if (list->length >= MAX_SIZE) {
        printf("顺序表已满，无法插入新图书！\n");
        return 0;
    }
    
    // 检查位置是否有效
    if (i < 1 || i > list->length + 1) {
        printf("插入位置 %d 无效！有效范围：1-%d\n", i, list->length + 1);
        return 0;
    }
    
    // 检查图书编号是否重复
    for (int j = 0; j < list->length; j++) {
        if (strcmp(list->data[j].bookId, book.bookId) == 0) {
            printf("图书编号 %s 已存在，无法插入！\n", book.bookId);
            return 0;
        }
    }
    
    // 移动元素，为插入腾出位置
    for (int j = list->length; j >= i; j--) {
        list->data[j] = list->data[j - 1];
    }
    
    // 插入新图书
    list->data[i - 1] = book;
    list->length++;
    
    printf("成功在第 %d 个位置插入图书信息！\n", i);
    return 1;
}

// 5. 删除顺序表中的第i个元素
int deleteElement(SeqList *list, int i) {
    // 检查位置是否有效
    if (i < 1 || i > list->length) {
        printf("删除位置 %d 无效！有效范围：1-%d\n", i, list->length);
        return 0;
    }
    
    printf("删除的图书信息：\n");
    printf("图书编号：%s\n", list->data[i - 1].bookId);
    printf("书名：%s\n", list->data[i - 1].title);
    printf("作者：%s\n", list->data[i - 1].author);
    
    // 移动元素，覆盖要删除的元素
    for (int j = i - 1; j < list->length - 1; j++) {
        list->data[j] = list->data[j + 1];
    }
    
    list->length--;
    printf("成功删除第 %d 个图书信息！\n", i);
    return 1;
}

// 输入图书信息
Book inputBook() {
    Book book;
    
    printf("请输入图书编号：");
    scanf("%s", book.bookId);
    
    printf("请输入书名：");
    scanf("%s", book.title);
    
    printf("请输入作者：");
    scanf("%s", book.author);
    
    printf("请输入出版社：");
    scanf("%s", book.publisher);
    
    printf("请输入价格：");
    scanf("%f", &book.price);
    
    printf("请输入出版年份：");
    scanf("%d", &book.year);
    
    return book;
}

// 显示菜单
void showMenu() {
    printf("\n图书信息管理系统\n");
    printf("1. 输出顺序表\n");
    printf("2. 查找第i个元素\n");
    printf("3. 查找图书(按编号)\n");
    printf("4. 查找图书(按书名)\n");
    printf("5. 插入图书信息\n");
    printf("6. 删除图书信息\n");
    printf("7. 添加测试数据\n");
    printf("0. 退出系统\n");
    printf("请选择操作：");
}

// 添加测试数据
void addTestData(SeqList *list) {
    Book testBooks[] = {
        {"B001", "数据结构", "严蔚敏", "清华大学出版社", 45.00, 2018},
        {"B002", "C程序设计", "谭浩强", "清华大学出版社", 38.50, 2019},
        {"B003", "算法导论", "Thomas", "机械工业出版社", 128.00, 2020},
        {"B004", "操作系统", "汤小丹", "西安电子科技大学出版社", 52.30, 2017},
        {"B005", "计算机网络", "谢希仁", "电子工业出版社", 42.80, 2021}
    };
    
    int testCount = sizeof(testBooks) / sizeof(Book);
    
    for (int i = 0; i < testCount && list->length < MAX_SIZE; i++) {
        list->data[list->length] = testBooks[i];
        list->length++;
    }
    
    printf("成功添加 %d 条测试数据！\n", testCount);
}

// 显示系统统计信息
void showStatistics(SeqList *list) {
    if (list->length == 0) {
        printf("暂无图书数据！\n");
        return;
    }
    
    float totalPrice = 0;
    float maxPrice = list->data[0].price;
    float minPrice = list->data[0].price;
    int maxYear = list->data[0].year;
    int minYear = list->data[0].year;
    
    for (int i = 0; i < list->length; i++) {
        totalPrice += list->data[i].price;
        if (list->data[i].price > maxPrice) maxPrice = list->data[i].price;
        if (list->data[i].price < minPrice) minPrice = list->data[i].price;
        if (list->data[i].year > maxYear) maxYear = list->data[i].year;
        if (list->data[i].year < minYear) minYear = list->data[i].year;
    }
    
    printf("\n系统统计信息\n");
    printf("图书总数：%d 本\n", list->length);
    printf("图书总价值：%.2f 元\n", totalPrice);
    printf("平均价格：%.2f 元\n", totalPrice / list->length);
    printf("最高价格：%.2f 元\n", maxPrice);
    printf("最低价格：%.2f 元\n", minPrice);
    printf("最新出版年份：%d 年\n", maxYear);
    printf("最早出版年份：%d 年\n", minYear);
}

int main() {
    SeqList bookList;
    int choice, position;
    char searchKey[50];
    Book newBook;
    
    // 初始化顺序表
    initList(&bookList);
    
    printf("欢迎使用图书信息管理系统！\n");
    
    while (1) {
        showMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printList(&bookList);
                break;
                
            case 2:
                if (bookList.length == 0) {
                    printf("顺序表为空！\n");
                    break;
                }
                printf("请输入要查找的位置(1-%d)：", bookList.length);
                scanf("%d", &position);
                getElement(&bookList, position);
                break;
                
            case 3:
                printf("请输入要查找的图书编号：");
                scanf("%s", searchKey);
                findElementById(&bookList, searchKey);
                break;
                
            case 4:
                printf("请输入要查找的书名：");
                scanf("%s", searchKey);
                findElementByTitle(&bookList, searchKey);
                break;
                
            case 5:
                if (bookList.length >= MAX_SIZE) {
                    printf("顺序表已满，无法插入新图书！\n");
                    break;
                }
                printf("请输入插入位置(1-%d)：", bookList.length + 1);
                scanf("%d", &position);
                printf("请输入图书信息：\n");
                newBook = inputBook();
                insertElement(&bookList, position, newBook);
                break;
                
            case 6:
                if (bookList.length == 0) {
                    printf("顺序表为空！\n");
                    break;
                }
                printf("请输入要删除的位置(1-%d)：", bookList.length);
                scanf("%d", &position);
                deleteElement(&bookList, position);
                break;
                
            case 7:
                addTestData(&bookList);
                break;
                
            case 8:
                showStatistics(&bookList);
                break;
                
            case 0:
                printf("感谢使用图书信息管理系统，再见！\n");
                return 0;
                
            default:
                printf("无效的选择，请重新输入！\n");
                break;
        }
    }
    
    return 0;
}
