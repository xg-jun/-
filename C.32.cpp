#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* newNode(char value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
int search(char arr[], int start, int end, char value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            break;
    }
    return i;
}

TreeNode* buildTree(char* preorder, char* inorder, int inorderStart, int inorderEnd) {
    static int preorderIndex = 0;
    if (inorderStart > inorderEnd) return NULL;
    TreeNode* tNode = newNode(preorder[preorderIndex++]);
    if (inorderStart == inorderEnd) return tNode;
    int inorderIndex = search(inorder, inorderStart, inorderEnd, tNode->val);
    tNode->left = buildTree(preorder, inorder, inorderStart, inorderIndex - 1);
    tNode->right = buildTree(preorder, inorder, inorderIndex + 1, inorderEnd);
    return tNode;
}

void printInorder(TreeNode* node) {
    if (node == NULL) return;
    printInorder(node->left);
    printf("%c ", node->val);
    printInorder(node->right);
}
int main() {
    char preorder1[] = "ABDECF";
    char inorder1[] = "DBEACF";
    int len1 = sizeof(inorder1) / sizeof(inorder1[0]) - 1;
    TreeNode* tree1 = buildTree(preorder1, inorder1, 0, len1 - 1);
    printInorder(tree1);
    printf("\n");

    return 0;
}

