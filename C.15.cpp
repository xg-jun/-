#include <stdio.h>
#include <stdlib.h>

// 定义双向链表节点
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 创建双向链表
Node* createLinkedList(int arr[], int size) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < size; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = arr[i];
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    return head;
}

// 判断链表B是否是链表A的子序列
int isSubsequence(Node* A, Node* B) {
    if (B == NULL) {
        return 1;  // B为空，认为是子序列
    }

    if (A == NULL) {
        return 0;  // A为空，不可能是子序列
    }

    if (A->data == B->data) {
        return isSubsequence(A->next, B->next);  // 当前节点匹配，继续匹配下一个节点
    } else {
        return isSubsequence(A->next, B);  // 当前节点不匹配，继续在A中寻找匹配的起始节点
    }
}

// 释放链表内存
void freeLinkedList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    // 创建链表A和B
    int arrA[] = {1, 2, 3, 4, 5};
    int sizeA = sizeof(arrA) / sizeof(arrA[0]);
    Node* A = createLinkedList(arrA, sizeA);
    int arrB[] = {2, 4};
    int sizeB = sizeof(arrB) / sizeof(arrB[0]);
    Node* B = createLinkedList(arrB, sizeB);

    // 判断B是否是A的子序列
    int result = isSubsequence(A, B);

    // 输出结果
    if (result) {
        printf("是子序列\n");
    } else {
        printf("不是子序列\n");
    }

    // 释放链表内存
    freeLinkedList(A);
    freeLinkedList(B);

    return 0;
}

