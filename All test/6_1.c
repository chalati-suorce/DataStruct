#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20

// 图的邻接矩阵表示
typedef struct {
    int vertex[MAX_VERTEX_NUM];           // 顶点数组
    int edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵
    int vertexNum;                        // 顶点数
    int edgeNum;                          // 边数
    bool isDirected;                      // 是否为有向图
} MGraph;

// 邻接表节点
typedef struct ArcNode {
    int adjvex;              // 该边所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条边的指针
    int info;                // 边的权值
} ArcNode;

// 顶点节点
typedef struct VNode {
    int data;               // 顶点信息
    ArcNode *firstarc;      // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MAX_VERTEX_NUM];

// 邻接表
typedef struct {
    AdjList vertices;       // 邻接表
    int vertexNum;          // 顶点数
    int edgeNum;            // 边数
    bool isDirected;        // 是否为有向图
} ALGraph;

// 队列结构（用于BFS）
typedef struct {
    int data[MAX_VERTEX_NUM];
    int front;
    int rear;
} Queue;

// 队列操作
void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int v) {
    q->data[q->rear] = v;
    q->rear = (q->rear + 1) % MAX_VERTEX_NUM;
}

int dequeue(Queue *q) {
    int v = q->data[q->front];
    q->front = (q->front + 1) % MAX_VERTEX_NUM;
    return v;
}

// 初始化邻接矩阵图
void initMGraph(MGraph *G, int vertexNum, bool isDirected) {
    G->vertexNum = vertexNum;
    G->edgeNum = 0;
    G->isDirected = isDirected;
    
    // 初始化顶点
    for (int i = 0; i < vertexNum; i++) {
        G->vertex[i] = i;
    }
    
    // 初始化邻接矩阵
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            G->edges[i][j] = 0;
        }
    }
}

// 添加边到邻接矩阵
void addEdgeMGraph(MGraph *G, int v1, int v2) {
    if (v1 >= 0 && v1 < G->vertexNum && v2 >= 0 && v2 < G->vertexNum) {
        G->edges[v1][v2] = 1;
        if (!G->isDirected) {
            G->edges[v2][v1] = 1;
        }
        G->edgeNum++;
    }
}

// 打印邻接矩阵
void printAdjMatrix(MGraph *G) {
    printf("邻接矩阵:\n");
    printf("   ");
    for (int i = 0; i < G->vertexNum; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < G->vertexNum; i++) {
        printf("%2d ", i);
        for (int j = 0; j < G->vertexNum; j++) {
            printf("%2d ", G->edges[i][j]);
        }
        printf("\n");
    }
}

// 深度优先搜索（递归）
void DFS(MGraph *G, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);
    
    for (int i = 0; i < G->vertexNum; i++) {
        if (G->edges[v][i] == 1 && !visited[i]) {
            DFS(G, i, visited);
        }
    }
}

// 深度优先搜索整个图
void DFSTraverse(MGraph *G) {
    bool visited[MAX_VERTEX_NUM] = {false};
    printf("深度优先搜索序列: ");
    
    for (int i = 0; i < G->vertexNum; i++) {
        if (!visited[i]) {
            DFS(G, i, visited);
        }
    }
    printf("\n");
}

// 广度优先搜索整个图
void BFSTraverse(MGraph *G) {
    bool visited[MAX_VERTEX_NUM] = {false};
    Queue q;
    initQueue(&q);
    
    printf("广度优先搜索序列: ");
    
    for (int i = 0; i < G->vertexNum; i++) {
        if (!visited[i]) {
            visited[i] = true;
            printf("%d ", i);
            enqueue(&q, i);
            
            while (!isEmpty(&q)) {
                int v = dequeue(&q);
                for (int j = 0; j < G->vertexNum; j++) {
                    if (G->edges[v][j] == 1 && !visited[j]) {
                        visited[j] = true;
                        printf("%d ", j);
                        enqueue(&q, j);
                    }
                }
            }
        }
    }
    printf("\n");
}

