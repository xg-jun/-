#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// 邻接表中的节点
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 邻接表
typedef struct Graph {
    Node* adjList[MAX];
    int numVertices;
} Graph;

// 创建新节点
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 添加边到有向图
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// 深度优先搜索函数
void DFS(Graph* graph, int v, int visited[]) {
    visited[v] = 1;  // 将节点标记为已访问

    Node* temp = graph->adjList[v];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// 反转有向图的边
Graph* getTranspose(Graph* graph) {
    Graph* transposedGraph = (Graph*)malloc(sizeof(Graph));
    transposedGraph->numVertices = graph->numVertices;

    for (int v = 0; v < graph->numVertices; v++) {
        transposedGraph->adjList[v] = NULL;
    }

    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjList[v];
        while (temp != NULL) {
            addEdge(transposedGraph, temp->vertex, v);
            temp = temp->next;
        }
    }

    return transposedGraph;
}

// 判断有向图是否是强连通图
int isStronglyConnected(Graph* graph) {
    int visited[MAX] = {0};

    // 从第一个节点开始深度优先搜索
    DFS(graph, 0, visited);

    // 检查是否有未访问的节点
    for (int v = 0; v < graph->numVertices; v++) {
        if (visited[v] == 0) {
            return 0;  // 不是强连通图
        }
    }

    // 反转有向图的边
    Graph* transposedGraph = getTranspose(graph);

    // 重置访问数组
    for (int v = 0; v < graph->numVertices; v++) {
        visited[v] = 0;
    }

    // 从第一个节点开始深度优先搜索反转后的图
    DFS(transposedGraph, 0, visited);

    // 检查是否有未访问的节点
    for (int v = 0; v < graph->numVertices; v++) {
        if (visited[v] == 0) {
            return 0;  // 不是强连通图
        }
    }

    return 1;  // 是强连通图
}

int main() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = 5;

    for (int i = 0; i < graph->numVertices; i++) {
        graph->adjList[i] = NULL;
    }

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 1);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 0);
    addEdge(graph, 3, 2);
    addEdge(graph, 4, 2);

    if (isStronglyConnected(graph)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}

