#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

// �Թ��ĵ�Ԫ��ṹ
typedef struct {
    int x, y;
} Point;

// ���еĽṹ
typedef struct {
    Point data[MAXSIZE];
    int front, rear;
} Queue;

// ��ʼ������
void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

// �ж϶����Ƿ�Ϊ��
bool isEmpty(Queue q) {
    return q.front == q.rear;
}

// ���
bool enqueue(Queue *q, Point p) {
    if ((q->rear + 1) % MAXSIZE == q->front) {
        return false; // ������
    }
    q->data[q->rear] = p;
    q->rear = (q->rear + 1) % MAXSIZE;
    return true;
}

// ����
bool dequeue(Queue *q, Point *p) {
    if (q->front == q->rear) {
        return false; // ���п�
    }
    *p = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return true;
}

// �Թ��Ĵ�С������
int N, M;
int maze[MAXSIZE][MAXSIZE];
bool visited[MAXSIZE][MAXSIZE]; // ���ʱ������

// �������飬��ʾ���������ƶ�
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// ����Ƿ�����ߵ������
bool canMoveTo(int x, int y) {
    if (x >= 0 && x < N && y >= 0 && y < M && maze[x][y] == 0 && !visited[x][y]) {
        return true;
    }
    return false;
}

// �ݹ�DFS�㷨
bool recursiveDFS(int x, int y, int destX, int destY, int *pathCount) {
    if (x == destX && y == destY) { // �����յ�
        return true;
    }

    visited[x][y] = true; // ���Ϊ�ѷ���
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        if (canMoveTo(newX, newY)) {
            (*pathCount)++;
            if (recursiveDFS(newX, newY, destX, destY, pathCount)) {
                return true;
            }
            (*pathCount)--; // ����
        }
    }
    visited[x][y] = false; // ����
    return false;
}

// BFS�㷨
int BFS(int startX, int startY, int destX, int destY) {
    Queue q;
    initQueue(&q);
    Point start = {startX, startY};
    enqueue(&q, start);
    int pathCount = 0;
    visited[startX][startY] = true;

    while (!isEmpty(q)) {
        int size = (q.rear - q.front + MAXSIZE) % MAXSIZE; // ��ǰ��Ľڵ���
        pathCount++;
        while (size--) {
            Point p;
            dequeue(&q, &p);
            if (p.x == destX && p.y == destY) {
                return pathCount;
            }
            for (int i = 0; i < 4; i++) {
                int newX = p.x + directions[i][0];
                int newY = p.y + directions[i][1];
                if (canMoveTo(newX, newY)) {
                    visited[newX][newY] = true;
                    Point newPoint = {newX, newY};
                    enqueue(&q, newPoint);
                }
            }
        }
    }
    return -1; // ����޷������յ�
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    int startX, startY, destX, destY;
    scanf("%d %d %d %d", &startX, &startY, &destX, &destY);
    startX--; startY--; destX--; destY--; // �����������ת��Ϊ��������

    // �ݹ�DFS
    int pathCountDFS = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visited[i][j] = false;
        }
    }
    recursiveDFS(startX, startY, destX, destY, &pathCountDFS);

    // BFS
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visited[i][j] = false;
        }
    }
    int pathCountBFS = BFS(startX, startY, destX, destY) - 1; // ��ȥ�������Ĳ���

    printf("%d\n", pathCountDFS);
    printf("%d\n", pathCountBFS);

    return 0;
}

