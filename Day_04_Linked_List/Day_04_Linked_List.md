# Day 4 Linked List

## 876. Middle of the Linked List

### 題目
>Given the head of a singly linked list, return the middle node of the linked list.</br>
If there are two middle nodes, return the second middle node.</br>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* middleNode(struct ListNode* head){

}
```
>Constraints:
>- The number of nodes in the list is in the range [1, 100].
>- 1 <= Node.val <= 100

### 過程
- 最初想法就是遍歷所有節點計算數量
    - 若是奇數則Middle numble index = n / 2
    - 若是偶數則index = n / 2
    ```c
    struct ListNode* middleNode(struct ListNode* head){
        struct ListNode* ptr_array[100] = {NULL};
        struct ListNode* ptr;
        int index = 0;
        
        ptr = head;
        
        while (ptr != NULL) {
            ptr_array[index] = ptr;
            index++;
            ptr = ptr->next;
        }

        return ptr_array[index / 2];
    }
    ```


---
## 142. Linked List Cycle II

### 題目
> Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.</br>
There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.</br>
Do not modify the linked list.</br>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    
}
```
>Constraints:
>- The number of the nodes in the list is in the range [0, $10^4$].
>- $-10^5$ <= Node.val <= $10^5$
>- pos is -1 or a valid index in the linked-list.

### 過程
- 一開始想到的方法是用[10000]的陣列來儲存所有走過的節點指標，出現有重複的指標就表示list存在有閉環
```c
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *ptr_array[10000] = {0};
    struct ListNode *ptr;
    int index = 0;
    int flag = 0;
    
    if (head == NULL) {
        return NULL;
    }
        
    ptr = head;
    
    while (ptr->next != NULL) {
        ptr_array[index] = ptr;
        if (isInArray(ptr_array, ptr->next, index)) {
            return  ptr->next;
        }
        index++;
        ptr = ptr->next;
    }
    return NULL;
}

int isInArray(struct ListNode** array, struct ListNode *node, int num) {
    int i;
    
    for (i=0; i<num; i++) {
        if (array[i] == node) {
            return 1;
        }
    }
    return 0;
}

```