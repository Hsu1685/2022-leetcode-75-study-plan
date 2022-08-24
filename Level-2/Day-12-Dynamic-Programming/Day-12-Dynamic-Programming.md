# Day 12 Sliding Window/Two Pointer

## 198. House Robber
- Medium

### Description
> You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and **it will automatically contact the police if two adjacent houses were broken into on the same night.**</br>

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight **without alerting the police.**</br>


### Initial
```cpp
int rob(int* nums, int numsSize){

}
```

### Constraints:
>- 1 <= nums.length <= 100
>- 0 <= nums[i] <= 400


### 題目解讀
### 解法脈絡
### 程式碼本體
### 參考資料
- []()
### 過程
- 一開始的想法是先選出陣列裡的最大值就可以將陣列分割成2部分，接著再選次大值繼續分割，直到剩下的部分可以直接求出，後來發現這樣並不會得到最大的總和(例如選了最大值勢必會捨棄其左右2個數值，但有時其左右兩個數值加起來比最大值還大)
- 暴力列出所有可行性的話其數量也太大
- 既然用最大值分不行就乾脆對半分，類似二分搜尋法將陣列從中間分成左半部和右半部，一直分割到剩下部分可以直接得出
- 過程中分割的點其實可以選擇正中央的數值，也可以選擇前一個或後一個數值
    - 可能性如下，5個元素可以選擇(index=2)分割也可以選擇(index=1)或(index=3)
    - 不同的選擇都要分別加總找出最大值


- 2022-08-23測試
```cpp
int rob(int* nums, int numsSize){
    return robMax(0, numsSize-1, nums);
    // return nums[numsSize];
}

int robMax(int s, int e, int* nums) {
    if (s == e) {
        return 0;
    }

    if ((e - s) == 1) {
        return nums[s];
    }

    int max_index = findMax(s, e, nums);
    return robMax(s, max_index-1, nums) + robMax(max_index+1, e, nums) + nums[max_index];
}

int findMax(int s, int e, int* nums) {
    int i;
    int max_index = s;
    int max_value = nums[s];

    for (i=s; i<=e; i++) {
        if (nums[i] > max_value) {
            max_value = nums[i];
            max_index = i;
        }
    }
    return max_index;
}
```

