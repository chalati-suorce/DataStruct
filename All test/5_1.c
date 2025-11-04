#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


// 先序递归建立二叉树
void CreateBiTree(BiTree *T) {
    char ch;
    scanf("%c", &ch);
    
    while (ch == ' ' || ch == '\n') {
        scanf("%c", &ch);
    }
    
    if (ch == '#') {
        *T = NULL; 
    } else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T) {
            printf("内存分配失败！\n");
            exit(1);
        }
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);  // 左子树
        CreateBiTree(&(*T)->rchild);  // 右子树
    }
}

// 先序遍历 ，根左右
void PreOrderTraverse(BiTree T) {
    if (T) {
        printf("%c ", T->data);
        PreOrderTraverse(T->lchild); 
        PreOrderTraverse(T->rchild); 
    }
}

// 中序遍历，左根右
void InOrderTraverse(BiTree T) {
    if (T) {
        InOrderTraverse(T->lchild); 
        printf("%c ", T->data); 
        InOrderTraverse(T->rchild); 
    }
}

// 后序遍历，左右根
void PostOrderTraverse(BiTree T) {
    if (T) {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c ", T->data); 
    }
}

int main() {
    BiTree T = NULL;
    int choice;
    
    printf("二叉树建立与遍历程序\n");
    printf("请输入扩展先序遍历序列（用#表示空指针，回车结束输入）：\n");
    printf("例如：ABD##E##CF##G##\n");
    
    CreateBiTree(&T);
    
    printf("\n请选择遍历方式：\n");
    printf("1. 先序遍历\n");
    printf("2. 中序遍历\n");
    printf("3. 后序遍历\n");
    printf("4. 所有遍历方式\n");
    printf("请输入选择（1-4）：");
    scanf("%d", &choice);
    
    printf("\n遍历结果：\n");
    
    switch (choice) {
        case 1:
            printf("先序遍历结果：");
            PreOrderTraverse(T);
            printf("\n");
            break;
        case 2:
            printf("中序遍历结果：");
            InOrderTraverse(T);
            printf("\n");
            break;
        case 3:
            printf("后序遍历结果：");
            PostOrderTraverse(T);
            printf("\n");
            break;
        case 4:
            printf("先序遍历结果：");
            PreOrderTraverse(T);
            printf("\n");
            
            printf("中序遍历结果：");
            InOrderTraverse(T);
            printf("\n");
            
            printf("后序遍历结果：");
            PostOrderTraverse(T);
            printf("\n");
            break;
        default:
            printf("无效选择！\n");
            break;
    }
    
    return 0;
}
