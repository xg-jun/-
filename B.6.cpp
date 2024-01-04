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
int stack[MAXN], top; // ���ڱ��浱ǰ·����ջ
int visited[MAXN]; // ��ǽڵ��Ƿ񱻷��ʹ�

// �������翪ʼʱ��
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

// ��������ʼʱ��
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

// ������������ҳ����йؼ�·��
void dfs(int node) {
    stack[top++] = node; // ���ڵ�ѹ��ջ��
    visited[node] = 1; // ��ǽڵ�Ϊ�ѷ���
    if (node == N - 1) { // ��������յ�
        // �����ǰ·��
        for (int i = 0; i < top; ++i) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    } else {
        // �������г���
        for (int i = 0; i < M; ++i) {
            if (edges[i].from == node) {
                int nextNode = edges[i].to;
                // �����һ���ڵ������ʱ����ڵ�ǰ�ڵ������ʱ����ϻ����ʱ��
                if (earliest[nextNode] == earliest[node] + edges[i].duration && !visited[nextNode]) {
                    dfs(nextNode);
                }
            }
        }
    }
    // ����
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
    dfs(0); // �ӽڵ�0��ʼ�����������

    return 0;
}
/*���ȣ�������Ҫ��ȡ����������AOE���硣��ͨ���漰����һ�����������洢���еĻ����ͷ�����������ǵ���ʼ�ڵ㡢�����ڵ�ͳ���ʱ�䡣
�������翪ʼʱ�䣨earliest����

Ϊ���ҵ��ؼ�·����������Ҫ֪��ÿ���¼����ڵ㣩�����翪ʼʱ�䡣�����ͨ������ʼ�ڵ㿪ʼ��������˳�����ÿ���ڵ�ɴ���·������ɡ����������е�ÿ���ڵ㣬���Ǽ�����н���ýڵ�ıߣ����¸ýڵ�����翪ʼʱ��Ϊ��������ǰ���ڵ�����翪ʼʱ�� + ǰ���ڵ㵽�ýڵ�Ļ����ʱ�䡱�����ֵ��
��������ʼʱ�䣨latest����

ͬ�������ǻ���Ҫ����ÿ���¼�������ʼʱ�䣬���ڲ��Ƴ�������Ŀ��ǰ���£�ÿ���¼���������ʼ��ʱ�䡣��ͨ����ͨ�����������������ɵģ��ӽ����ڵ㿪ʼ������ʼ�ڵ㷽����С����������е�ÿ���ڵ㣬���Ǽ�����дӸýڵ�����ıߣ����¸ýڵ������ʼʱ��Ϊ�������ĺ�̽ڵ������ʼʱ�� - �ýڵ㵽��̽ڵ�Ļ����ʱ�䡱����Сֵ��
ȷ���ؼ����

�ؼ����ָ��Щ��������Ŀ��û��ʱ���ӳٵĻ�������ǵ����翪ʼʱ���������ʼʱ�䡣���ǿ���ͨ���Ƚ�ÿ��������翪ʼʱ�������ʼʱ����ȷ����
�������������DFS���ҳ����йؼ�·����

���˹ؼ������Ϣ��������Ҫ�ҵ����еĹؼ�·�����ؼ�·���������д���ʼ�ڵ㵽�����ڵ��·����·���ϵ����л���ǹؼ�������ǿ���ͨ���������������ʵ����һ�㣬ֻѡ����Щʱ������Ϊ��Ļ���������������һ���ڵ��ж�������ǹؼ��������Ҫ�ֱ�̽����Щ�ߡ�
����ؼ�·����

��DFS��������ڵ�ʱ�����Ǿ��ҵ���һ���ؼ�·�����������·����Ȼ����ݵ���һ���ڵ㣬���������������ܵĹؼ�·����ֱ�����еĹؼ�·�������ҵ��������*/

