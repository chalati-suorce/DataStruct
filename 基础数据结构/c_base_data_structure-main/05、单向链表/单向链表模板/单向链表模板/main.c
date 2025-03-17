#include <stdio.h>
#include <stdlib.h>

#define eleType int

// ����������Ķ���
typedef struct ListNode {
    eleType data;
    struct ListNode* next;
}ListNode;

// ��������Ķ���
typedef struct LinkedList {
    struct ListNode* head;
    size_t size;
}LinkedList;

// ��������
void LinkedListCreate(LinkedList* list) {
    // ��ʼ������ͷΪ NULL
    list->head = NULL;
    list->size = 0;
}

// ��������
void LinkedListDestroy(LinkedList* list) {
    // ���������ͷ�ÿ�����
    while (list->head) {
        ListNode* temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    list->size = 0;
}

// ������ list �ĵ� i ��λ�ò���һ��ֵΪ value �Ľ��
void LinkedListInsert(LinkedList* list, int i, eleType value) {
    if (i < 0 || i > list->size) {
        printf("Invalid index\n");
        return;
    }

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = value;

    if (i == 0) {
        newNode->next = list->head;
        list->head = newNode;
    }
    else {
        ListNode* current = list->head;
        for (int j = 0; j < i - 1; j++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->size++;
}

// ɾ������ list �ĵ� i �����
void LinkedListRemove(LinkedList* list, int i) {
    if (i < 0 || i >= list->size) {
        printf("Invalid index\n");
        return;
    }

    if (i == 0) {
        ListNode* next = list->head->next;
        free(list->head);
        list->head = next;
    }
    else {
        ListNode* current = list->head;
        for (int j = 0; j < i - 1; j++) {
            current = current->next;
        }
        ListNode* next = current->next->next;
        free(current->next);
        current->next = next;
    }
    list->size--;
}

// �������� list ��ֵΪ value �Ľ�㣬������
ListNode* LinkedListFind(LinkedList* list, eleType value) {
    ListNode* current = list->head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// ��ȡ���� list �е� i �����
ListNode* LinkedListGet(LinkedList* list, int i) {
    if (i < 0 || i >= list->size) {
        printf("Invalid index\n");
        return NULL;
    }

    ListNode* current = list->head;
    for (int j = 0; j < i; j++) {
        current = current->next;
    }
    return current;
}

// �������� list �е� i ������ֵΪ value
void LinkedListUpdate(LinkedList* list, int i, eleType value) {
    ListNode* node = LinkedListGet(list, i);
    if (node != NULL) {
        node->data = value;
    }
    else {
        printf("Invalid index\n");
    }
}

// ��ӡ����
void LinkedListPrint(LinkedList* list) {
    ListNode* current = list->head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    // ����һ������
    LinkedList list;
    list.head = NULL;
    list.size = 0;

    // ����Ԫ��
    LinkedListInsert(&list, 0, 10);
    LinkedListInsert(&list, 1, 20);
    LinkedListInsert(&list, 2, 30);
    LinkedListInsert(&list, 3, 40);

    // ��ӡԭʼ����
    printf("Original List: ");
    LinkedListPrint(&list);

    // ɾ���� 2 �����
    LinkedListRemove(&list, 2);

    // ���µ� 1 ������ֵ
    LinkedListUpdate(&list, 1, 100);

    // ����ֵΪ 30 �Ľ��
    ListNode* found = LinkedListFind(&list, 30);
    if (found != NULL) {
        printf("Element found!\n");
    }
    else {
        printf("Element not found!\n");
    }

    // ��ȡ�� 2 �����
    ListNode* node = LinkedListGet(&list, 2);
    if (node != NULL) {
        printf("Element at index 2: %d\n", node->data);
    }
    else {
        printf("Element at index 2 not found!\n");
    }

    // ��ӡ���º������
    printf("Updated List: ");
    LinkedListPrint(&list);

    return 0;
}