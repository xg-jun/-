#include <stdio.h>
#include <stdlib.h>

// 二叉树节点的结构定义
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// 创建一个新的二叉树节点
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 判断二叉树是否为满二叉树
int isFullBinaryTree(struct Node* root) {
    if (root == NULL)
        return 1;

    if (root->left == NULL && root->right == NULL)
        return 1;

    if (root->left != NULL && root->right != NULL)
        return (isFullBinaryTree(root->left) && isFullBinaryTree(root->right));

    return 0;
}

// 判断二叉树是否为完全二叉树
int isCompleteBinaryTree(struct Node* root, int index, int nodeCount) {
    if (root == NULL)
        return 1;

    if (index >= nodeCount)
        return 0;

    return (isCompleteBinaryTree(root->left, 2 * index + 1, nodeCount) &&
            isCompleteBinaryTree(root->right, 2 * index + 2, nodeCount));
}

// 计算二叉树中节点的数量
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    // 创建一棵完全二叉树
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
        printf("是满二叉树，");
    else
        printf("不是满二叉树，");

    if (isComplete)
        printf("是完全二叉树。\n");
    else
        printf("不是完全二叉树。\n");

    // 释放二叉树节点的内存
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

