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

// 统计叶子结点个数
int CountLeafNodes(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    if (T->lchild == NULL && T->rchild == NULL) {
        return 1;
    }
    return CountLeafNodes(T->lchild) + CountLeafNodes(T->rchild);
}

// 统计结点总数
int CountNodes(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    return 1 + CountNodes(T->lchild) + CountNodes(T->rchild);
}

// 查找二叉树中是否存在某个值的结点
int SearchNode(BiTree T, char target) {
    if (T == NULL) {
        return 0;
    }
    if (T->data == target) {
        return 1;
    }
    return SearchNode(T->lchild, target) || SearchNode(T->rchild, target);
}

// 交换二叉树所有结点的左右子树
void SwapLeftRight(BiTree T) {
    if (T == NULL) {
        return;
    }
    // 交换左右子树
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    
    // 递归交换左右子树
    SwapLeftRight(T->lchild);
    SwapLeftRight(T->rchild);
}

// 求二叉树的深度
int GetTreeDepth(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    int leftDepth = GetTreeDepth(T->lchild);
    int rightDepth = GetTreeDepth(T->rchild);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

int main() {
    BiTree T = NULL;
    int choice;
    char target;
    
    printf("二叉树建立与遍历程序\n");
    printf("请输入扩展先序遍历序列（用#表示空指针，回车结束输入）：\n");
    printf("例如：ABD##E##CF##G##\n");
    
    CreateBiTree(&T);
    
    while (1) {
        printf("\n========== 二叉树操作菜单 ==========\n");
        printf("1. 先序遍历\n");
        printf("2. 中序遍历\n");
        printf("3. 后序遍历\n");
        printf("4. 所有遍历方式\n");
        printf("5. 统计叶子结点个数\n");
        printf("6. 统计结点总数\n");
        printf("7. 查找结点\n");
        printf("8. 交换左右子树\n");
        printf("9. 求二叉树深度\n");
        printf("0. 退出程序\n");
        printf("请输入选择（0-9）：");
        scanf("%d", &choice);
        
        // 清除输入缓冲区
        while (getchar() != '\n');
        
        printf("\n操作结果：\n");
        
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
            case 5:
                printf("叶子结点个数：%d\n", CountLeafNodes(T));
                break;
            case 6:
                printf("结点总数：%d\n", CountNodes(T));
                break;
            case 7:
                printf("请输入要查找的字符：");
                scanf("%c", &target);
                while (getchar() != '\n'); // 清除输入缓冲区
                if (SearchNode(T, target)) {
                    printf("字符 '%c' 存在于二叉树中\n", target);
                } else {
                    printf("字符 '%c' 不存在于二叉树中\n", target);
                }
                break;
            case 8:
                SwapLeftRight(T);
                printf("已交换所有结点的左右子树\n");
                printf("交换后的先序遍历结果：");
                PreOrderTraverse(T);
                printf("\n");
                break;
            case 9:
                printf("二叉树深度：%d\n", GetTreeDepth(T));
                break;
            case 0:
                printf("程序结束，感谢使用！\n");
                return 0;
            default:
                printf("无效选择！请重新输入。\n");
                break;
        }
    }
    
    return 0;
}
