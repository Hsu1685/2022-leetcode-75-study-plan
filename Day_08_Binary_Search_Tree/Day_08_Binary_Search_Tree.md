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
- 想法是使用前序走訪（Inorder Traversal）會產生一個從小到大的順序，最後檢查這個順序是否錯誤
- 複習二元樹中的中序走訪（Inorder Traversal）
    ```c
    void print_preorder(node *ptr) {
        if (ptr != NULL) {
            print_preorder(ptr->left);  // 先印左子節點
            printf("[%2d]\n", ptr->data);  // 再印自己
            print_preorder(ptr->right);  // 最後印右子節點
        }
    }
    ```
- 將走訪結果丟入queue中，再拿出來檢查
```c
#define MAX_QUEUE_SIZE 10000

int *queue, *front, *rear, *counter;

bool isValidBST(struct TreeNode* root){
    int dq1 = 0, dq2 = 0;

    queue = (int*)calloc(MAX_QUEUE_SIZE, sizeof(int));
    front = (int*)malloc(sizeof(int));
    rear = (int*)malloc(sizeof(int));
    counter = (int*)malloc(sizeof(int));

    *front = *rear = *counter = 0;

    run_inorder(root);

    if (*counter == 1) {
       return true;
    }

    dq1 = deleteq();
    for (int i=0; i<(*counter)-1; i++) {
        dq2 = deleteq();
        if (dq2 > dq1) {
            dq1 = dq2;
        } else {
            return 0;
        }
    }
    return 1;
}

void run_inorder(struct TreeNode* ptr) {
    if (ptr != NULL) {
        run_inorder(ptr->left);  // 先是左子節點
        addq(ptr->val);  // 再來是自身
        (*counter)++;
        run_inorder(ptr->right);  // 最後是右子節點
    }
}

void addq(int val) {
    *rear = (*rear + 1) % MAX_QUEUE_SIZE;
    // if (front == rear) {
    //     queueFull();
    // }
    queue[*rear] = val;
}

int deleteq(void) {
    // if (front == rear) {
    //     return queueEmpty();
    // }
    *front = (*front + 1) % MAX_QUEUE_SIZE;
    return queue[*front];
}
```