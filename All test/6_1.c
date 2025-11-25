#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 边结点
typedef struct enode {
    int adjvex;
    struct enode *next;
} ENode;

// 顶点结点
typedef struct vnode {
    char vertex;
    ENode *first;
} VNode;

// 图的邻接表
typedef struct {
    VNode adjlist[100];
    int n, e;
} Graph;

//辅助队列（用于广度优先遍历）
typedef struct Queue {
    int data[100];
    int front, rear;
} Queue;

void InitQueue(Queue *q) {
    q->front = q->rear = 0;
}

void EnQueue(Queue *q, int x) {
    q->data[q->rear++] = x;
}

int DeQueue(Queue *q) {
    return q->data[q->front++];
}

int QueueEmpty(Queue *q) {
    return q->front == q->rear;
}

void InitGraph(Graph *G) {
    G->n = G->e = 0;
    for (int i = 0; i < 100; i++) {
        G->adjlist[i].first = NULL;
    }
}

//查找顶点对应的索引
int LocateVertex(Graph *G, char v) {
    for (int i = 0; i < G->n; i++) {
        if (G->adjlist[i].vertex == v) {
            return i;
        }
    }
    return -1;
}

//建立无向图的邻接表
void CreateGraph(Graph *G) {
    printf("请输入顶点数（例如：4）：");
    scanf("%d", &G->n);
    printf("请输入顶点信息（连续输入顶点字符，如ABCD）：");
    char vertex_input[100];
    scanf("%s", vertex_input);

    for (int i = 0; i < G->n; i++) {
        G->adjlist[i].vertex = vertex_input[i];
    }
    
    printf("请输入边数（例如：5）：");
    scanf("%d", &G->e);
    
    for (int k = 0; k < G->e; k++) {
        char v1, v2;
        printf("请输入第%d条边对应的两个顶点（格式如AB）：", k+1);
        scanf(" %c%c", &v1, &v2);
        
        int i = LocateVertex(G, v1);
        int j = LocateVertex(G, v2);
        if (i == -1 || j == -1) {
            printf("错误：顶点 %c 或 %c 不存在！请重新输入！\n", v1, v2);
            printf("当前存在的顶点：");
            for (int idx = 0; idx < G->n; idx++) {
                printf("%c ", G->adjlist[idx].vertex);
            }
            printf("\n");
            k--;
            continue;
        }

        ENode *p = (ENode*)malloc(sizeof(ENode));
        p->adjvex = j;
        p->next = G->adjlist[i].first;
        G->adjlist[i].first = p;

        ENode *q = (ENode*)malloc(sizeof(ENode));
        q->adjvex = i;
        q->next = G->adjlist[j].first;
        G->adjlist[j].first = q;
        
        printf("成功创建边：%c-%c\n", v1, v2);
    }
}

void PrintGraph(Graph *G) {
    printf("\n图的邻接表：\n");
    for (int i = 0; i < G->n; i++) {
        printf("Vertex %c：", G->adjlist[i].vertex);
        ENode *p = G->adjlist[i].first;
        while (p) {
            printf("%c -> ", G->adjlist[p->adjvex].vertex);
            p = p->next;
        }
        printf("NULL\n");
    }
}

int visited[100];

// 深度优先（递归）
void DFS(Graph *G, int v) {
    printf("%c ", G->adjlist[v].vertex);
    visited[v] = 1;
    ENode *p = G->adjlist[v].first;
    while (p) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex);
        }
        p = p->next;
    }
}

// 广度优先
void BFS(Graph *G, int v) {
    Queue q;
    InitQueue(&q);
    printf("%c ", G->adjlist[v].vertex);
    visited[v] = 1;
    EnQueue(&q, v);
    
    while (!QueueEmpty(&q)) {
        int u = DeQueue(&q);
        ENode *p = G->adjlist[u].first;
        while (p) {
            if (!visited[p->adjvex]) {
                printf("%c ", G->adjlist[p->adjvex].vertex);
                visited[p->adjvex] = 1;
                EnQueue(&q, p->adjvex);
            }
            p = p->next;
        }
    }
}

void InitVisited() {
    memset(visited, 0, sizeof(visited));
}


int main() {
    Graph G;
    InitGraph(&G);
    
    printf("图遍历程序：\n");
    printf("本程序演示图的邻接表表示和遍历算法\n");
    printf("请输入图的数据：\n\n");
    
    CreateGraph(&G);
    PrintGraph(&G);

    int start;
    printf("\n请输入深度优先遍历的起始顶点索引（0~%d）：", G.n-1);
    scanf("%d", &start);
    if (start < 0 || start >= G.n) {
        printf("索引无效！\n");
        return 1;
    }
    printf("深度优先遍历结果：");
    InitVisited();
    DFS(&G, start);
    printf("\n");

    printf("请输入广度优先遍历的起始顶点索引（0~%d）：", G.n-1);
    scanf("%d", &start);
    if (start < 0 || start >= G.n) {
        printf("索引无效！\n");
        return 1;
    }
    printf("广度优先遍历结果：");
    InitVisited();
    BFS(&G, start);
    printf("\n");
    
    return 0;
}
