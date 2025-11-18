#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20  // 最大顶点数

/**
 * 图的邻接矩阵表示
 * 使用二维数组存储顶点之间的边关系
 */
typedef struct {
    int vertex[MAX_VERTEX_NUM];           // 顶点数组，存储顶点信息
    int edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵，存储边关系
    int vertexNum;                        // 顶点数
    int edgeNum;                          // 边数
    bool isDirected;                      // 是否为有向图
} MGraph;

/**
 * 邻接表节点
 * 表示图中的一条边
 */
typedef struct ArcNode {
    int adjvex;              // 该边所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条边的指针
    int info;                // 边的权值
} ArcNode;

/**
 * 顶点节点
 * 表示图中的一个顶点及其邻接边链表
 */
typedef struct VNode {
    int data;               // 顶点信息
    ArcNode *firstarc;      // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MAX_VERTEX_NUM];

/**
 * 邻接表
 * 使用链表数组存储图的邻接关系
 */
typedef struct {
    AdjList vertices;       // 邻接表数组
    int vertexNum;          // 顶点数
    int edgeNum;            // 边数
    bool isDirected;        // 是否为有向图
} ALGraph;

/**
 * 队列结构（用于BFS广度优先搜索）
 * 循环队列实现
 */
typedef struct {
    int data[MAX_VERTEX_NUM];  // 队列数据
    int front;                 // 队头指针
    int rear;                  // 队尾指针
} Queue;

/**
 * 初始化队列
 * @param q 队列指针
 */
void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

/**
 * 判断队列是否为空
 * @param q 队列指针
 * @return true-队列为空，false-队列不为空
 */
bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

/**
 * 入队操作
 * @param q 队列指针
 * @param v 要入队的顶点编号
 */
void enqueue(Queue *q, int v) {
    q->data[q->rear] = v;
    q->rear = (q->rear + 1) % MAX_VERTEX_NUM;
}

/**
 * 出队操作
 * @param q 队列指针
 * @return 出队的顶点编号
 */
int dequeue(Queue *q) {
    int v = q->data[q->front];
    q->front = (q->front + 1) % MAX_VERTEX_NUM;
    return v;
}

/**
 * 初始化邻接矩阵图
 * @param G 图指针
 * @param vertexNum 顶点数
 * @param isDirected 是否为有向图
 */
void initMGraph(MGraph *G, int vertexNum, bool isDirected) {
    G->vertexNum = vertexNum;
    G->edgeNum = 0;
    G->isDirected = isDirected;
    
    // 初始化顶点，顶点编号从0开始
    for (int i = 0; i < vertexNum; i++) {
        G->vertex[i] = i;
    }
    
    // 初始化邻接矩阵，所有边初始化为0（无边）
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            G->edges[i][j] = 0;
        }
    }
}

/**
 * 添加边到邻接矩阵
 * @param G 图指针
 * @param v1 起点顶点编号
 * @param v2 终点顶点编号
 */
void addEdgeMGraph(MGraph *G, int v1, int v2) {
    if (v1 >= 0 && v1 < G->vertexNum && v2 >= 0 && v2 < G->vertexNum) {
        G->edges[v1][v2] = 1;  // 设置边存在
        if (!G->isDirected) {
            G->edges[v2][v1] = 1;  // 如果是无向图，添加对称边
        }
        G->edgeNum++;
    }
}

/**
 * 打印邻接矩阵
 * @param G 图指针
 */
void printAdjMatrix(MGraph *G) {
    printf("邻接矩阵:\n");
    printf("   ");
    for (int i = 0; i < G->vertexNum; i++) {
        printf("%2d ", i);  // 打印列标题
    }
    printf("\n");
    
    for (int i = 0; i < G->vertexNum; i++) {
        printf("%2d ", i);  // 打印行标题
        for (int j = 0; j < G->vertexNum; j++) {
            printf("%2d ", G->edges[i][j]);  // 打印邻接矩阵元素
        }
        printf("\n");
    }
}

/**
 * 深度优先搜索（递归实现）
 * @param G 图指针
 * @param v 当前访问的顶点
 * @param visited 访问标记数组
 */
