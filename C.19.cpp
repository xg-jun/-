#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ
struct Node {
    int data;
    struct Node* next;
};

// ������ĩβ�����½ڵ�
void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

// �������ֳ�����λ�ú�ż��λ�õ�����
void splitList(struct Node* head, struct Node** odd_list, struct Node** even_list) {
    struct Node* odd = NULL;
    struct Node* even = NULL;
    struct Node* current = head;
    int position = 1;
    while (current != NULL) {
        if (position % 2 == 1) {
            if (odd == NULL) {
                odd = current;
                *odd_list = odd;
            } else {
                odd->next = current;
                odd = odd->next;
            }
        } else {
            if (even == NULL) {
                even = current;
                *even_list = even;
            } else {
                even->next = current;
                even = even->next;
            }
        }
        current = current->next;
        position++;
    }
    if (odd != NULL) {
        odd->next = NULL;
    }
    if (even != NULL) {
        even->next = NULL;
    }
}

// ��ӡ����
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// �ͷ������ڴ�
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    struct Node* odd_list = NULL;
    struct Node* even_list = NULL;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    append(&head, 6);
    append(&head, 7);
    append(&head, 8);
    append(&head, 9);
    append(&head, 10);

    // �������ֳ�����λ�ú�ż��λ�õ�����
    splitList(head, &odd_list, &even_list);

    // ��ӡ���
    printf("L1: ");
    printList(odd_list);
    printf("L2: ");
    printList(even_list);

    // �ͷ������ڴ�
    freeList(head);
    freeList(odd_list);
    freeList(even_list);

    return 0;
}

