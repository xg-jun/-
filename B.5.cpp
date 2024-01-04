#include <stdio.h>
#include <stdlib.h>

// ����������ڵ�ṹ
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ����ջ�ṹ
typedef struct StackNode {
    TreeNode* node;
    struct StackNode* next;
} StackNode;

// ����ջ
StackNode* createStack() {
    return NULL;
}

// �ж�ջ�Ƿ�Ϊ��
int isEmpty(StackNode* stack) {
    return stack == NULL;
}

// ��ջ
void push(StackNode** stack, TreeNode* node) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->node = node;
    newNode->next = *stack;
    *stack = newNode;
}

// ��ջ
TreeNode* pop(StackNode** stack) {
    if (isEmpty(*stack)) {
        return NULL;
    }
    StackNode* top = *stack;
    TreeNode* node = top->node;
    *stack = top->next;
    free(top);
    return node;
}

// �������
void preorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    StackNode* stack = createStack();
    push(&stack, root);
    while (!isEmpty(stack)) {
        TreeNode* node = pop(&stack);
        printf("%d ", node->value);
        if (node->right != NULL) {
            push(&stack, node->right);
        }
        if (node->left != NULL) {
            push(&stack, node->left);
        }
    }
    printf("\n");
}

// �������
void inorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    StackNode* stack = createStack();
    TreeNode* current = root;
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->value);
        current = current->right;
    }
    printf("\n");
}

// �������
void postorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    StackNode* stack1 = createStack();
    StackNode* stack2 = createStack();
    push(&stack1, root);
    while (!isEmpty(stack1)) {
        TreeNode* node = pop(&stack1);
        push(&stack2, node);
        if (node->left != NULL) {
            push(&stack1, node->left);
        }
        if (node->right != NULL) {
            push(&stack1, node->right);
        }
    }
    while (!isEmpty(stack2)) {
        TreeNode* node = pop(&stack2);
        printf("%d ", node->value);
    }
    printf("\n");
}

// �����������ڵ�
TreeNode* createNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// �������빹��������
TreeNode* buildTree(int n) {
    TreeNode** nodes = (TreeNode**)malloc(n * sizeof(TreeNode*));
    for (int i = 0; i < n; i++) {
        nodes[i] = createNode(i + 1);
    }
    for (int i = 0; i < n; i++) {
        int value, leftIndex, rightIndex;
        scanf("%d %d %d", &value, &leftIndex, &rightIndex);
        TreeNode* node = nodes[i];
        if (leftIndex != -1) {
            node->left = nodes[leftIndex - 1];
        }
        if (rightIndex != -1) {
            node->right = nodes[rightIndex - 1];
        }
    }
    TreeNode* root = nodes[0];
    free(nodes);
    return root;
}

int main() {
    int n;
    scanf("%d", &n);
    TreeNode* root = buildTree(n);

    preorderTraversal(root);
    inorderTraversal(root);
    postorderTraversal(root);

    return 0;
}

