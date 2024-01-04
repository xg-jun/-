#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// �����ڵ�
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// ����ڵ㵽����β��
void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        (*head)->next = *head;
        (*head)->prev = *head;
    } else {
        Node* lastNode = (*head)->prev;
        lastNode->next = newNode;
        newNode->prev = lastNode;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

// ��ӡ����
void printList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

// ���������ϵĽ���
Node* intersection(Node* setA, Node* setB) {
    Node* result = NULL;
    Node* currentA = setA;
    do {
        Node* currentB = setB;
        do {
            if (currentA->data == currentB->data) {
                insertNode(&result, currentA->data);
                break;
            }
            currentB = currentB->next;
        } while (currentB != setB);
        currentA = currentA->next;
    } while (currentA != setA);
    return result;
}

// ���������ϵĲ���
Node* unionSet(Node* setA, Node* setB) {
    Node* result = NULL;
    Node* currentA = setA;
    do {
        insertNode(&result, currentA->data);
        currentA = currentA->next;
    } while (currentA != setA);
    Node* currentB = setB;
    do {
        Node* currentResult = result;
        int found = 0;
        do {
            if (currentB->data == currentResult->data) {
                found = 1;
                break;
            }
            currentResult = currentResult->next;
        } while (currentResult != result);
        if (!found) {
            insertNode(&result, currentB->data);
        }
        currentB = currentB->next;
    } while (currentB != setB);
    return result;
}

// ��������
void destroyList(Node** head) {
    if (*head == NULL) {
        return;
    }
    Node* current = *head;
    do {
        Node* temp = current;
        current = current->next;
        free(temp);
    } while (current != *head);
    *head = NULL;
}

int main() {
    // ��������1
    Node* setA = NULL;
    Node* setB = NULL;

    insertNode(&setA, 1);
    insertNode(&setA, 2);
    insertNode(&setA, 3);
    insertNode(&setA, 4);
    insertNode(&setA, 5);

    insertNode(&setB, 3);
    insertNode(&setB, 4);
    insertNode(&setB, 5);
    insertNode(&setB, 6);
    insertNode(&setB, 7);

    printf("����A��");
    printList(setA);
    printf("����B��");
    printList(setB);

    Node* intersectionResult = intersection(setA, setB);
    printf("������");
    printList(intersectionResult);

    Node* unionResult = unionSet(setA, setB);
    printf("������");
    printList(unionResult);

    destroyList(&setA);
    destroyList(&setB);
    destroyList(&intersectionResult);
    destroyList(&unionResult);

    // ��������2
    setA = NULL;
    setB = NULL;

    insertNode(&setA, 8);
    insertNode(&setA, 9);
    insertNode(&setA, 10);
    insertNode(&setA, 11);
    insertNode(&setA, 12);

    insertNode(&setB, 10);
    insertNode(&setB, 11);
    insertNode(&setB, 12);
    insertNode(&setB, 13);
    insertNode(&setB, 14);

    printf("����A��");
    printList(setA);
    printf("����B��");
    printList(setB);

    intersectionResult = intersection(setA, setB);
    printf("������");
    printList(intersectionResult);

    unionResult = unionSet(setA, setB);
    printf("������");
    printList(unionResult);

    destroyList(&setA);
    destroyList(&setB);
    destroyList(&intersectionResult);
    destroyList(&unionResult);

    return 0;
}