void DFS(MGraph *G, int v, bool visited[]) {
    visited[v] = true;  // 标记当前顶点已访问
    printf("%d ", v);   // 输出当前顶点
    
    // 遍历所有邻接顶点
    for (int i = 0; i < G->vertexNum; i++) {
        if (G->edges[v][i] == 1 && !visited[i]) {
            DFS(G, i, visited);  // 递归访问未访问的邻接顶点
        }
    }
}

/**
 * 深度优先搜索整个图
 * @param G 图指针
 */
void DFSTraverse(MGraph *G) {
    bool visited[MAX_VERTEX_NUM] = {false};  // 初始化访问标记数组
    printf("深度优先搜索序列: ");
    
    // 遍历所有顶点，处理非连通图
    for (int i = 0; i < G->vertexNum; i++) {
        if (!visited[i]) {
            DFS(G, i, visited);  // 从每个未访问的顶点开始DFS
        }
    }
    printf("\n");
}

/**
 * 广度优先搜索整个图
 * @param G 图指针
 */
void BFSTraverse(MGraph *G) {
    bool visited[MAX_VERTEX_NUM] = {false};  // 初始化访问标记数组
    Queue q;
    initQueue(&q);
    
    printf("广度优先搜索序列: ");
    
    // 遍历所有顶点，处理非连通图
    for (int i = 0; i < G->vertexNum; i++) {
        if (!visited[i]) {
            visited[i] = true;
            printf("%d ", i);
            enqueue(&q, i);  // 将起始顶点入队
            
            // BFS遍历当前连通分量
            while (!isEmpty(&q)) {
                int v = dequeue(&q);  // 出队一个顶点
                // 遍历所有邻接顶点
                for (int j = 0; j < G->vertexNum; j++) {
                    if (G->edges[v][j] == 1 && !visited[j]) {
                        visited[j] = true;
                        printf("%d ", j);
                        enqueue(&q, j);  // 将未访问的邻接顶点入队
                    }
                }
            }
        }
    }
    printf("\n");
}

/**
 * 初始化邻接表
 * @param G 邻接表图指针
 * @param vertexNum 顶点数
 * @param isDirected 是否为有向图
 */
void initALGraph(ALGraph *G, int vertexNum, bool isDirected) {
    G->vertexNum = vertexNum;
    G->edgeNum = 0;
    G->isDirected = isDirected;
    
    // 初始化所有顶点的邻接表
    for (int i = 0; i < vertexNum; i++) {
        G->vertices[i].data = i;        // 设置顶点数据
        G->vertices[i].firstarc = NULL; // 初始化邻接边链表为空
    }
}

/**
 * 添加边到邻接表
 * @param G 邻接表图指针
 * @param v1 起点顶点编号
 * @param v2 终点顶点编号
 */
