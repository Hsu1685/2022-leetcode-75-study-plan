# Day 8 Binary Search Tree

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
- 想法是使用中序走訪（Inorder Traversal）會產生一個從小到大的順序，最後檢查這個順序是否錯誤
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
       return 1;
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


---
## 235. Lowest Common Ancestor of a Binary Search Tree

### 題目
> Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.</br>
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”</br>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {

}
```
>Constraints:
>- The number of nodes in the tree is in the range [2, $10^5$].
>- $-10^*5*$ <= Node.val <= $10^9$
>- ll Node.val are **unique**.
>- p != q
>- p and q will exist in the BST.

### 過程
#### 查詢資訊
- [Lowest common ancestor From Wikipedi](https://en.wikipedia.org/wiki/Lowest_common_ancestor)
- [Binary Tree](https://web.ntnu.edu.tw/~algo/BinaryTree.html)
- [在二叉樹中查找給定節點的祖先](https://www.techiedelight.com/zh-tw/find-ancestors-of-given-node-binary-tree/)
- [Print ancestors of a given binary tree node without recursion](https://www.geeksforgeeks.org/print-ancestors-of-a-given-binary-tree-node-without-recursion/)
- [Tree_traversal#Implementations](https://en.wikipedia.org/wiki/Tree_traversal#Implementations)
- [Print Ancestors of a given node in Binary Tree in C++](https://www.tutorialspoint.com/print-ancestors-of-a-given-node-in-binary-tree-in-cplusplus)
```c
bool AncestorsNodes(struct TreeNode *root, int target) {
    if (root == NULL)
        return false;
    if (root->val == target) {
        printf("%d ", root->val);
        counter++;
        return true;
    }
    if ( AncestorsNodes(root->left, target) || AncestorsNodes(root->right, target) ) {
        printf("%d ", root->val);
        counter++;
        return true;
    }
    return false;
}
```

#### 想法
- 分別列出p和q的所有父階，再去找出最低的重複項目
    ```c
    #define COL 150

    int counter;

    struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
        int index_p, index_q;
        int break_flag = 0;
        struct TreeNode* ret;
        struct TreeNode* array_p[COL] = {NULL};
        struct TreeNode* array_q[COL] = {NULL};

        counter = 0;
        AncestorsNodes(root, p->val, array_p);
        index_p = counter;

        counter = 0;
        AncestorsNodes(root, q->val, array_q);
        index_q = counter;

        for (int i=0; i<index_p; i++) {
            for (int j=0; j<index_q; j++) {
                if (array_p[i]->val == array_q[j]->val) {
                    ret = array_p[i];
                    break_flag = 1;
                    break;
                }
            }
            if (break_flag == 1) break;
        }
        return ret;
    }

    int AncestorsNodes(struct TreeNode *root, int target, struct TreeNode **ptr_array) {
        if (root == NULL)
            return 0;
        if (root->val == target) {
            // printf("%d ", root->val);
            ptr_array[counter] = root;
            counter++;
            return 1;
        }
        if (AncestorsNodes(root->left, target, ptr_array) || AncestorsNodes(root->right, target, ptr_array)) {
            // printf("%d ", root->val);
            ptr_array[counter] = root;
            counter++;
            return 1;
        }
        return 0;
    }

    ```

#### 衍伸內容
- [Range minimum query From Wikipedia](https://en.wikipedia.org/wiki/Range_minimum_query)
- [RANGE MINIMUM QUERY AND LOWEST COMMON ANCESTOR](https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor)
- [範圍最小值問題（Range Minimum Query，RMQ）](https://codertw.com/%E7%A8%8B%E5%BC%8F%E8%AA%9E%E8%A8%80/561565/)
- [範圍最小值問題 (Range Minimum Query,RMQ)](https://code-question.com/developer-blog/range-minimum-query-rmq)