- 2022-08-24上傳
```cpp
int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];

    if (numsSize == 2) {
        if (nums[0] > nums[1]) {
            return nums[0];
        } else {
            return nums[1];
        }
    }

    if (numsSize == 3) {
        if (nums[1] > (nums[0] + nums[2])) {
            return nums[1];
        } else {
            return nums[0] + nums[2];
        }
    }

    if (numsSize == 4) {
        if ((nums[0] + nums[2]) > (nums[1] + nums[3])) {
            if (nums[2] > nums[3]) {
                return nums[0] + nums[2];
            } else {
                return nums[0] + nums[3];
            }
        } else {
            if (nums[0] > nums[1]) {
                return nums[0] + nums[3];
            } else {
                return nums[1] + nums[3];
            }
        }
    }

    int index1 = numsSize / 2;
    int result1 = robLeft(0, index1 - 2, nums) +
                  robRight(index1 + 2, numsSize - 1, nums) + nums[index1];
    // int result1 = 1;

    int index2 = (numsSize / 2) - 1;
    int result2 = robLeft(0, index2 - 2, nums) +
                  robRight(index2 + 2, numsSize - 1, nums) + nums[index2];
    // int result2 = 2;

    int index3 = (numsSize / 2) + 1;
    int result3 = robLeft(0, index3 - 2, nums) +
                  robRight(index3 + 2, numsSize - 1, nums) + nums[index3];
    // int result3 = 3;

    // if (result1 > result2) return result1;
    // else return result2;
    // return max_index;
    // return index1;
    // return result3;
    // return numsSize;
    return findMax2(result1, result2, result3);
}

int robLeft(int s, int e, int* nums) {
    // if ((s == e) || (e < s)) {
    // if (s >= e) {
    if (((e - s) < 0) || (e < 0)) {
        return 0;
    }

    if ((e - s) == 0) {
        return nums[s];
    }

    if ((e - s) == 1) {
        if (nums[s] > nums[s + 1]) {
            return nums[s];
        } else {
            return nums[s + 1];
        }
    }

    if ((e - s) == 2) {
        if (nums[s + 1] > (nums[s] + nums[s + 2])) {
            return nums[s + 1];
        } else {
            return nums[s] + nums[s + 2];
        }
    }

    if ((e - s) == 3) {
        return findMax2((nums[s] + nums[s + 2]), (nums[s + 1] + nums[s + 3]),
                        (nums[s] + nums[s + 3]));
    }

    // if ((e - s) == 4) {
    //     if ((nums[s] + nums[s + 2]) > (nums[s + 1] + nums[s + 3])) {
    //         if (nums[s + 2] > nums[s + 3]) {
    //             return nums[s] + nums[s + 2];
    //         } else {
    //             return nums[s] + nums[s + 3];
    //         }
    //     } else {
    //         if (nums[s] > nums[s + 1]) {
    //             return nums[s] + nums[s + 3];
    //         } else {
    //             return nums[s + 1] + nums[s + 3];
    //         }
    //     }
    // }

    // int max_index = findMax(s, e-1, nums);
    int left1 = s + ((e - s + 1) / 2);
    int left_result1 = robLeft(s, left1 - 2, nums) +
                       robRight(left1 + 2, e, nums) + nums[left1];

    int left2 = s + ((e - s + 1) / 2) - 1;
    int left_result2 = robLeft(s, left2 - 2, nums) +
                       robRight(left2 + 2, e, nums) + nums[left2];

    int left3 = s + ((e - s + 1) / 2) + 1;
    int left_result3 = robLeft(s, left3 - 2, nums) +
                       robRight(left3 + 2, e, nums) + nums[left3];

    // return robLeft(s, max_index-1, nums) + robRight(max_index+1, e, nums) +
    // nums[max_index];
    return findMax2(left_result1, left_result2, left_result3);
    // return result3;
}

int robRight(int s, int e, int* nums) {
    // if (s >= e) {
    // if ((e - s) < 0) {
    if (((e - s) < 0) || (e < 0)) {
        return 0;
    }

    if ((e - s) == 0) {
        return nums[e];
    }

    if ((e - s) == 1) {
        if (nums[s] > nums[s + 1]) {
            return nums[s];
        } else {
            return nums[s + 1];
        }
    }

    if ((e - s) == 2) {
        if (nums[s + 1] > (nums[s] + nums[s + 2])) {
            return nums[s + 1];
        } else {
            return nums[s] + nums[s + 2];
        }
    }

    if ((e - s) == 3) {
        return findMax2((nums[s] + nums[s + 2]), (nums[s + 1] + nums[s + 3]),
                        (nums[s] + nums[s + 3]));
    }

    // if ((e - s) == 4) {
    //     if ((nums[s + 1] + nums[s + 3]) > (nums[s + 2] + nums[s + 4])) {
    //         if (nums[s + 3] > nums[s + 4]) {
    //             return nums[s + 1] + nums[s + 3];
    //         } else {
    //             return nums[s + 1] + nums[s + 4];
    //         }
    //     } else {
    //         if (nums[s + 1] > nums[s + 2]) {
    //             return nums[s + 1] + nums[s + 4];
    //         } else {
    //             return nums[s + 2] + nums[s + 4];
    //         }
    //     }
    // }

    // int max_index = findMax(s+1, e, nums);
    int right1 = s + ((e - s + 1) / 2);
    int right_result1 = robLeft(s, right1 - 2, nums) +
                        robRight(right1 + 2, e, nums) + nums[right1];

    int right2 = s + ((e - s + 1) / 2) - 1;
    int right_result2 = robLeft(s, right2 - 2, nums) +
                        robRight(right2 + 2, e, nums) + nums[right2];

    int right3 = s + ((e - s + 1) / 2) + 1;
    int right_result3 = robLeft(s, right3 - 2, nums) +
                        robRight(right3 + 2, e, nums) + nums[right3];

    // return robLeft(s, max_index-1, nums) + robRight(max_index+1, e, nums) +
    // nums[max_index];
    return findMax2(right_result1, right_result2, right_result3);
    // return result3;
}

int findMax(int s, int e, int* nums) {
    int i;
    int max_index = s;
    int max_value = nums[s];

    for (i = s + 1; i <= e; i++) {
        if (nums[i] > max_value) {
            max_value = nums[i];
            max_index = i;
        }
    }
    return max_index;
}

int findMax2(int v1, int v2, int v3) {
    if (v1 > v2) {
        if (v1 > v3) {
            return v1;
        } else {
            return v3;
        }
    } else {
        if (v2 > v3) {
            return v2;
        } else {
            return v3;
        }
    }
}

```

