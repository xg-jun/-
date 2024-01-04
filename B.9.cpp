#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INFINITY 10000

typedef struct Edge {
    int from, to, weight;
} Edge;

typedef struct {
    Edge edges[MAX_VERTICES];
    int edgeCount;
    int verticesCount;
} Graph;

int earliest[MAX_VERTICES];
int latest[MAX_VERTICES];
int inDegree[MAX_VERTICES];
int outDegree[MAX_VERTICES];
int criticalCount = 0;

void calculateEarliest(Graph *g) {
    for (int i = 0; i < g->verticesCount; ++i) {
        earliest[i] = 0;
    }

    for (int i = 0; i < g->edgeCount; ++i) {
        if (earliest[g->edges[i].to] < earliest[g->edges[i].from] + g->edges[i].weight) {
            earliest[g->edges[i].to] = earliest[g->edges[i].from] + g->edges[i].weight;
        }
    }
}

void calculateLatest(Graph *g, int lastVertex) {
    for (int i = 0; i < g->verticesCount; ++i) {
        latest[i] = INFINITY;
    }

    latest[lastVertex] = earliest[lastVertex];

    for (int i = g->edgeCount - 1; i >= 0; --i) {
        if (latest[g->edges[i].from] > latest[g->edges[i].to] - g->edges[i].weight) {
            latest[g->edges[i].from] = latest[g->edges[i].to] - g->edges[i].weight;
        }
    }
}

void findCriticalPaths(Graph *g) {
    for (int i = 0; i < g->edgeCount; ++i) {
        int e = earliest[g->edges[i].from];
        int l = latest[g->edges[i].to] - g->edges[i].weight;
        if (e == l) {
            criticalCount++;
        }
    }
}

int main() {
    Graph g;
    g.edgeCount = 0;
    g.verticesCount = 5; 
    g.edges[g.edgeCount++] = (Edge){0, 1, 1};
    g.edges[g.edgeCount++] = (Edge){0, 2, 5};
    g.edges[g.edgeCount++] = (Edge){1, 3, 3};
    g.edges[g.edgeCount++] = (Edge){2, 3, 7};
    g.edges[g.edgeCount++] = (Edge){3, 4, 2}; 
    calculateEarliest(&g);
    calculateLatest(&g, g.verticesCount - 1);
    findCriticalPaths(&g);
    printf("关键路径数量: %d\n", criticalCount);

    return 0;
}

