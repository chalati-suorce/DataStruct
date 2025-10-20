#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

// 图书信息结构体
typedef struct
{
    char isbn[20];      // ISBN号
    char title[100];    // 书名
    char author[50];    // 作者
    char publisher[50]; // 出版社
    float price;        // 价格
    int year;           // 出版年份
} Book;

// 顺序表结构体
typedef struct
{
    Book books[MAX_SIZE]; // 图书数组
    int length;           // 当前长度
} BookList;

// 1. 初始化顺序表
void InitList(BookList *L)
{
    L->length = 0;
    printf("顺序表初始化成功！\n");
}

// 2. 输出顺序表
void PrintList(BookList *L)
{
    if (L->length == 0)
    {
        printf("顺序表为空！\n");
        return;
    }

    printf("\n图书信息列表\n");
    printf("序号\tISBN\t\t书名\t\t作者\t\t出版社\t\t价格\t年份\n");

    for (int i = 0; i < L->length; i++)
    {
        printf("%d\t%s\t%s\t%s\t%s\t%.2f\t%d\n",
               i + 1,
               L->books[i].isbn,
               L->books[i].title,
               L->books[i].author,
               L->books[i].publisher,
               L->books[i].price,
               L->books[i].year);
    }
    printf("总记录数: %d\n", L->length);
}

// 3. 查找第i个元素
Book *GetElem(BookList *L, int i)
{
    if (i < 1 || i > L->length)
    {
        printf("位置 %d 无效！有效范围: 1-%d\n", i, L->length);
        return NULL;
    }
    return &L->books[i - 1];
}

// 4. 按ISBN查找图书位置
int LocateElem(BookList *L, char *isbn)
{
    for (int i = 0; i < L->length; i++)
    {
        if (strcmp(L->books[i].isbn, isbn) == 0)
        {
            return i + 1; // 返回位置（从1开始）
        }
    }
    return -1; // 未找到
}

// 5. 在第i个位置之前插入图书
int ListInsert(BookList *L, int i, Book book)
{
    // 检查顺序表是否已满
    if (L->length >= MAX_SIZE)
    {
        printf("顺序表已满，无法插入！\n");
        return 0;
    }

    // 检查位置是否合法
    if (i < 1 || i > L->length + 1)
    {
        printf("插入位置 %d 无效！有效范围: 1-%d\n", i, L->length + 1);
        return 0;
    }

    // 检查ISBN是否已存在
    if (LocateElem(L, book.isbn) != -1)
    {
        printf("ISBN %s 已存在，无法插入！\n", book.isbn);
        return 0;
    }

    // 移动元素，为插入腾出位置
    for (int j = L->length; j >= i; j--)
    {
        L->books[j] = L->books[j - 1];
    }

    // 插入新元素
    L->books[i - 1] = book;
    L->length++;

    printf("图书插入成功！位置: %d\n", i);
    return 1;
}

// 6. 删除第i个位置的图书
int ListDelete(BookList *L, int i)
{
    // 检查位置是否合法
    if (i < 1 || i > L->length)
    {
        printf("删除位置 %d 无效！有效范围: 1-%d\n", i, L->length);
        return 0;
    }

    // 显示要删除的图书信息
    printf("删除的图书信息:\n");
    printf("ISBN: %s, 书名: %s, 作者: %s\n",
           L->books[i - 1].isbn, L->books[i - 1].title, L->books[i - 1].author);

    // 移动元素，覆盖要删除的元素
    for (int j = i; j < L->length; j++)
    {
        L->books[j - 1] = L->books[j];
    }

    L->length--;
    printf("图书删除成功！\n");
    return 1;
}

// 7. 修改第i个位置的图书信息
int ModifyBook(BookList *L, int i, Book newBook)
{
    // 检查位置是否合法
    if (i < 1 || i > L->length)
    {
        printf("修改位置 %d 无效！有效范围: 1-%d\n", i, L->length);
        return 0;
    }

    // 检查新ISBN是否与其他图书冲突（除了当前位置）
    for (int j = 0; j < L->length; j++)
    {
        if (j != i - 1 && strcmp(L->books[j].isbn, newBook.isbn) == 0)
        {
            printf("ISBN %s 已存在，无法修改！\n", newBook.isbn);
            return 0;
        }
    }

    // 显示原信息
    printf("原图书信息:\n");
    printf("ISBN: %s, 书名: %s, 作者: %s, 出版社: %s, 价格: %.2f, 年份: %d\n",
           L->books[i - 1].isbn, L->books[i - 1].title, L->books[i - 1].author,
           L->books[i - 1].publisher, L->books[i - 1].price, L->books[i - 1].year);

    // 修改信息
    L->books[i - 1] = newBook;

    printf("图书信息修改成功！\n");
    return 1;
}

