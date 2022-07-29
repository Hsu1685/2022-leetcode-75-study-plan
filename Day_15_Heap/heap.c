#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 10
#define HEAP_FULL(n) (n == MAXSIZE - 1)

typedef struct {
    int key;
    /* other fields */
} element;

typedef struct {
    int r[MAXSIZE + 1];
    int length;
} Sqlist;

void swap(Sqlist *, int, int);
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
    printf("length: %d\n", lst1.length);
    heapMaxBuilder(&lst1);
    printf("Max heap: \n");
    for (int i = 1; i < lst1.length + 1; i++) {
        printf("node%d: %d\n", i, lst1.r[i]);
    }
    printf("\n");

    /* 將已經是Max Heap中的最大值和最小值交換再重新排列成Max Heap */
    heapRemoveMax(&lst1);
    printf("Remove max: \n");
    for (int i = 1; i < lst1.length + 1; i++) {
        printf("node%d: %d\n", i, lst1.r[i]);
    }
    printf("\n");

    /* 將現成list排列為由小到大的順序 */
    heapSort(&lst1);
    printf("Heap sort: \n");
    for (int i = 1; i < lst1.length + 1; i++) {
        printf("node%d: %d\n", i, lst1.r[i]);
    }
    printf("\n");

    /* 將現成list改成Max Heap的排列 */
    /* 再進行2次pop (回傳最大元素->最大最小交換->list長度少一) */
    Sqlist lst2 = {{0, 50, 10, 90, 30, 70, 40, 80, 60, 20}, 9};
    heapMaxBuilder(&lst2);
    printf("pop 1: %d\n", pop(&lst2));
    printf("length: %d\n", lst2.length);
    printf("pop 2: %d\n", pop(&lst2));
    printf("length: %d\n", lst2.length);
    /* 再進行2次push (加入元素到最後->依key值和父階比較後找到位置->list長度加一)
     */
    push(&lst2, 65);
    printf("push 65 OK:\n");
    printf("length: %d\n", lst2.length);
    push(&lst2, 45);
    printf("push 45 OK:\n");
    printf("length: %d\n", lst2.length);
    for (int i = 1; i < lst2.length + 1; i++) {
        printf("node%d: %d\n", i, lst2.r[i]);
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

    for (int i = 1; i < lst3.length + 1; i++) {
        printf("node%d: %d\n", i, lst3.r[i]);
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
    for (int i = L->length / 2; i > 0; i--) {
        heapAdjust(L, i, L->length);
    }
}

/* 輸出由小到大排序後的結果，最大的會被放到最後面 */
void heapSort(Sqlist *L) {
    for (int i = L->length / 2; i > 0; i--) {
        heapAdjust(L, i, L->length);
    }

    for (int i = L->length; i > 1; i--) {
        swap(L, 1, i);
        heapAdjust(L, 1, i - 1);
    }
}

/* 將最大值與最小值交換，再將剩下的重新排列，排列後原來的次大值在最前面 */
void heapRemoveMax(Sqlist *L) {
    swap(L, 1, L->length);
    heapAdjust(L, 1, L->length - 1);
}

/* delete element with the highest key from the heap */
int pop(Sqlist *L) {
    int item = L->r[1];
    swap(L, 1, L->length);
    heapAdjust(L, 1, --(L->length));
    return item;
}

/* Heap調整方式 */
void heapAdjust(Sqlist *L, int s, int m) { /* Heap調整方式 */
    int temp, j;
    temp = L->r[s];
    for (int j = 2 * s; j <= m; j *= 2) {
        if ((j < m) && (L->r[j] < L->r[j + 1])) {
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