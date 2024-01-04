#include <stdio.h>
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *stack) {
    stack->top = -1;
}

// 入栈
void push(Stack *stack, int value) {
    if (stack->top == MAX_SIZE - 1) {
        printf("入栈失败\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// 出栈
int pop(Stack *stack) {
    if (stack->top == -1) {
        printf("出栈失败\n");
        return -1;
    }
    return stack->data[stack->top--];
}

void tentotwo(int data) {
    Stack stack;
    initStack(&stack);

    while (data > 0) {
        int remainder = data % 2;
        push(&stack, remainder);
        data /= 2;
    }

    printf("二进制: ");
    while (stack.top != -1) {
        printf("%d", pop(&stack));
    }
    printf("\n");
}
void tentoeight(int data) {
    Stack stack;
    initStack(&stack);

    while (data > 0) {
        int remainder = data % 8;
        push(&stack, remainder);
        data /= 8;
    }

    printf("八进制: ");
    while (stack.top != -1) {
        printf("%d", pop(&stack));
    }
    printf("\n");
}
void tentohex(int data) {
    Stack stack;
    initStack(&stack);

    while (data > 0) {
        int remainder = data % 16;
        push(&stack, remainder);
        data /= 16;
    }

    printf("十六进制: ");
    while (stack.top != -1) {
        int value = pop(&stack);
        if (value < 10) {
            printf("%d", value);
        } else {
            printf("%c", 'A' + (value - 10));
        }
    }
    printf("\n");
}

int main() {
    int data;
    printf("请输入一个十进制数: ");
    scanf("%d", &data);
    tentotwo(data);
    tentoeight(data);
    tentohex(data);
    return 0;
}

