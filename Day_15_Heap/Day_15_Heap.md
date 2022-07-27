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
    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

    #define MAXSIZE 10

    typedef struct {
        int r[MAXSIZE+1];
        int length;
    } Sqlist;

    void swap(Sqlist *, int , int);
    void heapSort(Sqlist *);
    void heapAdjust(Sqlist *, int, int);
    void heapRemoveMax(Sqlist *);
    void heapMaxBuilder(Sqlist *);

    int main() {
        Sqlist lst1 = {{0, 50, 10, 90, 30, 70, 40, 80, 60, 20}, 9};

        printf ("length: %d\n", lst1.length);
        heapMaxBuilder(&lst1);
        printf ("Max heap: \n");
        for (int i=1; i<lst1.length+1; i++) {
            printf ("node%d: %d\n", i, lst1.r[i]);
        }
        heapRemoveMax(&lst1);
        printf ("Remove max: \n");
        for (int i=1; i<lst1.length+1; i++) {
            printf ("node%d: %d\n", i, lst1.r[i]);
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

    /* 將最大值與最小值交換，再將剩下的重新排列，排列後最大值依然在最前面 */
    void heapRemoveMax(Sqlist *L) {
        swap(L, 1, L->length);
        heapAdjust(L, 1, L->length-1);
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
    ```