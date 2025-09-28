#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[32];
    float price;
    int quantity;
} ShopItem;

// ��elemtypeͳһ��Ʒ����
typedef ShopItem elemtype;

typedef struct {
    elemtype items[MAX];
    int length;
} ShopList;

// ��ʼ��
void initShopList(ShopList *list) {
    list->length = 0;
    printf("��Ʒ�б��ʼ����ɣ�\n");
}

// �����Ʒ
void addShopItem(ShopList *list) {
    if (list->length >= MAX) {
        printf("��Ʒ�����Ѵ����ޣ�\n");
        return;
    }
    elemtype item;
    item.id = list->length + 1;
    printf("��������Ʒ����: ");
    scanf("%s", item.name);
    printf("��������Ʒ�۸�: ");
    scanf("%f", &item.price);
    printf("��������Ʒ�������: ");
    scanf("%d", &item.quantity);
    list->items[list->length++] = item;
    printf("��ӳɹ���\n");
}

// ��ʾ������Ʒ
void showAllShopItems(ShopList *list) {
    printf("%-4s %-20s %-10s %-8s\n", "���", "����", "�۸�", "���");
    for (int i = 0; i < list->length; i++) {
        elemtype item = list->items[i];
        printf("%-4d %-20s %-10.2f %-8d\n", item.id, item.name, item.price, item.quantity);
    }
}

// �����Ʋ�����Ʒ
void findShopItem(ShopList *list) {
    char name[32];
    printf("������Ҫ���ҵ���Ʒ����: ");
    scanf("%s", name);
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->items[i].name, name) == 0) {
            elemtype item = list->items[i];
            printf("�ҵ���Ʒ�����%d ����%s �۸�%.2f ���%d\n", item.id, item.name, item.price, item.quantity);
            return;
        }
    }
    printf("δ�ҵ�����Ʒ��\n");
}

// ɾ����Ʒ
void deleteShopItem(ShopList *list) {
    int id;
    printf("������Ҫɾ������Ʒ���: ");
    scanf("%d", &id);
    int found = 0;
    for (int i = 0; i < list->length; i++) {
        if (list->items[i].id == id) {
            found = 1;
            for (int j = i; j < list->length - 1; j++) {
                list->items[j] = list->items[j + 1];
                list->items[j].id = j + 1; // ���±��
            }
            list->length--;
            printf("ɾ���ɹ���\n");
            break;
        }
    }
    if (!found) printf("δ�ҵ�����Ʒ��\n");
}

int main() {
    ShopList list;
    int choice;
    initShopList(&list);
    while (1) {
        printf("\n��Ʒ��Ϣ����ϵͳ\n");
        printf("1. �����Ʒ\n");
        printf("2. ��ʾ������Ʒ\n");
        printf("3. ������Ʒ\n");
        printf("4. ɾ����Ʒ\n");
        printf("0. �˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addShopItem(&list); break;
            case 2: showAllShopItems(&list); break;
            case 3: findShopItem(&list); break;
            case 4: deleteShopItem(&list); break;
            case 0: return 0;
            default: printf("��Чѡ��\n");
        }
    }
    return 0;
}