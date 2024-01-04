#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

// 迷宫的单元格结构
typedef struct {
    int x, y;
} Point;

// 队列的结构
typedef struct {
    Point data[MAXSIZE];
    int front, rear;
} Queue;

// 初始化队列
void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

// 判断队列是否为空
bool isEmpty(Queue q) {
    return q.front == q.rear;
}

// 入队
bool enqueue(Queue *q, Point p) {
    if ((q->rear + 1) % MAXSIZE == q->front) {
        return false; // 队列满
    }
    q->data[q->rear] = p;
    q->rear = (q->rear + 1) % MAXSIZE;
    return true;
}

// 出队
bool dequeue(Queue *q, Point *p) {
    if (q->front == q->rear) {
        return false; // 队列空
    }
    *p = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return true;
}

// 迷宫的大小和数据
int N, M;
int maze[MAXSIZE][MAXSIZE];
bool visited[MAXSIZE][MAXSIZE]; // 访问标记数组

// 方向数组，表示上下左右移动
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 检查是否可以走到这个点
bool canMoveTo(int x, int y) {
    if (x >= 0 && x < N && y >= 0 && y < M && maze[x][y] == 0 && !visited[x][y]) {
        return true;
    }
    return false;
}

// 递归DFS算法
bool recursiveDFS(int x, int y, int destX, int destY, int *pathCount) {
    if (x == destX && y == destY) { // 到达终点
        return true;
    }

    visited[x][y] = true; // 标记为已访问
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        if (canMoveTo(newX, newY)) {
            (*pathCount)++;
            if (recursiveDFS(newX, newY, destX, destY, pathCount)) {
                return true;
            }
            (*pathCount)--; // 回溯
        }
    }
    visited[x][y] = false; // 回溯
    return false;
}

// BFS算法
int BFS(int startX, int startY, int destX, int destY) {
    Queue q;
    initQueue(&q);
    Point start = {startX, startY};
    enqueue(&q, start);
    int pathCount = 0;
    visited[startX][startY] = true;

    while (!isEmpty(q)) {
        int size = (q.rear - q.front + MAXSIZE) % MAXSIZE; // 当前层的节点数
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
    return -1; // 如果无法到达终点
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
    startX--; startY--; destX--; destY--; // 将输入的坐标转换为数组索引

    // 递归DFS
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
    int pathCountBFS = BFS(startX, startY, destX, destY) - 1; // 减去起点自身的步数

    printf("%d\n", pathCountDFS);
    printf("%d\n", pathCountBFS);

    return 0;
}

