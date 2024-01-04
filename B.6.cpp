#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define MAXM 500

typedef struct {
    int from, to, duration;
} Edge;

int N, M;
Edge edges[MAXM];
int earliest[MAXN], latest[MAXN], indegree[MAXN];
int stack[MAXN], top; // 用于保存当前路径的栈
int visited[MAXN]; // 标记节点是否被访问过

// 计算最早开始时间
void calculateEarliest() {
    memset(earliest, 0, sizeof(earliest));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (earliest[edges[j].to] < earliest[edges[j].from] + edges[j].duration) {
                earliest[edges[j].to] = earliest[edges[j].from] + edges[j].duration;
            }
        }
    }
}

// 计算最晚开始时间
void calculateLatest() {
    for (int i = 0; i < N; ++i) {
        latest[i] = earliest[N - 1];
    }
    for (int i = N - 1; i >= 0; --i) {
        for (int j = 0; j < M; ++j) {
            if (latest[edges[j].from] > latest[edges[j].to] - edges[j].duration) {
                latest[edges[j].from] = latest[edges[j].to] - edges[j].duration;
            }
        }
    }
}

// 深度优先搜索找出所有关键路径
void dfs(int node) {
    stack[top++] = node; // 将节点压入栈中
    visited[node] = 1; // 标记节点为已访问
    if (node == N - 1) { // 如果到达终点
        // 输出当前路径
        for (int i = 0; i < top; ++i) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    } else {
        // 遍历所有出边
        for (int i = 0; i < M; ++i) {
            if (edges[i].from == node) {
                int nextNode = edges[i].to;
                // 如果下一个节点的最早时间等于当前节点的最早时间加上活动持续时间
                if (earliest[nextNode] == earliest[node] + edges[i].duration && !visited[nextNode]) {
                    dfs(nextNode);
                }
            }
        }
    }
    // 回溯
    top--;
    visited[node] = 0;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].duration);
        indegree[edges[i].to]++;
    }

    calculateEarliest();
    calculateLatest();

    memset(visited, 0, sizeof(visited));
    top = 0;
    dfs(0); // 从节点0开始深度优先搜索

    return 0;
}
/*首先，我们需要读取输入来构建AOE网络。这通常涉及创建一个边数组来存储所有的活动（箭头），包括它们的起始节点、结束节点和持续时间。
计算最早开始时间（earliest）：

为了找到关键路径，我们需要知道每个事件（节点）的最早开始时间。这可以通过从起始节点开始，按拓扑顺序计算每个节点可达的最长路径来完成。对于网络中的每个节点，我们检查所有进入该节点的边，更新该节点的最早开始时间为：“它的前驱节点的最早开始时间 + 前驱节点到该节点的活动持续时间”的最大值。
计算最晚开始时间（latest）：

同样，我们还需要计算每个事件的最晚开始时间，即在不推迟整个项目的前提下，每个事件可以最晚开始的时间。这通常是通过反向遍历网络来完成的，从结束节点开始，向起始节点方向进行。对于网络中的每个节点，我们检查所有从该节点出发的边，更新该节点的最晚开始时间为：“它的后继节点的最晚开始时间 - 该节点到后继节点的活动持续时间”的最小值。
确定关键活动：

关键活动是指那些在整个项目中没有时间延迟的活动，即它们的最早开始时间等于最晚开始时间。我们可以通过比较每个活动的最早开始时间和最晚开始时间来确定。
深度优先搜索（DFS）找出所有关键路径：

有了关键活动的信息后，我们需要找到所有的关键路径。关键路径是网络中从起始节点到结束节点的路径，路径上的所有活动都是关键活动。我们可以通过深度优先搜索来实现这一点，只选择那些时间余量为零的活动来继续搜索。如果一个节点有多个出边是关键活动，则需要分别探索这些边。
输出关键路径：

当DFS到达结束节点时，我们就找到了一条关键路径。输出这条路径，然后回溯到上一个节点，继续搜索其他可能的关键路径，直到所有的关键路径都被找到并输出。*/

