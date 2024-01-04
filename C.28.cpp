#include <stdio.h>
#include <stdlib.h>

// �������ڵ�Ľṹ����
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// ����һ���µĶ������ڵ�
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// �ж϶������Ƿ�Ϊ��������
int isFullBinaryTree(struct Node* root) {
    if (root == NULL)
        return 1;

    if (root->left == NULL && root->right == NULL)
        return 1;

    if (root->left != NULL && root->right != NULL)
        return (isFullBinaryTree(root->left) && isFullBinaryTree(root->right));

    return 0;
}

// �ж϶������Ƿ�Ϊ��ȫ������
int isCompleteBinaryTree(struct Node* root, int index, int nodeCount) {
    if (root == NULL)
        return 1;

    if (index >= nodeCount)
        return 0;

    return (isCompleteBinaryTree(root->left, 2 * index + 1, nodeCount) &&
            isCompleteBinaryTree(root->right, 2 * index + 2, nodeCount));
}

// ����������нڵ������
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    // ����һ����ȫ������
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);

    int nodeCount = countNodes(root);
    int isFull = isFullBinaryTree(root);
    int isComplete = isCompleteBinaryTree(root, 0, nodeCount);

    if (isFull)
        printf("������������");
    else
        printf("��������������");

    if (isComplete)
        printf("����ȫ��������\n");
    else
        printf("������ȫ��������\n");

    // �ͷŶ������ڵ���ڴ�
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