void addEdgeALGraph(ALGraph *G, int v1, int v2) {
    if (v1 >= 0 && v1 < G->vertexNum && v2 >= 0 && v2 < G->vertexNum) {
        // 添加v1->v2的边（头插法）
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

/**
 * 打印邻接表
 * @param G 邻接表图指针
 */
void printAdjList(ALGraph *G) {
    printf("邻接表:\n");
    for (int i = 0; i < G->vertexNum; i++) {
        printf("顶点%d: ", i);
        ArcNode *p = G->vertices[i].firstarc;
        // 遍历当前顶点的所有邻接边
        while (p != NULL) {
            printf("->%d", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
}

// 手动输入图信息
void inputGraphManually(MGraph *G) {
    int vertexNum, edgeNum;
    bool isDirected;
    char directedChoice;
    
    printf("请输入图的顶点数: ");
    scanf("%d", &vertexNum);
    
    printf("是否为有向图? (y/n): ");
    scanf(" %c", &directedChoice);
    isDirected = (directedChoice == 'y' || directedChoice == 'Y');
    
    printf("请输入边的数量: ");
    scanf("%d", &edgeNum);
    
    // 初始化图
    initMGraph(G, vertexNum, isDirected);
    
    printf("请输入边的信息 (格式: 起点 终点):\n");
    for (int i = 0; i < edgeNum; i++) {
        int v1, v2;
        printf("边 %d: ", i + 1);
        scanf("%d %d", &v1, &v2);
        
        if (v1 >= 0 && v1 < vertexNum && v2 >= 0 && v2 < vertexNum) {
            addEdgeMGraph(G, v1, v2);
        } else {
            printf("错误: 顶点编号应在 0 到 %d 之间\n", vertexNum - 1);
            i--; // 重新输入这条边
        }
    }
}

/**
 * 测试输入示例：
 * 
 * 示例1：无向图（邻接矩阵）
 * 选择操作：1
 * 顶点数：5
 * 是否为有向图：n
 * 边的数量：6
 * 边信息：
 *   边1：0 1
 *   边2：0 2
 *   边3：1 3
 *   边4：2 4
 *   边5：3 4
 *   边6：1 4
 * 
 * 示例2：有向图（邻接表）
 * 选择操作：2
 * 顶点数：4
 * 是否为有向图：y
 * 边的数量：5
 * 边信息：
 *   边1：0 1
 *   边2：0 2
 *   边3：1 3
 *   边4：2 3
 *   边5：3 0
 * 
 * 示例3：简单树结构（无向图）
 * 选择操作：1
 * 顶点数：6
 * 是否为有向图：n
 * 边的数量：5
 * 边信息：
 *   边1：0 1
 *   边2：0 2
 *   边3：1 3
 *   边4：1 4
 *   边5：2 5
 * 
 * 示例4：完全图（有向图）
 * 选择操作：2
 * 顶点数：3
 * 是否为有向图：y
 * 边的数量：6
 * 边信息：
 *   边1：0 1
 *   边2：0 2
 *   边3：1 0
 *   边4：1 2
 *   边5：2 0
 *   边6：2 1
 */

// 手动输入邻接表图信息
void inputALGraphManually(ALGraph *G) {
    int vertexNum, edgeNum;
    bool isDirected;
    char directedChoice;
    
    printf("请输入图的顶点数: ");
    scanf("%d", &vertexNum);
    
    printf("是否为有向图? (y/n): ");
    scanf(" %c", &directedChoice);
    isDirected = (directedChoice == 'y' || directedChoice == 'Y');
    
    printf("请输入边的数量: ");
    scanf("%d", &edgeNum);
    
    // 初始化图
    initALGraph(G, vertexNum, isDirected);
    
    printf("请输入边的信息 (格式: 起点 终点):\n");
    for (int i = 0; i < edgeNum; i++) {
        int v1, v2;
        printf("边 %d: ", i + 1);
        scanf("%d %d", &v1, &v2);
        
        if (v1 >= 0 && v1 < vertexNum && v2 >= 0 && v2 < vertexNum) {
            addEdgeALGraph(G, v1, v2);
        } else {
            printf("错误: 顶点编号应在 0 到 %d 之间\n", vertexNum - 1);
            i--; // 重新输入这条边
        }
    }
}

int main() {
    printf("=== 图的操作演示 (手动输入模式) ===\n\n");
    
    int choice;
    
    do {
        printf("\n请选择操作:\n");
        printf("1. 使用邻接矩阵创建图\n");
        printf("2. 使用邻接表创建图\n");
        printf("3. 退出\n");
        printf("请输入选择 (1-3): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                printf("\n=== 邻接矩阵图 ===\n");
                MGraph graph;
                inputGraphManually(&graph);
                
                printf("\n图信息:\n");
                printf("顶点数: %d\n", graph.vertexNum);
                printf("边数: %d\n", graph.edgeNum);
                printf("是否为有向图: %s\n", graph.isDirected ? "是" : "否");
                
                printf("\n邻接矩阵:\n");
                printAdjMatrix(&graph);
                
                printf("\n遍历序列:\n");
                DFSTraverse(&graph);
                BFSTraverse(&graph);
                break;
            }
            
            case 2: {
                printf("\n=== 邻接表图 ===\n");
                ALGraph graph;
                inputALGraphManually(&graph);
                
                printf("\n图信息:\n");
                printf("顶点数: %d\n", graph.vertexNum);
                printf("边数: %d\n", graph.edgeNum);
                printf("是否为有向图: %s\n", graph.isDirected ? "是" : "否");
                
                printf("\n邻接表:\n");
                printAdjList(&graph);
                break;
            }
            
            case 3:
                printf("程序结束，再见！\n");
                break;
                
            default:
                printf("无效选择，请重新输入！\n");
                break;
        }
    } while (choice != 3);
    
    return 0;
}
