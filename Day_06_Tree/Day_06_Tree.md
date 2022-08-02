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
- 查詢 Tree Traversal
    - [Binary Tree: Traversal(尋訪)](http://alrightchiu.github.io/SecondRound/binary-tree-traversalxun-fang.html#in_parent)
    - [Tree Traversal in C](https://www.tutorialspoint.com/data_structures_algorithms/tree_traversal_in_c.htm)
- 複習二元樹中的前序走訪（Preorder Traversal）
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
- 複習二維的動態記憶體配置
    ```c
    #define ROW 2000
    #define COL 150
    #define HEIGHT 800

    int *dynArr;                                            /* 動態記憶體配置 */
    int **dynArr2D;                                         /* 動態記憶體配置 */

    int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
        dynArr = (int *)calloc(HEIGHT, sizeof(int));        /* 動態記憶體配置 */

        dynArr2D = (int **)malloc(sizeof(int *) * ROW);         /* 動態記憶體配置 */
        for (int i=0; i<ROW; i++) {
            dynArr2D[i] = (int *)malloc(sizeof(int) * COL);     /* 動態記憶體配置 */
            memset(dynArr2D[i], -1, COL * sizeof(int));         /* 記憶體區塊設定 -> 用來初始化 */
        }

        *returnColumnSizes = dynArr;  // 要回應一個陣列表示每一層有多少節點
        *returnSize = 1;  // 要指出*returnColumnSizes這個陣列有多長
        return NULL;
    }
    ```

- Level Order Binary Tree Traversal
    - [Level Order Traversal of Binary Tree](https://www.interviewbit.com/blog/level-order-traversal/)
    - [Level Order Binary Tree Traversal](https://www.geeksforgeeks.org/level-order-tree-traversal/)
    - [Inorder Tree Traversal without Recursion](https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/)
    - [Number of Nodes in a Binary Tree With Level N](https://www.baeldung.com/cs/binary-tree-number-of-nodes-level)


- Inorder Tree Traversal
    - [Inorder Tree Traversal without Recursion](https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/)
    - [Inorder Tree Traversal without recursion and without stack!](https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/)
    - [Traversing a n-ary tree without using recurrsion](https://stackoverflow.com/questions/5987867/traversing-a-n-ary-tree-without-using-recurrsion)
    - [Inorder Tree Traversal Without Using Recursion or Stack](https://www.interviewkickstart.com/learn/inorder-tree-traversal-without-stack)



- C語言實現queue
    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

    #define MAX_QUEUE_SIZE 100

    typedef struct {
        int key;
    } element;

    void addq(element);
    element deleteq(void);
    int isEmpty(void);

    element queue[MAX_QUEUE_SIZE];
    int rear = 0;
    int front = 0;

    int main() {
        element item1, item2;
        item1.key = 7;
        item2.key = 9;
        addq(item1);
        addq(item2);
        printf ("deleteq: %d\n", deleteq().key);
        printf ("deleteq: %d\n", deleteq().key);
        return 0;
    }

    void addq(element item) {
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        if (front == rear) {
            // queueFull();
        }
        queue[rear] = item;
    }

    element deleteq(void) {
        element item;
        if (front == rear) {
            // return queueEmpty();
        }
        front = (front + 1) % MAX_QUEUE_SIZE;
        return queue[front];
    }

    int isEmpty(void) {
        if (front == rear) {
            return 1;
        } else {
            return 0;
        }
    }
    ```

    - addq()及deleteq()的變形: addq()改成傳入key不傳struct，deleteq()改成回傳pointer
        ```c
        int main() {
            element item1, item2, *e;
            item1.key = 7;
            item2.key = 9;
            addq(5);
            addq(6);

            e = deleteq();
            printf ("deleteq: %d\n", e->key);
            e = deleteq();
            printf ("deleteq: %d\n", e->key);

            return 0;
        }

        void addq(int val) {
            element item;
            item.key = val;
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            if (front == rear) {
                // queueFull();
            }
            queue[rear] = item;
        }

        element *deleteq(void) {
            // element item;
            if (front == rear) {
                // return queueEmpty();
            }
            front = (front + 1) % MAX_QUEUE_SIZE;
            return queue + front;
        }
        ```

- 2022-07-15 Submissions
    ```c
    #define ROW 800
    #define COL 150
    #define HEIGHT 800

    // int **dynArr2D;
    // int *dynArr;

    #define MAX_QUEUE_SIZE 150

    typedef struct {
        struct TreeNode* key;
        int level;
    } element;

    element *deleteq(void);
    element queue[MAX_QUEUE_SIZE];
    int front;
    int rear;

    int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
        int *dynArr = (int *)calloc(HEIGHT, sizeof(int));

        int **dynArr2D = (int **)malloc(sizeof(int *) * ROW);
        for (int i=0; i<ROW; i++) {
            dynArr2D[i] = (int *)malloc(sizeof(int) * COL);
        }

        *returnSize = run_preorder3(root, dynArr, dynArr2D);
        *returnColumnSizes = dynArr;
        return dynArr2D;
    }

    int run_preorder3(struct TreeNode *ptr, int *array, int **array2D) {
        int node_level = 0;
        // int node_total = 0;
        element *e;

        if (ptr == NULL) return 0;

        addq(ptr, 0);
        while (!isEmpty()) {
            e = deleteq();

            if (node_level <= e->level) {
                node_level = e->level;
            }
            // node_total += 1;

            ptr = e->key;
            if (ptr != NULL) {
                array2D[e->level][++array[e->level] - 1]= ptr->val;

                if ((ptr->left) != NULL) {
                    addq(ptr->left, e->level + 1);
                }

                if ((ptr->right) != NULL) {
                    addq(ptr->right, e->level + 1);
                }
            } else {
                break;
            }
        }
        return node_level + 1;
    }

    void addq(struct TreeNode* ptr, int lv) {
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        queue[rear].key = ptr;
        queue[rear].level = lv;
    }

    element *deleteq(void) {
        front = (front + 1) % MAX_QUEUE_SIZE;
        return (queue + front);
    }

    int isEmpty(void) {
        return (front == rear);
    }
    ```