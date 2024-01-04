#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// �ڽӱ��еĽڵ�
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// �ڽӱ�
typedef struct Graph {
    Node* adjList[MAX];
    int numVertices;
} Graph;

// �����½ڵ�
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// ��ӱߵ�����ͼ
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// ���������������
void DFS(Graph* graph, int v, int visited[]) {
    visited[v] = 1;  // ���ڵ���Ϊ�ѷ���

    Node* temp = graph->adjList[v];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// ��ת����ͼ�ı�
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

// �ж�����ͼ�Ƿ���ǿ��ͨͼ
int isStronglyConnected(Graph* graph) {
    int visited[MAX] = {0};

    // �ӵ�һ���ڵ㿪ʼ�����������
    DFS(graph, 0, visited);

    // ����Ƿ���δ���ʵĽڵ�
    for (int v = 0; v < graph->numVertices; v++) {
        if (visited[v] == 0) {
            return 0;  // ����ǿ��ͨͼ
        }
    }

    // ��ת����ͼ�ı�
    Graph* transposedGraph = getTranspose(graph);

    // ���÷�������
    for (int v = 0; v < graph->numVertices; v++) {
        visited[v] = 0;
    }

    // �ӵ�һ���ڵ㿪ʼ�������������ת���ͼ
    DFS(transposedGraph, 0, visited);

    // ����Ƿ���δ���ʵĽڵ�
    for (int v = 0; v < graph->numVertices; v++) {
        if (visited[v] == 0) {
            return 0;  // ����ǿ��ͨͼ
        }
    }

    return 1;  // ��ǿ��ͨͼ
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

