#include <stdio.h>
#include <stdlib.h>

// ����˫������ڵ�
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// ����˫������
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

// �ж�����B�Ƿ�������A��������
int isSubsequence(Node* A, Node* B) {
    if (B == NULL) {
        return 1;  // BΪ�գ���Ϊ��������
    }

    if (A == NULL) {
        return 0;  // AΪ�գ���������������
    }

    if (A->data == B->data) {
        return isSubsequence(A->next, B->next);  // ��ǰ�ڵ�ƥ�䣬����ƥ����һ���ڵ�
    } else {
        return isSubsequence(A->next, B);  // ��ǰ�ڵ㲻ƥ�䣬������A��Ѱ��ƥ�����ʼ�ڵ�
    }
}

// �ͷ������ڴ�
void freeLinkedList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    // ��������A��B
    int arrA[] = {1, 2, 3, 4, 5};
    int sizeA = sizeof(arrA) / sizeof(arrA[0]);
    Node* A = createLinkedList(arrA, sizeA);
    int arrB[] = {2, 4};
    int sizeB = sizeof(arrB) / sizeof(arrB[0]);
    Node* B = createLinkedList(arrB, sizeB);

    // �ж�B�Ƿ���A��������
    int result = isSubsequence(A, B);

    // ������
    if (result) {
        printf("��������\n");
    } else {
        printf("����������\n");
    }

    // �ͷ������ڴ�
    freeLinkedList(A);
    freeLinkedList(B);

    return 0;
}

