#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//图的邻接表结构定义
// 边结点结构
typedef struct enode {
    int adjvex;          // 邻接点的索引
    struct enode *next;  // 指向下一个边结点
} ENode;

// 顶点结点结构
typedef struct vnode {
    char vertex;         // 顶点信息（字符型）
    ENode *first;        // 指向第一个边结点
} VNode;

// 图的邻接表结构
typedef struct {
    VNode adjlist[100];  // 顶点数组（最多100个顶点）
    int n, e;            // 顶点数n，边数e
} Graph;

//辅助队列（用于广度优先遍历）
typedef struct Queue {
    int data[100];
    int front, rear;
} Queue;

// 初始化队列
void InitQueue(Queue *q) {
    q->front = q->rear = 0;
}

// 入队
void EnQueue(Queue *q, int x) {
    q->data[q->rear++] = x;
}

// 出队
int DeQueue(Queue *q) {
    return q->data[q->front++];
}

// 判断队列是否为空
int QueueEmpty(Queue *q) {
    return q->front == q->rear;
}


//图的基本操作
// 1. 初始化图
void InitGraph(Graph *G) {
    G->n = G->e = 0;
    for (int i = 0; i < 100; i++) {
        G->adjlist[i].first = NULL;
    }
}

// 2. 查找顶点对应的索引
int LocateVertex(Graph *G, char v) {
    for (int i = 0; i < G->n; i++) {
        if (G->adjlist[i].vertex == v) {
            return i;
        }
    }
    return -1;  // 未找到
}

// 3. 建立无向图的邻接表
void CreateGraph(Graph *G) {
    printf("请输入顶点数（例如：4）：");
    scanf("%d", &G->n);
    printf("请输入顶点信息（连续输入顶点字符，如ABCD）：");
    char vertex_input[100];
    scanf("%s", vertex_input);
    
    // 将输入的顶点字符逐个存储到顶点数组中
    for (int i = 0; i < G->n; i++) {
        G->adjlist[i].vertex = vertex_input[i];
    }
    
    printf("请输入边数（例如：5）：");
    scanf("%d", &G->e);
    
    printf("\n=== 边输入说明 ===\n");
    printf("请输入边的两个顶点，格式为：AB 表示顶点A和B之间的边\n");
    printf("注意：这是无向图，输入AB会自动创建A-B和B-A两条边\n\n");
    
    for (int k = 0; k < G->e; k++) {
        char v1, v2;
        printf("请输入第%d条边对应的两个顶点（格式如AB）：", k+1);
        scanf(" %c%c", &v1, &v2);  // 注意空格吸收换行
        
        int i = LocateVertex(G, v1);
        int j = LocateVertex(G, v2);
        if (i == -1 || j == -1) {
            printf("错误：顶点 %c 或 %c 不存在！请重新输入！\n", v1, v2);
            printf("当前存在的顶点：");
            for (int idx = 0; idx < G->n; idx++) {
                printf("%c ", G->adjlist[idx].vertex);
            }
            printf("\n");
            k--;  // 重新输入当前边
            continue;
        }
        
        // 插入边 i->j
        ENode *p = (ENode*)malloc(sizeof(ENode));
        p->adjvex = j;
        p->next = G->adjlist[i].first;
        G->adjlist[i].first = p;
        
        // 无向图，插入边 j->i
        ENode *q = (ENode*)malloc(sizeof(ENode));
        q->adjvex = i;
        q->next = G->adjlist[j].first;
        G->adjlist[j].first = q;
        
        printf("成功创建边：%c-%c\n", v1, v2);
    }
}

// 4. 输出图的邻接表
void PrintGraph(Graph *G) {
    printf("\n===== 图的邻接表 =====\n");
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

// 图的遍历（深度/广度优先）
int visited[100];  // 标记顶点是否被访问

// 深度优先遍历（递归）
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

// 广度优先遍历
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

// 初始化访问标记数组
void InitVisited() {
    memset(visited, 0, sizeof(visited));
}


int main() {
    Graph G;
    InitGraph(&G);
    
    printf("===== 图遍历程序 =====\n");
    printf("本程序演示图的邻接表表示和遍历算法\n");
    printf("请输入图的数据：\n\n");
    
    CreateGraph(&G);
    PrintGraph(&G);
    
    // 深度优先遍历
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
    
    // 广度优先遍历
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
