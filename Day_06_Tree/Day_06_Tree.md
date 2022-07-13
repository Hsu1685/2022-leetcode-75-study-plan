# Day 6 Tree

## 589. N-ary Tree Preorder Traversal

### 題目
>Given the root of an n-ary tree, return the preorder traversal of its nodes' values.</br>
Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)</br>

```c
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorder(struct Node* root, int* returnSize) {
    
}
```
>Constraints:
>- The number of nodes in the tree is in the range [0, $10^4$].
>- 0 <= Node.val <= $10^4$
>- The height of the n-ary tree is less than or equal to 1000.

### 過程
- 先複習二元樹中的前序走訪（Preorder Traversal）
    ```c
    void print_preorder(node *ptr) {
        if (ptr != NULL) {
            printf("[%2d]\n", ptr->data);  // 先印自己
            print_preorder(ptr->left);  // 再印左子節點
            print_preorder(ptr->right);  // 最後印右子節點
        }
    }
    ```

- 再來實現多元樹中的前序走訪
    - 要利用題目所提供的節點中的元素numChildren避免訪問到錯誤的位置
        ```c
        void run_preorder3(struct Node* ptr) {
            int num = ptr->numChildren;
            int i;
            
            if (num >= 0) {
                append_array(ptr->val);
                for (i=0; i<num; i++) {  // 避免ptr->children[i]超過範圍
                    run_preorder3(ptr->children[i]);
                }
            }    
        }
        ```
    - 要再利用numChildren判斷是否節點還有子階
        ```c
        void run_preorder4(struct Node* ptr) {
            int num = ptr->numChildren;
            int i;
            if (ptr != NULL) {
                append_array(ptr->val);
                if (num > 0) {  // 等於0就不用再向下訪問了
                    for (i=0; i<num; i++) {
                        run_preorder3(ptr->children[i]);
                    }
                }
            }
        }
        ```
- 最後利用前序走訪列出所有的元素
    ```c
    int* dynArr;
    int dynArr_index;

    int* preorder(struct Node* root, int* returnSize) {
        dynArr = (int *)malloc(10000 * sizeof(int));
        if (root == NULL) {
            *returnSize = 0;
            return NULL;
        }
        
        dynArr_index = 0;
        run_preorder4(root);
        
        *returnSize = dynArr_index;
        return dynArr;
    }

    void run_preorder4(struct Node* ptr) {
        int num = ptr->numChildren;
        int i;
        if (ptr != NULL) {
            append_array(ptr->val);
            if (num > 0) {  // 等於0就不用再向下訪問了
                for (i=0; i<num; i++) {
                    run_preorder3(ptr->children[i]);
                }
            }
        }
    }

    void append_array(int val) {
        dynArr[dynArr_index] = val;
        dynArr_index += 1;
    }
    ```

---
## 102. Binary Tree Level Order Traversal

### 題目
> Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).</br>


```c
int longestPalindrome(char * s){

}
```
>Constraints:
>- The number of nodes in the tree is in the range [0, 2000].
>- -1000 <= Node.val <= 1000

### 過程
- 一樣先複習二元樹中的前序走訪（Preorder Traversal）
    ```c
    void print_preorder(node *ptr) {
        if (ptr != NULL) {
            printf("[%2d]\n", ptr->data);  // 先印自己
            print_preorder(ptr->left);  // 再印左子節點
            print_preorder(ptr->right);  // 最後印右子節點
        }
    }
    ```
- 再來複習二維的動態記憶體配置
```c
#define ROW 2000
#define COL 2000

int **dynArr;                                           /* 動態記憶體配置 */
int *dynArr;                                            /* 動態記憶體配置 */
int dynArr_index;                                       /* 動態記憶體配置 */

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    dynArr = (int **)malloc(sizeof(int *) * ROW);       /* 動態記憶體配置 */
    for (int i=0; i<ROW; i++) {                         /* 動態記憶體配置 */
        dynArr[i] = (int *)malloc(sizeof(int) * COL);   /* 動態記憶體配置 */
    }                                                   /* 動態記憶體配置 */

    dynArr = (int *)malloc(sizeof(int) * ROW);          /* 動態記憶體配置 */

    *returnColumnSizes = dynArr;  // 要回應一個陣列表示每一層有多少節點
    *returnSize = 1;  // 要指出*returnColumnSizes這個陣列有多長
    return NULL;
}
```