// 初始化邻接表
void initALGraph(ALGraph *G, int vertexNum, bool isDirected) {
    G->vertexNum = vertexNum;
    G->edgeNum = 0;
    G->isDirected = isDirected;
    
    for (int i = 0; i < vertexNum; i++) {
        G->vertices[i].data = i;
        G->vertices[i].firstarc = NULL;
    }
}

// 添加边到邻接表
void addEdgeALGraph(ALGraph *G, int v1, int v2) {
    if (v1 >= 0 && v1 < G->vertexNum && v2 >= 0 && v2 < G->vertexNum) {
        // 添加v1->v2的边
        ArcNode *newArc = (ArcNode *)malloc(sizeof(ArcNode));
        newArc->adjvex = v2;
        newArc->nextarc = G->vertices[v1].firstarc;
        newArc->info = 1;
        G->vertices[v1].firstarc = newArc;
        
        // 如果是无向图，添加v2->v1的边
        if (!G->isDirected) {
            ArcNode *newArc2 = (ArcNode *)malloc(sizeof(ArcNode));
            newArc2->adjvex = v1;
            newArc2->nextarc = G->vertices[v2].firstarc;
            newArc2->info = 1;
            G->vertices[v2].firstarc = newArc2;
        }
        
        G->edgeNum++;
    }
}

// 打印邻接表
void printAdjList(ALGraph *G) {
    printf("邻接表:\n");
    for (int i = 0; i < G->vertexNum; i++) {
        printf("顶点%d: ", i);
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            printf("->%d", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
}

int main() {
    printf("=== 图的操作演示 ===\n\n");
    
    // 示例图结构（无向图）
    // 顶点: 0,1,2,3,4
    // 边: (0,1), (0,2), (1,3), (2,4), (3,4)
    
    // 1. 创建无向图的邻接矩阵
    printf("1. 无向图的邻接矩阵:\n");
    MGraph undirectedGraph;
    initMGraph(&undirectedGraph, 5, false);
    
    // 添加边
    addEdgeMGraph(&undirectedGraph, 0, 1);
    addEdgeMGraph(&undirectedGraph, 0, 2);
    addEdgeMGraph(&undirectedGraph, 1, 3);
    addEdgeMGraph(&undirectedGraph, 2, 4);
    addEdgeMGraph(&undirectedGraph, 3, 4);
    
    printAdjMatrix(&undirectedGraph);
    printf("\n");
    
    // 2. 深度优先搜索和广度优先搜索序列
    printf("2. 无向图的遍历序列:\n");
    DFSTraverse(&undirectedGraph);
    BFSTraverse(&undirectedGraph);
    printf("\n");
    
    // 3. 创建有向图的邻接表
    printf("3. 有向图的邻接表:\n");
    ALGraph directedGraph;
    initALGraph(&directedGraph, 5, true);
    
    // 添加有向边
    addEdgeALGraph(&directedGraph, 0, 1);
    addEdgeALGraph(&directedGraph, 0, 2);
    addEdgeALGraph(&directedGraph, 1, 3);
    addEdgeALGraph(&directedGraph, 2, 4);
    addEdgeALGraph(&directedGraph, 3, 4);
    
    printAdjList(&directedGraph);
    printf("\n");
    
    // 4. 实现图的邻接矩阵表示并建立无向图
    printf("4. 邻接矩阵表示的无向图:\n");
    MGraph customGraph;
    initMGraph(&customGraph, 6, false);
    
    // 建立另一个无向图
    addEdgeMGraph(&customGraph, 0, 1);
    addEdgeMGraph(&customGraph, 0, 2);
    addEdgeMGraph(&customGraph, 1, 3);
    addEdgeMGraph(&customGraph, 2, 4);
    addEdgeMGraph(&customGraph, 3, 5);
    addEdgeMGraph(&customGraph, 4, 5);
    
    printAdjMatrix(&customGraph);
    printf("\n");
    
    // 5. 深度优先搜索和广度优先搜索整个图
    printf("5. 图的遍历:\n");
    DFSTraverse(&customGraph);
    BFSTraverse(&customGraph);
    
    return 0;
}
