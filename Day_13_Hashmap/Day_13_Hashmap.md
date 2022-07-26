# Day 13 Hashmap

## 1. Two Sum

### Description
> Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.</br>
You may assume that each input would have exactly one solution, and you may not use the same element twice.</br>
You can return the answer in any order.</br>


```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){

}
```
>Constraints:
>- 2 <= nums.length <= $10^4$
>- $-10^9$ <= nums[i] <= $10^9$
>- $-10^9$ <= target <= $10^9$
>- **Only one valid answer exists.**

>**Follow-up:** Can you come up with an algorithm that is less than O(n2) time complexity?</br>

### 題目解讀
- 給一個整數陣列nums[ ]和一個目標值target，輸出一對位置[i, j]表示nums[i]+nums[j] = target，注意解答只有一個
### 解法脈絡
### 程式碼本體
### 過程
- 一開始使用雙迴圈計算所有可能情況
```c
int output[2] = {0};

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int break_flag = 0;

    for (int i=0; i<numsSize; i++) {
        for (int j=i+1; j<numsSize; j++) {
            if ((nums[i] + nums[j]) == target) {
                output[0] = i;
                output[1] = j;
                break_flag = 1;
                break;
            }
        }
        if (break_flag) {
            break;
        }
    }

    *returnSize = 2;
    return output;
}
```

### 題目延伸
- 是否時間複雜度可以小於 $O(n2)$?
- 想法使用Hashmap建表存放(target - nums[i])的值，邊遍歷邊建表，只要走過一次就檢查完畢
#### 解法脈絡
- i=0 -> nums[0]時先建表，表位置是在abs(nums[0] % HASH_SIZE)，內容是2個元素 index{i=0} 和 val{target - nums[0]}
- i>0 -> 檢查位置abs((target - nums[i]) % HASH_SIZE)中內容的val是否和nums[i]相同
    - 若"是"則找到兩個和為target
    - 若"否"則將nums[i]繼續建表
```c
#define HASH_SIZE 200

typedef struct {
    int index;
    int val;
} element;

int output[2] = {0};

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    element hash[HASH_SIZE] = {NULL};
    element node;

    node.index = 0;
    node.val = target - nums[0];
    hash[hash_function(nums[0])] = node;

    for (int i=1; i<numsSize; i++) {
        if (hash[hash_function(target - nums[i])].val == nums[i]) {
            output[0] = hash[hash_function(target - nums[i])].index;
            output[1] = i;
            break;
        } else {
            node.index = i;
            node.val = target - nums[i];
            hash[hash_function(nums[i])] = node;
        }
    }
    *returnSize = 2;
    return output;
}

int hash_function(int key) {
    return abs(key % HASH_SIZE);
}

```

---
## 299. Bulls and Cows

### 題目
> You are playing the [Bulls and Cows](https://en.wikipedia.org/wiki/Bulls_and_Cows) game with your friend.</br>
You write down a secret number and ask your friend to guess what the number is. When your friend makes a guess, you provide a hint with the following info:</br>
>- The number of "bulls", which are digits in the guess that are in the correct position.</br>
>- The number of "cows", which are digits in the guess that are in your secret number but are located in the wrong position. Specifically, the non-bull digits in the guess that could be rearranged such that they become bulls.</br>
>
> Given the secret number $secret$ and your friend's guess $guess$, return the *hint for your friend's guess*.</br>
The hint should be formatted as **"xAyB"**, where $x$ is the number of bulls and y is the number of cows. Note that both $secret$ and $guess$ may contain duplicate digits.</br>

```c
char * getHint(char * secret, char * guess){

}
```

>Constraints:
>- 1 <= secret.length, guess.length <= 1000
>- secret.length == guess.length
>- secret and guess consist of digits only.

### Process
- 想法是計算secret和guess的數字(0-9)出現個數，如果1個數字(0-9)在secret和guess都有出現，則有猜對
- 計算猜對的數量時以secret和guess少的那邊為主，
    - 例如secret(1807)和guess(7781)對7來說只有猜中1個(計算少的那邊secret只有1個7)，全部是3B
    - 例如secret(1877)和guess(7081)對7來說還是只有猜中1個(計算少的那邊guess只有1個7)，全部是3B
- 把0-9的數量取secret和guess少的全部加起來就是[總共猜對的數字]
- 再來一對一比對是否有猜中A(位置及數字都對?)，最後計算B = [總共猜對的數字] - A的數量
- C中將整數轉為字串的方法
    - [How to convert an int to string in C?](https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c)
    - [如何在 C 語言中把整數轉換成字串](https://www.delftstack.com/zh-tw/howto/c/how-to-convert-an-integer-to-a-string-in-c/)
    - sprintf()
    - itoa()
```c
char output[50];

char * getHint(char * secret, char * guess){
    int secret_len = strlen(secret);
    int secret_num[10] = {0};
    int guess_num[10] = {0};
    int i, j, a_output, b_output, a_cal, b_cal;
    char temp[10];

    /* 計算secret和guess每個數字出現的次數，順便計算A */
    a_output = 0;
    for (int i=0; i<secret_len; i++) {
        secret_num[secret[i] - '0'] += 1;
        guess_num[guess[i] - '0'] += 1;
        if (secret[i] == guess[i]) {
            a_output++;
        }
    }

    /* 計算B */
    b_output = 0;
    for (int i=0; i<10; i++) {
        if ((secret_num[i] != 0) && (guess_num[i] != 0)) {
            if (secret_num[i] <= guess_num[i]) {
                b_output += secret_num[i];
            } else {
                b_output += guess_num[i];
            }

        }
    }
    b_output = b_output - a_output;

    strcpy(output, "");
    strcpy(temp, "");

    /* 將A: int -> char[] */
    if (a_output != 0) {
        a_cal = a_output;
        i = 0;
        while (a_cal != 0) {
            a_cal = a_cal / 10;
            i++;
        }
        temp[i] = '\0';

        while (i > 0) {
            temp[i - 1] = (a_output % 10) + '0';
            a_output = a_output / 10;
            i--;
        }
    } else {
        temp[0] = '0';
        temp[1] = '\0';
    }

    strcpy(output, temp);
    strcat(output, "A");

    /* 將B: int -> char[] */
    if (b_output != 0) {
        b_cal = b_output;
        i = 0;
        while (b_cal != 0) {
            b_cal = b_cal / 10;
            i++;
        }
        temp[i] = '\0';

        while (i > 0) {
            temp[i - 1] = (b_output % 10) + '0';
            b_output = b_output / 10;
            i--;
        }
    } else {
        temp[0] = '0';
        temp[1] = '\0';
    }

    strcat(output, temp);
    strcat(output, "B");

    return output;
}
```