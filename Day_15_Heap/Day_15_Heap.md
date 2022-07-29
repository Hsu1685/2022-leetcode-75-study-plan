# Day 15 Heap

## 1046. Last Stone Weight

### 題目
> You are given an array of integers stones where stones[i] is the weight of the ith stone.</br>
We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:</br>
>- If x == y, both stones are destroyed, and</br>
>- If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.</br>
At the end of the game, there is **at most one** stone left.</br>
>
> Return the weight of the last remaining stone. If there are no stones left, return 0.</br>


```c
int lastStoneWeight(int* stones, int stonesSize){

}
```
>Constraints:
>- 1 <= stones.length <= 30
>- 1 <= stones[i] <= 1000

### 題目解讀
### 解法脈絡
### 程式碼本體
### 過程
- Heap
    - [Heap (data structure) From Wikipedia](https://en.wikipedia.org/wiki/Heap_(data_structure))
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 10
#define HEAP_FULL(n) (n == MAXSIZE - 1)

typedef struct {
    int key;
    /* other fields */
} element;

typedef struct {
    int r[MAXSIZE+1];
    int length;
} Sqlist;

void swap(Sqlist *, int , int);
void heapSort(Sqlist *);
void heapAdjust(Sqlist *, int, int);
void heapRemoveMax(Sqlist *);
int pop(Sqlist *);
void heapMaxBuilder(Sqlist *);
// void push(Sqlist *, int, int *);
void push(Sqlist *, int val);

int main() {
    Sqlist lst1 = {{0, 50, 10, 90, 30, 70, 40, 80, 60, 20}, 9};

    /* 將現成list改成Max Heap的排列 */
    printf ("length: %d\n", lst1.length);
    heapMaxBuilder(&lst1);
    printf ("Max heap: \n");
    for (int i=1; i<lst1.length+1; i++) {
        printf ("node%d: %d\n", i, lst1.r[i]);
    }
    printf ("\n");

    /* 將已經是Max Heap中的最大值和最小值交換再重新排列成Max Heap */
    heapRemoveMax(&lst1);
    printf ("Remove max: \n");
    for (int i=1; i<lst1.length+1; i++) {
        printf ("node%d: %d\n", i, lst1.r[i]);
    }
    printf ("\n");

    /* 將現成list排列為由小到大的順序 */
    heapSort(&lst1);
    printf ("Heap sort: \n");
    for (int i=1; i<lst1.length+1; i++) {
        printf ("node%d: %d\n", i, lst1.r[i]);
    }
    printf ("\n");

    /* 將現成list改成Max Heap的排列 */
    /* 再進行2次pop (回傳最大元素->最大最小交換->list長度少一) */
    Sqlist lst2 = {{0, 50, 10, 90, 30, 70, 40, 80, 60, 20}, 9};
    heapMaxBuilder(&lst2);
    printf ("pop 1: %d\n", pop(&lst2));
    printf ("length: %d\n", lst2.length);
    printf ("pop 2: %d\n", pop(&lst2));
    printf ("length: %d\n", lst2.length);
    /* 再進行2次push (加入元素到最後->依key值和父階比較後找到位置->list長度加一) */
    push(&lst2, 65);
    printf ("push 65 OK:\n");
    printf ("length: %d\n", lst2.length);
    push(&lst2, 45);
    printf ("push 45 OK:\n");
    printf ("length: %d\n", lst2.length);
    for (int i=1; i<lst2.length+1; i++) {
        printf ("node%d: %d\n", i, lst2.r[i]);
    }

    /* 將元素依Max heap規則放入list中 */
    Sqlist lst3;
    lst3.length = 0;

    push(&lst3, 50);
    push(&lst3, 10);
    push(&lst3, 90);
    push(&lst3, 30);
    push(&lst3, 70);
    push(&lst3, 40);
    push(&lst3, 80);
    push(&lst3, 60);
    push(&lst3, 20);

    for (int i=1; i<lst3.length+1; i++) {
        printf ("node%d: %d\n", i, lst3.r[i]);
    }

    return 0;
}

/* 數值交換 */
void swap(Sqlist *L, int i, int j) {
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

/* 建立一個Max Heap的排列，最大值在最前面 */
void heapMaxBuilder(Sqlist *L) {
    for (int i=L->length/2; i>0; i--) {
        heapAdjust(L, i, L->length);
    }
}

/* 輸出由小到大排序後的結果，最大的會被放到最後面 */
void heapSort(Sqlist *L) {
    for (int i=L->length/2; i>0; i--) {
        heapAdjust(L, i, L->length);
    }

    for (int i=L->length; i>1; i--) {
        swap(L, 1, i);
        heapAdjust(L, 1, i-1);
    }
}

/* 將最大值與最小值交換，再將剩下的重新排列，排列後原來的次大值在最前面 */
void heapRemoveMax(Sqlist *L) {
    swap(L, 1, L->length);
    heapAdjust(L, 1, L->length-1);
}

/* delete element with the highest key from the heap */
int pop(Sqlist *L) {
    int item = L->r[1];
    swap(L, 1, L->length);
    heapAdjust(L, 1, --(L->length));
    return item;
}

/* Heap調整方式 */
void heapAdjust(Sqlist *L, int s, int m) {  /* Heap調整方式 */
    int temp, j;
    temp = L->r[s];
    for (int j=2*s; j<=m; j*=2) {
        if ((j < m) && (L->r[j] < L->r[j+1])) {
            j++;
        }
        if (temp >= L->r[j]) {
            break;
        }
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp;
}

/* insert item into a max heap of current size *n */
void push(Sqlist *L, int val) {
    int i;
    if (HEAP_FULL(L->length)) {
        return;
    }
    i = ++(L->length);
    while ((i != 1) && (val > L->r[i / 2])) {
        L->r[i] = L->r[i / 2];
        i /= 2;
    }
    L->r[i] = val;
}
```
- 初始想法就是找出最大的數再找出次大的數
    - 如果兩個相等則石頭數量少2
    - 如果不相等則石頭數量少1，最大變成最大減去次大
    - 重複這個過程直到石頭數量剩最後一個
- 2022-07-28上傳
```cpp
int lastStoneWeight(int* stones, int stonesSize){
    int max, max_index, submax, submax_index;
    int i;
    int stones_num = stonesSize;

    if (stonesSize == 1) {
        return stones[0];
    }

    while (stones_num > 1) {
        max_index = findMax(stones, stonesSize);
        max = stones[max_index];
        stones[max_index] = 0;

        submax_index = findMax(stones, stonesSize);
        submax = stones[submax_index];
        stones[submax_index] = 0;

        if (max == submax) {
            stones_num -= 2;
        } else {
            stones[max_index] = abs(max - submax);
            stones_num -= 1;
        }
    }


    for (i=0; i<stonesSize; i++) {
        if (stones[i] != 0) {
            return stones[i];
        }
    }
    return 0;
}

int findMax(int *lst, int num) {
    int max = 0;
    int max_i = 0;
    for (int i=0; i<num; i++) {
        if (lst[i] >= max) {
            max = lst[i];
            max_i = i;
        }
    }
    return max_i;
}
```

---
## 692. Top K Frequent Words

### 題目
> Given an array of strings $words$ and an integer $k$, return the $k$ most frequent strings.</br>
Return the answer sorted by the frequency from highest to lowest. Sort the words with the same frequency by their lexicographical order.</br>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize){

}
```

>Constraints:
>- 1 <= words.length <= 500
>- 1 <= words[i].length <= 10
>- words[i] consists of lowercase English letters.
>- k is in the range [1, The number of unique words[i]]

### Process
- Lexicographical Order
    - [Lexicographic order From Wikipedia](https://en.wikipedia.org/wiki/Lexicographic_order)
```cpp
/* 回傳 1: 字母依序比較其中a[i] > b[i]，或是依序比較後每個字母相同但是a比較長 */
/* 回傳 0: 依序比較每個字母都相同，而且a b的字串長度相同 */
/* 回傳 -1: 字母依序比較其中a[i] < b[i]，或是依序比較後每個字母相同但是a比較短 */
int lexicographicOrder(char *a, char *b) {
    int i = 0;

    while ((a[i] != '\0') && (b[i] != '\0')) {
        if (a[i] > b[i]) {
            return 1;
        } else if (a[i] < b[i]){
            return -1;
        }
        i++;
    }

    if ((a[i] == '\0') && (b[i] == '\0')) {
        return 0;
    } else if (a[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}
```
- 2022-07-28嘗試，
    - 這次嘗試的問題在於無法判斷同樣高頻的字串誰要排在前面
    - 改進方向：可以將找最大的判斷改成頻率相同時判斷字典順序
```cpp
char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize){
    int counter;
    int max, max_index, submax, submax_index;

    int *dynArr = (int *)calloc(wordsSize, sizeof(int));

    char **dynArr2D = (char **)malloc(sizeof(char *) * 2);
    for (int i=0; i<2; i++) {
        dynArr2D[i] = (char *)malloc(sizeof(char) * 500);     /* 動態記憶體配置 */
        memset(dynArr2D[i], '\0', 1 * sizeof(char));         /* 記憶體區塊設定 -> 用來初始化 */
    }


    for (int i=0; i<wordsSize; i++) {
        if (dynArr[i] != -1) {
            counter = 1;
        } else {
            continue;
        }

        for (int j=i; j<wordsSize; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                counter++;
                dynArr[j] = -1;
            }
        }
        dynArr[i] = counter;
    }

    for (int i=0; i<k; i++) {
        max_index = findMax(dynArr, wordsSize);
        dynArr[max_index] = 1;
        strcpy(dynArr2D[i], words[max_index]);
    }

    *returnSize = k;

    return dynArr2D;
}

int findMax(int *lst, int num) {  // 可以將找最大的判斷改成頻率相同時判斷字典順序
    int max = 0;
    int max_i = 0;
    for (int i=0; i<num; i++) {
        if (lst[i] >= max) {
            max = lst[i];
            max_i = i;
        }
    }
    return max_i;
}
```

- 參考網路上的做法
    - [[LeetCode] Top K Frequent Words 前K个高频词](https://www.cnblogs.com/grandyang/p/7689927.html)
- 2022-07-29上傳
```cpp
#define MAXSIZE 100
#define MAX_STR_SIZE 20
#define HEAP_FULL(n) (n == MAXSIZE - 1)

typedef struct {
    char data[MAX_STR_SIZE];
    int freq;
    /* other fields */
} element;

typedef struct {
    element r[MAXSIZE+1];
    int length;
} Sqlist;

element pop(Sqlist *);
void push(Sqlist *, element);
void heapAdjust(Sqlist *, int, int);
int heapOrder(element *, element *);
int lexicographicOrder(char *, char *);

char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize){
    int counter;
    Sqlist lst1;
    lst1.length = 0;

    int *dynArr = (int *)calloc(wordsSize, sizeof(int));  /* 動態記憶體配置初始化為0 */
    char **dynArr2D = (char **)malloc(sizeof(char *) * k);  /* 動態記憶體配置 */
    for (int i=0; i<k; i++) {
        dynArr2D[i] = (char *)malloc(sizeof(char) * MAX_STR_SIZE);  /* 動態記憶體配置 */
        memset(dynArr2D[i], '\0', 1 * sizeof(char));  /* 記憶體區塊設定 -> 用來初始化為空字串 */
    }

    /* 找出字串重複的次數並記錄 */
    for (int i=0; i<wordsSize; i++) {
        if (dynArr[i] != -1) {
            counter = 1;
        } else {
            continue;
        }

        for (int j=i+1; j<wordsSize; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                counter++;
                dynArr[j] = -1;
            }
        }
        dynArr[i] = counter;
    }

    /* 將字串和出現頻率一起丟到Heap裡，頻率相同的元素依字典順序排序 */
    for (int i=0; i<wordsSize; i++) {
        if (dynArr[i] > 0) {
            element item;
            strcpy(item.data, words[i]);
            item.freq = dynArr[i];
            push(&lst1, item);
        }
    }

    /* 取出題目要求的前幾名高頻字串 */
    for (int i=0; i<k; i++) {
        strcpy(dynArr2D[i], pop(&lst1).data);
    }
    *returnSize = k;
    return dynArr2D;
}

/* 元素內容交換 */
void swap(Sqlist *L, int i, int j) {
    element temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

/* delete element with the highest key from the heap */
element pop(Sqlist *L) {
    element item = L->r[1];
    swap(L, 1, L->length);
    heapAdjust(L, 1, --(L->length));
    return item;
}

/* Heap調整方式 */
void heapAdjust(Sqlist *L, int s, int m) {
    element temp;
    int j;
    temp = L->r[s];
    for (int j=2*s; j<=m; j*=2) {
        if ((j < m) && (heapOrder(&(L->r[j]), &(L->r[j+1])) < 0)) {
            j++;
        }
        if (heapOrder(&temp, &(L->r[j])) >= 0) {
            break;
        }
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp;
}

/* insert item into a max heap of current size *n */
void push(Sqlist *L, element item) {
    int i;
    if (HEAP_FULL(L->length)) {
        return;
    }
    i = ++(L->length);
    while ((i != 1) && (heapOrder(&item, &(L->r[i / 2])) > 0)) {
        L->r[i] = L->r[i / 2];
        i /= 2;
    }
    L->r[i] = item;
}

/* 回傳 1: a > b，a的freq 大於 b的freq或是在 a的freq 等於 b的freq情況下，a的字典順序較靠前*/
/* 回傳 0: a = b */
/* 回傳 -1: a = b */
int heapOrder(element *a, element *b) {
    if (a->freq > b->freq) {
        return 1;
    } else if (a->freq < b->freq) {
        return -1;
    } else {
        if (lexicographicOrder(a->data, b->data) < 0) {
            return 1;
        } else if (lexicographicOrder(a->data, b->data) > 0) {
            return -1;
        } else {
            return 0;
        }
    }
}

/* 回傳 1: 字母依序比較其中a[i] > b[i]，或是依序比較後每個字母相同但是a比較長 */
/* 回傳 0: 依序比較每個字母都相同，而且a b的字串長度相同 */
/* 回傳 -1: 字母依序比較其中a[i] < b[i]，或是依序比較後每個字母相同但是a比較短 */
int lexicographicOrder(char *a, char *b) {
    int i = 0;

    while ((a[i] != '\0') && (b[i] != '\0')) {
        if (a[i] > b[i]) {
            return 1;
        } else if (a[i] < b[i]){
            return -1;
        }
        i++;
    }

    if ((a[i] == '\0') && (b[i] == '\0')) {
        return 0;
    } else if (a[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

```
- 延伸內容
    - [Priority queue From Wikipedia](https://en.wikipedia.org/wiki/Priority_queue)
    - [Day-11 priority queue](https://ithelp.ithome.com.tw/articles/10269601)
    - [Priority Queue：Intro(簡介)](http://alrightchiu.github.io/SecondRound/priority-queueintrojian-jie.html)
    - [Priority Queue：Binary Heap](http://alrightchiu.github.io/SecondRound/priority-queuebinary-heap.html)
    - [std::priority_queue - cplusplus.com](https://cplusplus.com/reference/queue/priority_queue/)