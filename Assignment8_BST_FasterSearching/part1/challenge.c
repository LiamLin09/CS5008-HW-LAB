// CS5008 Assignment 8
// Author: Nianlong Lin
// Date: 10/31/2023

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int sum = 0;

void reverseInorder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    reverseInorder(root->right);

    root->val += sum;
    sum = root->val;

    reverseInorder(root->left);
}

struct TreeNode* convertBST(struct TreeNode* root) {
    sum = 0;
    reverseInorder(root);
    return root;
}

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* insertLevelOrder(int arr[], struct TreeNode* root, int i, int n) {
    if (i < n) {
        struct TreeNode* temp = NULL;
        if (arr[i] != -1) {
            temp = createNode(arr[i]);
        }
        root = temp;
        if (root != NULL) {
            root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);
            root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
        }
    }
    return root;
}

void printLevelOrder(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d", root->val);
        if (root->left != NULL || root->right != NULL) {
            printf(",");
        }
        printLevelOrder(root->left);
        if (root->left != NULL && root->right == NULL) {
            printf("null,");
        }
        if (root->right != NULL) {
            printf(",");
        }
        printLevelOrder(root->right);
        if (root->right != NULL && root->left == NULL) {
            printf(",null");
        }
    }
}

int main() {
    int arr[] = {1, 0, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
    struct TreeNode* root = insertLevelOrder(arr, root, 0, n);
    root = convertBST(root);
    printLevelOrder(root);
    return 0;
}
