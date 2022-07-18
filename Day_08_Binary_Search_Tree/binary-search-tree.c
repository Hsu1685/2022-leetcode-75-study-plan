#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };
 struct TreeNode* newNode(int);

void run_inorder(struct TreeNode *);
struct TreeNode* newNode(int);

int counter;

int main() {
    struct TreeNode* root;

    // Constructing tree given in the above figure
    root = newNode(6);
    root->left = newNode(2);
    root->right = newNode(8);
    root->left->left = newNode(0);
    root->left->right = newNode(4);
    root->right->left = newNode(7);
    root->right->right = newNode(9);
    root->left->right->left = newNode(3);
    root->left->right->right = newNode(5);

    counter = 0;
    run_inorder(root);
    printf ("counter: %d\n", counter);
    return 0;
}

void run_inorder(struct TreeNode* ptr) {
    if (ptr != NULL) {
        run_inorder(ptr->left);  // 先是左子節點
        printf("[%2d]\n", ptr->val);  // 再來是自身
        counter++;
        run_inorder(ptr->right);  // 最後是右子節點
    }
}

struct TreeNode* newNode(int data) {  // 建立節點
    struct TreeNode* temp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    temp->val = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}