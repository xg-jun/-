#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 1000
#define INF 10000000

// 定义边的结构体
struct Edge {
    int source;
    int target;
    int weight;
};

// Bellman-Ford 算法
void BellmanFord(struct Edge edges[], int V, int E, int source) {
    int i, j;
    int distance[MAX_VERTICES];

    // 初始化距离数组
    for (i = 0; i < V; i++) {
        distance[i] = INF;
    }
    distance[source] = 0;

    // 进行 V-1 轮松弛操作
    for (i = 0; i < V - 1; i++) {
        for (j = 0; j < E; j++) {
            int u = edges[j].source;
            int v = edges[j].target;
            int weight = edges[j].weight;
            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // 检测负权重循环
    for (i = 0; i < E; i++) {
        int u = edges[i].source;
        int v = edges[i].target;
        int weight = edges[i].weight;
        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            printf("Error\n");
            return;
        }
    }

    // 输出结果
    for (i = 0; i < V; i++) {
        if (distance[i] == INF) {
            printf("INF\n");
        } else {
            printf("%d\n", distance[i]);
        }
    }
}

int main() {
    int V, E, i;
    int source;

    // 读取顶点和边的数量
    scanf("%d %d", &V, &E);

    // 创建边数组
    struct Edge *edges = (struct Edge *)malloc(E * sizeof(struct Edge));

    // 读取边的信息
    for (i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].source, &edges[i].target, &edges[i].weight);
        edges[i].source--; // 调整为从 0 开始的索引
        edges[i].target--; // 调整为从 0 开始的索引
    }

    // 读取源点
    scanf("%d", &source);
    source--; // 调整为从 0 开始的索引

    // 运行 Bellman-Ford 算法
    BellmanFord(edges, V, E, source);

    // 清理分配的内存
    free(edges);

    return 0;
}

