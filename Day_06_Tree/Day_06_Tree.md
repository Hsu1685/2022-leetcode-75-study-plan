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
- 查詢Level Order Binary Tree Traversal
    - [Level Order Binary Tree Traversal](https://www.geeksforgeeks.org/level-order-tree-traversal/)
    - [Inorder Tree Traversal without Recursion](https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/)
    - [Inorder Tree Traversal without Recursion in C](https://prepinsta.com/data-structures/inorder-tree-traversal-without-recursion/)
    - [Level Order Traversal of Binary Tree](https://www.interviewbit.com/blog/level-order-traversal/)
    ```c
    void print_preorder(node *ptr) {
        if (ptr != NULL) {
            printf("[%2d]\n", ptr->data);  // 先印自己
            print_preorder(ptr->left);  // 再印左子節點
            print_preorder(ptr->right);  // 最後印右子節點
        }
    }
    ```

- 需要複習queue
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
```

- queue測試檔案
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int key;
} element;

void addq(int);
element *deleteq(void);

element queue[MAX_QUEUE_SIZE];
int rear = 0;
int front = 0;

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

- 2022-07-13寫到一半
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define ROW 2000
#define COL 2000

int **dynArr2D;
int *dynArr;
int dynArr_row = 0;
int dynArr_col;
int counter = 0;

int level_counter = 0;
int temp_array_counter = 0;
int temp_array[2000] = {0};

// int **ptr2;

// ptr2 = (int **)malloc(sizeof(int *) * ROW);

// for (int i=0; i<ROW; i++) {
//     ptr2[i] = (int *)malloc(sizeof(int) * COL);
// }

#define MAX_QUEUE_SIZE 100

typedef struct {
    struct TreeNode* key;
    int level;
    int position;
} element;

element *deleteq(void);

element queue[MAX_QUEUE_SIZE];
int rear = 0;
int front = 0;

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    dynArr2D = (int **)malloc(sizeof(int *) * ROW);
    for (int i=0; i<ROW; i++) {
        dynArr2D[i] = (int *)malloc(sizeof(int) * COL);
    }

    dynArr = (int *)malloc(sizeof(int) * ROW);

    // run_preorder2(root, 0);
    // output_array();

    dynArr[0] = 1;
    dynArr[1] = 2;
    dynArr[2] = 2;

    // dynArr2D[0][0] = level_counter;

    // int a = run_preorder3(root);

    *returnSize = run_preorder3(root);
    *returnColumnSizes = dynArr;
    return dynArr2D;
}

void run_preorder(struct TreeNode *ptr) {
    if (ptr != NULL) {
        // printf("[%2d]\n", ptr->data);  // 先印自己
        // append_array(ptr->val);
        run_preorder(ptr->left);  // 再印左子節點
        run_preorder(ptr->right);  // 最後印右子節點
    }
}

// int run_preorder2(struct TreeNode *ptr, int input_level) {
void run_preorder2(struct TreeNode *ptr, int input_level) {
    // int level = 0;
    int next_level;

    if (ptr != NULL) {
        level_counter++;
        // append_array(ptr->val, input_level);
        // append_to_array(ptr->val, input_level);
        next_level = level_counter++;
        run_preorder2(ptr->left, next_level);
        run_preorder2(ptr->right, next_level);
    }
    // return level;
}

int run_preorder3(struct TreeNode *ptr) {
    int tree_level = 0;
    int tree_total = 0;
    element *e;

    if (ptr == NULL) return 0;

    addq(ptr, 0, 0);
    while (1) {
        e = deleteq();

        if (tree_level <= e->level) {
            tree_level = e->level;
        }
        tree_total += 1;

        ptr = e->key;
        if (ptr != NULL) {
            append_to_array(ptr->val, e->level, e->position);
            if ((ptr->left) != NULL) addq(ptr->left, e->level + 1, 0);
            if ((ptr->right) != NULL) addq(ptr->right, e->level + 1, 1);
        } else {
            break;
        }
    }
    return tree_level;
}

void append_to_array(int val, int row, int col) {
    // dynArr[row] += 1;
    // temp_array[temp_array_counter] = val;
    // temp_array_counter++;
    dynArr2D[row][col] = val;
}

// void output_array(void) {
//     int i, j;
//     int k = 0;
//     for (i=0; i<level_counter; i++) {
//         for (j=0; j<dynArr[i]; j++) {
//             dynArr2D[i][j] = temp_array[k];
//             k++;
//         }
//     }
// }

// void addq(element item) {
void addq(struct TreeNode* ptr, int lv, int pos) {
    element item;
    item.key = ptr;
    item.level = lv;
    item.position = pos;

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