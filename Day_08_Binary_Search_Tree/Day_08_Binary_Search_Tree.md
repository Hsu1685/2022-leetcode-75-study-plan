# Day 7 Day 8 Binary Search Tree

## 98. Validate Binary Search Tree

### 題目
>Given the root of a binary tree, determine if it is a valid binary search tree (BST).</br>
>A valid BST is defined as follows:</br>
>   - The left subtree of a node contains only nodes with keys less than the node's key.
>   - The right subtree of a node contains only nodes with keys greater than the node's key.
>   - Both the left and right subtrees must also be binary search trees.

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


bool isValidBST(struct TreeNode* root){

}
```
>Constraints:
>- The number of nodes in the tree is in the range [1, $10^4$].
>- -$2^{31}$ <= Node.val <= $2^{31}$ - 1

### 過程
- 複習二元樹中的前序走訪（Inorder Traversal）
    - 這會產生一個從小到大的順序
    ```c
    void print_preorder(node *ptr) {
        if (ptr != NULL) {
            print_preorder(ptr->left);  // 先印左子節點
            printf("[%2d]\n", ptr->data);  // 再印自己
            print_preorder(ptr->right);  // 最後印右子節點
        }
    }
    ```