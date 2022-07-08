# Day 1 Prefix Sum

## 1480. Running Sum of 1d Array

### 題目
>Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).</br>
Return the running sum of nums.</br>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize){

}
```

### 過程
- 一開始不確定題目中預設函數的設定
    ```c
    int* runningSum(int* nums, int numsSize, int* returnSize)
    ```
- return值是計算好後輸出的array
- int* nums是輸入的array, numsSize是該array的大小
- int* returnSize是要提供輸出array的大小
- 要在函數中動態建立array記憶體再回傳array的位置
- C透過指標傳入函數都要再提供array的大小，不然其實無法得知array大小
    ```c
    /* 最後上傳 */
    /**
    * Note: The returned array must be malloced, assume caller calls free().
    */
    int* runningSum(int* nums, int numsSize, int* returnSize){
        int sum = 0;    
        int* dynArr = malloc(numsSize * sizeof(int));
        
        *dynArr = *nums;
        for (int i=1; i<numsSize; i++) {
            *(dynArr+i) = *(nums+i) + *(dynArr+i-1);        
        }
        *returnSize = numsSize;  // 要回傳陣列的大小
        return dynArr;
    }
    ```
## 724. Find Pivot Index

### 題目
> Given an array of integers nums, calculate the pivot index of this array.</br>
The pivot index is the index where the sum of all the numbers strictly to the left of the index is equal to the sum of all the numbers strictly to the index's right.</br>
If the index is on the left edge of the array, then the left sum is 0 because there are no elements to the left. This also applies to the right edge of the array.</br>
Return the leftmost pivot index. If no such index exists, return -1.</br>

```c
int pivotIndex(int* nums, int numsSize){

}
```

### 過程
- 一開始想到的方法是用多個迴圈計算
    - 假設pivot index=0時計算總合是不是0
    - 接著假設pivot index=i時，分別迴圈計算i左邊的總和及右邊的總和
    ```c
    int pivotIndex(int* nums, int numsSize){
        int i, j, k;
        int sum_0 = 0;
        int sum_left, sum_right = 0;
        
        for (i=1; i<numsSize; i++) {
            sum_0 += nums[i];
        }
        if (sum_0 == 0) {
            return 0;
        }
        
        for (i=1; i<numsSize; i++) {
            sum_left = 0;
            sum_right = 0;
            for (j=0; j<i; j++) {
                sum_left += nums[j];
            }
            
            for (k=i+1; k<numsSize; k++) {
                sum_right += nums[k];
            }
            
            if (sum_left == sum_right) {
                return i;
            }
        }    
        return -1;
    }
    ```
- 後來發現既然一開始全部總和已經計算過了，接下來所有i的左邊總和及右邊總和，都和全部總合差異1個元素而已
    ```c
    /* 最後上傳 */
    int pivotIndex(int* nums, int numsSize){
        int i;
        int sum_total = 0;
        int sum_left, sum_right = 0;
        
        for (i=0; i<numsSize; i++) {
            sum_total += nums[i];
        }
        if ((sum_total - nums[0]) == 0) {
            return 0;
        }
        
        for (i=1; i<numsSize; i++) {
            sum_left += nums[i-1];
            sum_right = sum_total -  nums[i] - sum_left;
            
            if (sum_left == sum_right) {
                return i;
            }
        }    
        return -1;
    }
    ```
    - 修改後計算時間從1583 ms左右降到31 ms左右