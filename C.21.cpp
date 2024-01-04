#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct {
    double data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, double value) {
    if (isFull(stack)) {
        printf("Stack is full.\n");
        exit(1);
    }
    stack->data[++stack->top] = value;
}

double pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

double peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        exit(1);
    }
    return stack->data[stack->top];
}

int getPriority(char operator1) {
    switch (operator1) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

double performOperation(double operand1, double operand2, char operator1) {
    switch (operator1) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        case '^':
            return pow(operand1, operand2);
        default:
            return 0;
    }
}

double evaluateExpression(char *expression) {
    Stack operandStack;
    Stack operatorStack;
    initStack(&operandStack);
    initStack(&operatorStack);

    int i = 0;
    int isNegative = 0; // ��ǵ�ǰ�����Ƿ�Ϊ����
    while (expression[i] != '\0') {
        if (isdigit(expression[i]) || expression[i] == '.') {
            // ��������
            double operand = strtod(&expression[i], NULL);
            if (isNegative) {
                operand = -operand; // ������Ϊ������������ȡ��
                isNegative = 0; // ���ø������
            }
            push(&operandStack, operand);
            while (isdigit(expression[i]) || expression[i] == '.') {
                i++;
            }
        } else if (expression[i] == '(') {
            // ����������
            push(&operatorStack, '(');
            i++;
        } else if (expression[i] == ')') {
            // ���������ţ�ִ����Ӧ����
            while (!isEmpty(&operatorStack) && peek(&operatorStack) != '(') {
                double operand2 = pop(&operandStack);
                double operand1 = pop(&operandStack);
                char operator1 = pop(&operatorStack);
                double result = performOperation(operand1, operand2, operator1);
                push(&operandStack, result);
            }
            if (!isEmpty(&operatorStack) && peek(&operatorStack) == '(') {
                pop(&operatorStack); // ����������
            }
            i++;
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
            // �����������ִ����Ӧ����
            if (expression[i] == '-' && (i == 0 || expression[i - 1] == '(')) {
                // ����������ţ����Ҹ���ǰ���������Ż���ʽ�Ŀ�ͷ��������һ������Ϊ����
                isNegative = 1;
                i++;
                continue;
            }
            while (!isEmpty(&operatorStack) && getPriority(peek(&operatorStack)) >= getPriority(expression[i])) {
                double operand2 = pop(&operandStack);
                double operand1 = pop(&operandStack);
                char operator1 = pop(&operatorStack);
                double result = performOperation(operand1, operand2, operator1);
                push(&operandStack, result);
            }
            push(&operatorStack, expression[i]);
            i++;
        } else {
            // ���Կո�������Ƿ��ַ�
            i++;
        }
    }

    while (!isEmpty(&operatorStack)) {
        double operand2 = pop(&operandStack);
        double operand1 = pop(&operandStack);
        char operator1 = pop(&operatorStack);
        double result = performOperation(operand1, operand2, operator1);
        push(&operandStack, result);
    }

    return pop(&operandStack);
}

int main() {
    char expression[100];
    printf("��������ʽ��");
    fgets(expression, sizeof(expression), stdin);

    int i = 0;
    while (expression[i] != '\0') {
        if (expression[i] == '\n') {
            expression[i] = '\0';
            break;
        }
        i++;
    }

    double result = evaluateExpression(expression);
    printf("������: %.3f\n", result);

    return 0;
}

