#include <stdio.h>
#include <stdlib.h>

// ����ѭ������Ľڵ�ṹ
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// ����ѭ������
Node* createCircularLinkedList(int n) {
    Node* head = NULL;
    Node* prev = NULL;
    
    // ������һ���ڵ�
    head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    head->next = NULL;
    prev = head;
    
    // ����ʣ��ڵ�
    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = i;
        newNode->next = NULL;
        prev->next = newNode;
        prev = newNode;
    }
    
    // �����һ���ڵ��nextָ��ͷ�ڵ㣬�γ�ѭ������
    prev->next = head;
    
    return head;
}

// ���Լɪ������
void solveJosephusProblem(int n, int m) {
    Node* head = createCircularLinkedList(n);
    Node* current = head;
    
    // �ҵ���һ������Ϊ1�Ľڵ�
    while (current->data != 1) {
        current = current->next;
    }
    
    // ��ʼ��̭����
    while (current->next != current) {
        // �ҵ���m���ڵ��ǰһ���ڵ�
        for (int i = 1; i < m - 1; i++) {
            current = current->next;
        }
        
        // ��̭��m���ڵ�
        Node* eliminatedNode = current->next;
        printf("��̭���ˣ�%d\n", eliminatedNode->data);
        current->next = eliminatedNode->next;
        free(eliminatedNode);
        
        // ������һ�ֱ���
        current = current->next;
    }
    
    // ������ʣ�µ���
    printf("���ʣ�µ��ˣ�%d\n", current->data);
    
    // �ͷ��ڴ�
    free(current);
}

int main() {
    int n = 10;  // ������
    int m = 3;   // �������
    
    solveJosephusProblem(n, m);
    
    return 0;
}

