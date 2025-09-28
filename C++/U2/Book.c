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

// ��ʼ��˳���
void InitBookList(BookList *list) {
    list->length = 0;
}

// �ļ���ȡ
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

// �ļ�����
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

// ����
int FindBook(BookList *list, const char *key, int isbnFlag) {
    for (int i = 0; i < list->length; i++) {
        if (isbnFlag && strcmp(list->data[i].isbn, key) == 0)
            return i;
        else if (!isbnFlag && strcmp(list->data[i].name, key) == 0)
            return i;
    }
    return -1;
}

// ����
int InsertBook(BookList *list, Book *newBook) {
    if (list->length >= MAX_BOOKS) return 0;
    list->data[list->length++] = *newBook;
    return 1;
}

// ɾ��
int DeleteBook(BookList *list, int index) {
    if (index < 0 || index >= list->length) return 0;
    for (int i = index; i < list->length - 1; i++)
        list->data[i] = list->data[i + 1];
    list->length--;
    return 1;
}

// �޸ļ۸�
int ModifyPrice(BookList *list, const char *isbn, float newPrice) {
    int idx = FindBook(list, isbn, 1);
    if (idx == -1) return 0;
    list->data[idx].price = newPrice;
    return 1;
}

// ����
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

// ��ʾ����
void ShowAllBooks(BookList *list) {
    printf("\n===== ����ͼ����Ϣ =====\n");
    for (int i = 0; i < list->length; i++)
        printf("[%d] ISBN: %s, ����: %s, �۸�: %.2f\n",
               i + 1, list->data[i].isbn, list->data[i].name, list->data[i].price);
}

// �˵�
void PrintMenu() {
    printf("\n===== ͼ����Ϣ����ϵͳ =====\n");
    printf("1. ����ͼ�飨ISBN/������\n");
    printf("2. ����ͼ��\n");
    printf("3. ɾ��ͼ�飨��λ�ã�\n");
    printf("4. �޸�ͼ��۸񣨰�ISBN��\n");
    printf("5. ���۸�����\n");
    printf("6. ͳ��ͼ������\n");
    printf("7. ��ʾ����ͼ��\n");
    printf("0. �˳�ϵͳ\n");
    printf("������ѡ��");
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
                printf("��ѡ����ҷ�ʽ��1: ISBN, 2: ��������");
                scanf("%d", &flag);
                printf("������ؼ��ʣ�");
                scanf("%s", key);
                index = FindBook(&list, key, flag == 1);
                if (index != -1) {
                    printf("�ҵ�ͼ�飬λ��Ϊ %d\n", index + 1);
                    printf("ISBN: %s, ����: %s, �۸�: %.2f\n",
                           list.data[index].isbn, list.data[index].name, list.data[index].price);
                } else {
                    printf("δ�ҵ���ͼ��\n");
                }
                break;
            case 2:
                printf("��������ͼ���ISBN���������۸�");
                scanf("%s %s %f", newBook.isbn, newBook.name, &newBook.price);
                if (InsertBook(&list, &newBook))
                    printf("����ͼ��ɹ�\n");
                else
                    printf("����ʧ�ܣ��Ѵ�����\n");
                break;
            case 3:
                ShowAllBooks(&list);
                printf("������Ҫɾ����ͼ��λ�ã�");
                scanf("%d", &index);
                if (DeleteBook(&list, index - 1))
                    printf("ɾ���ɹ�\n");
                else
                    printf("ɾ��ʧ��\n");
                break;
            case 4:
                printf("������ͼ��ISBN���¼۸�");
                scanf("%s %f", key, &price);
                if (ModifyPrice(&list, key, price))
                    printf("�޸ļ۸�ɹ�\n");
                else
                    printf("δ�ҵ���ISBN\n");
                break;
            case 5:
                SortByPrice(&list);
                printf("�Ѱ��۸�����\n");
                break;
            case 6:
                printf("��ǰͼ��������%d\n", list.length);
                break;
            case 7:
                ShowAllBooks(&list);
                break;
            case 0:
                SaveToFile(&list, "book.txt");
                printf("��лʹ�ã��ټ���\n");
                return 0;
            default:
                printf("������Ч��������ѡ��\n");
        }
    }
    return 0;
}