#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Node {
    int data;
    struct Node* next;
};

// 在链表末尾插入新节点
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

// 将链表拆分成奇数位置和偶数位置的链表
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

// 打印链表
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 释放链表内存
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

    // 将链表拆分成奇数位置和偶数位置的链表
    splitList(head, &odd_list, &even_list);

    // 打印结果
    printf("L1: ");
    printList(odd_list);
    printf("L2: ");
    printList(even_list);

    // 释放链表内存
    freeList(head);
    freeList(odd_list);
    freeList(even_list);

    return 0;
}

