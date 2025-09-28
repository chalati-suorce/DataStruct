#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[32];
    float price;
    int quantity;
} ShopItem;

// 用elemtype统一商品类型
typedef ShopItem elemtype;

typedef struct {
    elemtype items[MAX];
    int length;
} ShopList;

// 初始化
void initShopList(ShopList *list) {
    list->length = 0;
    printf("商品列表初始化完成！\n");
}

// 添加商品
void addShopItem(ShopList *list) {
    if (list->length >= MAX) {
        printf("商品数量已达上限！\n");
        return;
    }
    elemtype item;
    item.id = list->length + 1;
    printf("请输入商品名称: ");
    scanf("%s", item.name);
    printf("请输入商品价格: ");
    scanf("%f", &item.price);
    printf("请输入商品库存数量: ");
    scanf("%d", &item.quantity);
    list->items[list->length++] = item;
    printf("添加成功！\n");
}

// 显示所有商品
void showAllShopItems(ShopList *list) {
    printf("%-4s %-20s %-10s %-8s\n", "编号", "名称", "价格", "库存");
    for (int i = 0; i < list->length; i++) {
        elemtype item = list->items[i];
        printf("%-4d %-20s %-10.2f %-8d\n", item.id, item.name, item.price, item.quantity);
    }
}

// 按名称查找商品
void findShopItem(ShopList *list) {
    char name[32];
    printf("请输入要查找的商品名称: ");
    scanf("%s", name);
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->items[i].name, name) == 0) {
            elemtype item = list->items[i];
            printf("找到商品：编号%d 名称%s 价格%.2f 库存%d\n", item.id, item.name, item.price, item.quantity);
            return;
        }
    }
    printf("未找到该商品！\n");
}

// 删除商品
void deleteShopItem(ShopList *list) {
    int id;
    printf("请输入要删除的商品编号: ");
    scanf("%d", &id);
    int found = 0;
    for (int i = 0; i < list->length; i++) {
        if (list->items[i].id == id) {
            found = 1;
            for (int j = i; j < list->length - 1; j++) {
                list->items[j] = list->items[j + 1];
                list->items[j].id = j + 1; // 重新编号
            }
            list->length--;
            printf("删除成功！\n");
            break;
        }
    }
    if (!found) printf("未找到该商品！\n");
}

int main() {
    ShopList list;
    int choice;
    initShopList(&list);
    while (1) {
        printf("\n商品信息管理系统\n");
        printf("1. 添加商品\n");
        printf("2. 显示所有商品\n");
        printf("3. 查找商品\n");
        printf("4. 删除商品\n");
        printf("0. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addShopItem(&list); break;
            case 2: showAllShopItems(&list); break;
            case 3: findShopItem(&list); break;
            case 4: deleteShopItem(&list); break;
            case 0: return 0;
            default: printf("无效选择！\n");
        }
    }
    return 0;
}