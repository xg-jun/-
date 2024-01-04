#include <stdio.h>
#include <stdlib.h>

// 定义循环链表的节点结构
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建循环链表
Node* createCircularLinkedList(int n) {
    Node* head = NULL;
    Node* prev = NULL;
    
    // 创建第一个节点
    head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    head->next = NULL;
    prev = head;
    
    // 创建剩余节点
    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = i;
        newNode->next = NULL;
        prev->next = newNode;
        prev = newNode;
    }
    
    // 将最后一个节点的next指向头节点，形成循环链表
    prev->next = head;
    
    return head;
}

// 解决约瑟夫环问题
void solveJosephusProblem(int n, int m) {
    Node* head = createCircularLinkedList(n);
    Node* current = head;
    
    // 找到第一个报数为1的节点
    while (current->data != 1) {
        current = current->next;
    }
    
    // 开始淘汰过程
    while (current->next != current) {
        // 找到第m个节点的前一个节点
        for (int i = 1; i < m - 1; i++) {
            current = current->next;
        }
        
        // 淘汰第m个节点
        Node* eliminatedNode = current->next;
        printf("淘汰的人：%d\n", eliminatedNode->data);
        current->next = eliminatedNode->next;
        free(eliminatedNode);
        
        // 继续下一轮报数
        current = current->next;
    }
    
    // 输出最后剩下的人
    printf("最后剩下的人：%d\n", current->data);
    
    // 释放内存
    free(current);
}

int main() {
    int n = 10;  // 总人数
    int m = 3;   // 报数间隔
    
    solveJosephusProblem(n, m);
    
    return 0;
}