// 8. 按书名查找图书
void SearchByTitle(BookList *L, char *title)
{
    int found = 0;
    printf("\n按书名查找结果\n");

    for (int i = 0; i < L->length; i++)
    {
        if (strstr(L->books[i].title, title) != NULL)
        {
            printf("位置: %d, ISBN: %s, 书名: %s, 作者: %s, 出版社: %s, 价格: %.2f, 年份: %d\n",
                   i + 1, L->books[i].isbn, L->books[i].title, L->books[i].author,
                   L->books[i].publisher, L->books[i].price, L->books[i].year);
            found = 1;
        }
    }

    if (!found)
    {
        printf("未找到包含 \"%s\" 的图书！\n", title);
    }
}

// 9. 按作者查找图书
void SearchByAuthor(BookList *L, char *author)
{
    int found = 0;
    printf("\n按作者查找结果\n");

    for (int i = 0; i < L->length; i++)
    {
        if (strstr(L->books[i].author, author) != NULL)
        {
            printf("位置: %d, ISBN: %s, 书名: %s, 作者: %s, 出版社: %s, 价格: %.2f, 年份: %d\n",
                   i + 1, L->books[i].isbn, L->books[i].title, L->books[i].author,
                   L->books[i].publisher, L->books[i].price, L->books[i].year);
            found = 1;
        }
    }

    if (!found)
    {
        printf("未找到作者为 \"%s\" 的图书！\n", author);
    }
}

// 10. 清空顺序表
void ClearList(BookList *L)
{
    L->length = 0;
    printf("顺序表已清空！\n");
}

// 11. 获取顺序表长度
int GetLength(BookList *L)
{
    return L->length;
}

// 12. 判断顺序表是否为空
int IsEmpty(BookList *L)
{
    return L->length == 0;
}

// 13. 输入图书信息
Book InputBook()
{
    Book book;
    printf("请输入图书信息:\n");

    printf("ISBN: ");
    scanf("%s", book.isbn);

    printf("书名: ");
    scanf("%s", book.title);

    printf("作者: ");
    scanf("%s", book.author);

    printf("出版社: ");
    scanf("%s", book.publisher);

    printf("价格: ");
    scanf("%f", &book.price);

    printf("出版年份: ");
    scanf("%d", &book.year);

    return book;
}

// 14. 显示菜单
void ShowMenu()
{
    printf("\n图书信息管理系统\n");
    printf("1. 初始化顺序表\n");
    printf("2. 输出所有图书\n");
    printf("3. 查找第i个元素\n");
    printf("4. 按ISBN查找图书位置\n");
    printf("5. 插入图书\n");
    printf("6. 删除图书\n");
    printf("7. 修改图书信息\n");
    printf("8. 按书名查找\n");
    printf("9. 按作者查找\n");
    printf("10. 清空顺序表\n");
    printf("11. 获取顺序表长度\n");
    printf("12. 判断顺序表是否为空\n");
    printf("0. 退出系统\n");
    printf("请选择操作: ");
}

int main()
{
    BookList bookList;
    int choice, position;
    char isbn[20], title[100], author[50];
    Book book, *foundBook;

    // 初始化顺序表
    InitList(&bookList);

    while (1)
    {
        ShowMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("感谢使用图书信息管理系统！\n");
            return 0;

        case 1:
            InitList(&bookList);
            break;

        case 2:
            PrintList(&bookList);
            break;

        case 3:
            printf("请输入要查找的位置: ");
            scanf("%d", &position);
            foundBook = GetElem(&bookList, position);
            if (foundBook != NULL)
            {
                printf("第%d个位置的图书信息:\n", position);
                printf("ISBN: %s, 书名: %s, 作者: %s, 出版社: %s, 价格: %.2f, 年份: %d\n",
                       foundBook->isbn, foundBook->title, foundBook->author,
                       foundBook->publisher, foundBook->price, foundBook->year);
            }
            break;

        case 4:
            printf("请输入要查找的ISBN: ");
            scanf("%s", isbn);
            position = LocateElem(&bookList, isbn);
            if (position != -1)
            {
                printf("ISBN %s 位于第 %d 个位置\n", isbn, position);
            }
            else
            {
                printf("未找到ISBN为 %s 的图书\n", isbn);
            }
            break;

        case 5:
            book = InputBook();
            printf("请输入插入位置: ");
            scanf("%d", &position);
            ListInsert(&bookList, position, book);
            break;

        case 6:
            printf("请输入要删除的位置: ");
            scanf("%d", &position);
            ListDelete(&bookList, position);
            break;

        case 7:
            printf("请输入要修改的位置: ");
            scanf("%d", &position);
            book = InputBook();
            ModifyBook(&bookList, position, book);
            break;

        case 8:
            printf("请输入要查找的书名: ");
            scanf("%s", title);
            SearchByTitle(&bookList, title);
            break;

        case 9:
            printf("请输入要查找的作者: ");
            scanf("%s", author);
            SearchByAuthor(&bookList, author);
            break;

        case 10:
            ClearList(&bookList);
            break;

        case 11:
            printf("顺序表当前长度: %d\n", GetLength(&bookList));
            break;

        case 12:
            if (IsEmpty(&bookList))
            {
                printf("顺序表为空\n");
            }
            else
            {
                printf("顺序表不为空\n");
            }
            break;

        default:
            printf("无效的选择，请重新输入！\n");
            break;
        }
    }

    return 0;
}