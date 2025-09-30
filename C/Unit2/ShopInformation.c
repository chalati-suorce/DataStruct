#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[32];
    float price;
    int quantity;
} ShopItem;

// 浣跨敤elemtype缁熶竴鍟嗗搧绫诲瀷
typedef ShopItem elemtype;

typedef struct {
    elemtype items[MAX];
    int length;
} ShopList;

// 鍒濆鍖?
void initShopList(ShopList *list) {
    list->length = 0;
    printf("鍟嗗搧鍒楄〃鍒濆鍖栧畬鎴愶紒\n");
}

// 娣诲姞鍟嗗搧
void addShopItem(ShopList *list) {
    if (list->length >= MAX) {
        printf("鍟嗗搧鏁伴噺宸茶揪涓婇檺锛乗n");
        return;
    }
    elemtype item;
    item.id = list->length + 1;
    printf("璇疯緭鍏ュ晢鍝佸悕绉? ");
    scanf_s("%s", item.name, sizeof(item.name));
    printf("璇疯緭鍏ュ晢鍝佷环鏍? ");
    scanf_s("%f", &item.price);
    printf("璇疯緭鍏ュ晢鍝佹暟閲? ");
    scanf_s("%d", &item.quantity);
    list->items[list->length++] = item;
    printf("娣诲姞鎴愬姛锛乗n");
}

// 鏄剧ず鎵€鏈夊晢鍝?
void showAllShopItems(ShopList *list) {
    printf("%-4s %-20s %-10s %-8s\n", "缂栧彿", "鍚嶇О", "浠锋牸", "鏁伴噺");
    for (int i = 0; i < list->length; i++) {
        elemtype item = list->items[i];
        printf("%-4d %-20s %-10.2f %-8d\n", item.id, item.name, item.price, item.quantity);
    }
}

// 鎸夊悕绉版煡鎵惧晢鍝?
void findShopItem(ShopList *list) {
    char name[32];
    printf("璇疯緭鍏ヨ鏌ユ壘鐨勫晢鍝佸悕绉? ");
    scanf_s("%s", name, sizeof(name));
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->items[i].name, name) == 0) {
            elemtype item = list->items[i];
            printf("鎵惧埌鍟嗗搧锛氱紪鍙?d 鍚嶇О%s 浠锋牸%.2f 鏁伴噺%d\n", item.id, item.name, item.price, item.quantity);
            return;
        }
    }
    printf("鏈壘鍒拌鍟嗗搧锛乗n");
}

// 鍒犻櫎鍟嗗搧
void deleteShopItem(ShopList *list) {
    int id;
    printf("璇疯緭鍏ヨ鍒犻櫎鐨勫晢鍝佺紪鍙? ");
    scanf_s("%d", &id);
    int found = 0;
    for (int i = 0; i < list->length; i++) {
        if (list->items[i].id == id) {
            found = 1;
            for (int j = i; j < list->length - 1; j++) {
                list->items[j] = list->items[j + 1];
                list->items[j].id = j + 1; // 鏇存柊缂栧彿
            }
            list->length--;
            printf("鍒犻櫎鎴愬姛锛乗n");
            break;
        }
    }
    if (!found) printf("鏈壘鍒拌鍟嗗搧锛乗n");
}

int main() {
    ShopList list;
    int choice;
    initShopList(&list);
    while (1) {
        printf("\n鍟嗗搧淇℃伅绠＄悊绯荤粺\n");
        printf("1. 鍒濆鍖朶n");
        printf("2. 娣诲姞鍟嗗搧\n");
        printf("3. 鏄剧ず鎵€鏈夊晢鍝乗n");
        printf("4. 鏌ユ壘鍟嗗搧\n");
        printf("5. 鍒犻櫎鍟嗗搧\n");
        printf("0. 閫€鍑篭n");
        printf("璇烽€夋嫨: ");
        scanf_s("%d", &choice);
        switch (choice) {
            case 1: initShopList(&list); break;
            case 2: addShopItem(&list); break;
            case 3: showAllShopItems(&list); break;
            case 4: findShopItem(&list); break;
            case 5: deleteShopItem(&list); break;
            case 0: return 0;
            default: printf("鏃犳晥閫夋嫨锛乗n");
        }
    }
    return 0;
}

