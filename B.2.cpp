#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 1000
#define INF 10000000

// ����ߵĽṹ��
struct Edge {
    int source;
    int target;
    int weight;
};

// Bellman-Ford �㷨
void BellmanFord(struct Edge edges[], int V, int E, int source) {
    int i, j;
    int distance[MAX_VERTICES];

    // ��ʼ����������
    for (i = 0; i < V; i++) {
        distance[i] = INF;
    }
    distance[source] = 0;

    // ���� V-1 ���ɳڲ���
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

    // ��⸺Ȩ��ѭ��
    for (i = 0; i < E; i++) {
        int u = edges[i].source;
        int v = edges[i].target;
        int weight = edges[i].weight;
        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            printf("Error\n");
            return;
        }
    }

    // ������
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

    // ��ȡ����ͱߵ�����
    scanf("%d %d", &V, &E);

    // ����������
    struct Edge *edges = (struct Edge *)malloc(E * sizeof(struct Edge));

    // ��ȡ�ߵ���Ϣ
    for (i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].source, &edges[i].target, &edges[i].weight);
        edges[i].source--; // ����Ϊ�� 0 ��ʼ������
        edges[i].target--; // ����Ϊ�� 0 ��ʼ������
    }

    // ��ȡԴ��
    scanf("%d", &source);
    source--; // ����Ϊ�� 0 ��ʼ������

    // ���� Bellman-Ford �㷨
    BellmanFord(edges, V, E, source);

    // ���������ڴ�
    free(edges);

    return 0;
}

