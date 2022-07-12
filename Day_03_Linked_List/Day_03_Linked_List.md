# Day 3 Linked List

## 21. Merge Two Sorted Lists

### 題目
>You are given the heads of two sorted linked lists list1 and list2.</br>
Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.</br>
Return the head of the merged linked list.</br>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){

}
```
>Constraints:
>- The number of nodes in both lists is in the range [0, 50].
>- -100 <= Node.val <= 100
>- Both list1 and list2 are sorted in non-decreasing order.

### 過程
- 建立輸出list的指標及記憶體位置
    ```c
    struct ListNode *head;
    head = (struct ListNode*)malloc(sizeof(struct ListNode));
    ```
- 向list新增節點
    ```c
    void appendList(struct ListNode* list1, struct ListNode* list2) {
        list1->next = list2;
    }
    ```
- 一開始想法先比較2個list的第一個節點的元素，將較小的數值設定為max_value
    - 設定指標ptr_next指向下一個要查詢的節點
    - 設定指標ptr_last指向上一個要查詢過的節點
    ```c
    int max_value = 0;
    ListNode* ptr_next;
    ListNode* ptr_last;

    if (list1->val <= list2->val) {
        max_value = list1->val;
        // 加入list1第一個元素
        ptr_next = list2;
        ptr_last = list1;
    } else {        
        max_value = list2->val;
        // 加入list2第一個元素
        ptr_next = list1;
        ptr_last = list2;
    }
    ```
- 後來想法是將2個list最開頭節點元素做比較，較小的取出至新list，並將指標指向下一個節點，再繼續比較2個list最開頭的節點元素，再將較小的取出，接著循環下去
    - 最後加上對空node的判斷
    ```c
    struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
        struct ListNode *head, *head_temp;
        struct ListNode* list1_new_head = list1;
        struct ListNode* list2_new_head = list2;
        
        head = (struct ListNode*)malloc(sizeof(struct ListNode));    
        head->next = NULL;
        head_temp = head;
        
        if ((list1 == NULL) && (list2 == NULL)) {
            return NULL;
        } else if (list1 == NULL) {
            head->val = list2->val;
            list2_new_head = list2_new_head->next;
        } else if (list2 == NULL) {
            head->val = list1->val;
            list1_new_head = list1_new_head->next;
        } else if (list1_new_head->val <= list2_new_head->val) {
            // 加入list1第一個元素至 head
            head->val = list1_new_head->val;
            list1_new_head = list1_new_head->next;
        } else {        
            // 加入list2第一個元素
            head->val = list2_new_head->val;
            list2_new_head = list2_new_head->next;
        }
        
        while ((list1_new_head != NULL) || (list2_new_head != NULL)) {
            if (list1_new_head == NULL) {
                // 加入list2第一個元素
                appendList(head_temp, list2_new_head);
                head_temp = head_temp->next;
                list2_new_head = list2_new_head->next;
                continue;
            } else if (list2_new_head == NULL) {
                // 加入list1第一個元素至 head
                appendList(head_temp, list1_new_head);
                head_temp = head_temp->next;
                list1_new_head = list1_new_head->next;
                continue;
            } else if (list1_new_head->val <= list2_new_head->val) {
                // 加入list1第一個元素至 head
                appendList(head_temp, list1_new_head);
                head_temp = head_temp->next;
                list1_new_head = list1_new_head->next;
            } else {        
                // 加入list2第一個元素
                appendList(head_temp, list2_new_head);
                head_temp = head_temp->next;
                list2_new_head = list2_new_head->next;
            }
        }
        return head;
    }

    void appendList(struct ListNode* list1, struct ListNode* list2) {
        list1->next = list2;
    }
    ```


---
## 206. Reverse Linked List

### 題目
> Given the head of a singly linked list, reverse the list, and return the reversed list.</br>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseList(struct ListNode* head){

}
```
>Constraints:
>- The number of nodes in the list is the range [0, 5000].
>- -5000 <= Node.val <= 5000
 
### 過程
- 向list的最後新增節點
    ```c
    node *new_node;
    new_node = getnode();  // (node *) malloc(sizeof(node));
    new_node -> next = NULL;
    ptr->next = new_node  // 指向新節點
    ```
- 向list節點的前面新增節點
    ```c
    head = new_node;
    new_node->next = ptr;
    ```
- 最後想法將第一個節點當作新head，之後的每一個節點都加在list最前面
    - 最後檢查是否為空node
    ```c
    struct ListNode* reverseList(struct ListNode* head){
        struct ListNode *output_head, *output_head_temp, *ptr, *ptr_next_temp;
        output_head = (struct ListNode*)malloc(sizeof(struct ListNode));
        output_head->next = NULL;
        
        if (head == NULL) {
            return NULL;
        }
        
        ptr = head;    
        output_head->val = ptr->val;
        ptr = ptr->next;
        
        while (ptr != NULL) {
            output_head_temp = output_head;
            ptr_next_temp = ptr->next;
            
            output_head = ptr;
            output_head->next = output_head_temp;        
            ptr = ptr_next_temp;
        }
        return output_head;
    }
    ```