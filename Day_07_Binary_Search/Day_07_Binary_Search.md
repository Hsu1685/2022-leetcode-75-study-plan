# Day 7 Binary Search

## 704. Binary Search

### 題目
>Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.</br>
You must write an algorithm with O(log n) runtime complexity.</br>

```c
int search(int* nums, int numsSize, int target){

}
```
>Constraints:
>- 1 <= nums.length <= $10^4$
>- -$10^4$ < nums[i], target < $10^4$
>- All the integers in nums are unique.
>- nums is sorted in ascending order.

### 過程
- [二分搜尋演算法 - 維基百科](https://zh.wikipedia.org/zh-tw/%E4%BA%8C%E5%88%86%E6%90%9C%E5%B0%8B%E6%BC%94%E7%AE%97%E6%B3%95)
- 想法就是確認資料的中間值
  - 是否為目標值
  - 中間值大於目標值，目標值在較小的半部
  - 中間值小於目標值，目標值在較大的半部
  - 重複以上過程直到剩下的半部數量為[1]
    ```c
    int search(int* nums, int numsSize, int target){
        int next_index, next_size, index_start;

        next_index = 0;
        next_size = numsSize;
        index_start = 0;

        if ((next_size == 1) && (nums[0] == target)) {
            return 0;
        }

        next_index = next_size / 2;

        while (next_size > 1) {
            next_index = index_start + (next_size / 2);

            if (nums[next_index] < target) {

                if (next_size % 2) {
                    next_size = (next_size - 1) / 2;
                } else {
                    next_size = (next_size / 2) - 1;
                }

                index_start = next_index + 1;
                if ((next_size == 1) && (nums[next_index + 1] == target)) {
                    return next_index + 1;
                }

            } else if (nums[next_index] > target) {

                if (next_size % 2) {
                    next_size = (next_size - 1) / 2;
                } else {
                    next_size = (next_size / 2);
                }

                if ((next_size == 1) && (nums[next_index - 1] == target)) {
                    return next_index - 1;
                }

            } else {
                return next_index;
            }
        }
        return -1;
    }
    ```

---
## 278. First Bad Version

### 題目
> You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.</br>
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.</br>
You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.</br>


```c
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) {

}
```
>Constraints:
>- 1 <= bad <= n <= $2^{31}$ - 1

### 過程
- 一開始也是考慮和[704. Binary Search]相同的作法，後來覺得可以直接由更新上下限來做逼近
    ```c
    int firstBadVersion(int n) {
        int next_n;
        int next_n_start;
        int next_n_size;

        int n_right_limit = n;
        int n_left_limit = 1;

        next_n_start = 1;
        next_n_size = n;

        next_n = n;

        if (next_n == 1) {
            if (isBadVersion(next_n_start)) {
                return 1;
            }
        }

        while (1) {
            next_n = next_n_start +  (next_n_size / 2);

            if (isBadVersion(next_n)) {
                n_right_limit = next_n;
                next_n_size = (next_n_size / 2);
            } else {
                next_n_start = next_n + 1;
                n_left_limit = next_n + 1;
                next_n_size = (next_n_size / 2);
            }

            if (n_right_limit == n_left_limit) {
                return n_right_limit;
            }
        }
        return -1;
    }
    ```