# Day 12 Sliding Window/Two Pointer

## 438. Find All Anagrams in a String

### 題目
> Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.</br>
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.</br>


```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char * s, char * p, int* returnSize){

}
```
>Constraints:
>- $1 <= s.length, p.length <= 3 * 10^4$
>- $s$ and $p$ consist of lowercase English letters.

### 題目解讀
- 輸入給2個字串s和p，輸出在s之中，存在p的易位構詞的位置
### 解法脈絡
### 程式碼本體
### 過程
- 想法是用來2個指標作為一個視窗來檢查s[i]中是否有p[i]的易位構詞
- 檢查的方法是易位構詞中字母出現數量是相同的，p[i]可以產生一個int char_array[26]，比較array中字母的數量就可以知道是否為易位構詞
- 2022-07-21上傳
```c
#define MAX_ARRAY_SIZE 30000

int* findAnagrams(char * s, char * p, int* returnSize){
    int *ptr = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE);
    int p_char_array[26] = {0};
    int s_char_array[26] = {0};
    int i, s_num, p_num, counter;
    int ptr1, ptr2;

    i = 0;
    while (s[i] != '\0') {
        i++;
    }
    s_num = i;

    i = 0;
    while (p[i] != '\0') {
        p_char_array[p[i] - 'a'] += 1;
        i++;
    }
    p_num = i;

    if (p_num > s_num) {
        *returnSize = 0;
        return NULL;
    }

    ptr1 = 0;
    ptr2 = p_num-1;
    i = 0;
    counter = 0;
    while (s[ptr2] != '\0') {
        if (ptr1 == 0) {
            for (int j=ptr1; j<=ptr2; j++) {
                s_char_array[s[j] - 'a'] += 1;
            }
        } else {
            s_char_array[s[ptr1 - 1] - 'a'] -= 1;
            s_char_array[s[ptr2] - 'a'] += 1;
        }

        int flag = 0;
        for (int k=0; k<26; k++) {
            if (p_char_array[k] != s_char_array[k]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            ptr[counter] = i;
            counter++;
        }
        ptr1++;
        ptr2++;
        i++;
    }

    *returnSize = counter;
    return ptr;
}
```
### 題目延伸
- [<cstring> (string.h)](https://cplusplus.com/reference/cstring/)
- [Null-terminated byte strings](https://en.cppreference.com/w/cpp/string/byte)
- 常用的C語言中字串應用函式:
    - 字串比對: strcmp
    - 字串複製: strcpy
    - 字串連接: strcat
    - 計算字串長度: strlen

---
## 424. Longest Repeating Character Replacement

### 題目
> You are given a string $s$ and an integer $k$. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most $k$ times.</br>
Return *the length of the longest substring containing the same letter you can get after performing the above operations*.</br>

```c
int climbStairs(int n){

}
```

>Constraints:
>- 1 <= s.length <= $10^5$
>- $s$ consists of only uppercase English letters.
>- 0 <= k <= s.length

### 過程
- 想法就是利用滑動視窗(有視窗開頭和視窗長度2個變數)進行檢查，由大到小，從全字串長度n為視窗長度開始檢查會有1種可能，n-1有2種可能(視窗開頭是0或1)，一直到視窗長度為1
    - 其中字串改變後要最長連續的話，~~最好檢查時只有2種字母出現，而且出現次多字母數量是k，這樣把次多的字母全換成最多的字母就會得到最長的連續字串~~，字串出現最多次數的字母數量只要是(字串長度(n) - 可變換次數(k))，就可以達到最長連續字串
    - 這種檢查方式在字串很大時會超過時間 (Time Limit Exceeded)，因為有很多組合是不需要計算的，而且花費很多時間在計算字串的字母數量
    ```c
    int characterReplacement(char * s, int k){
        int i = 0;
        int j = 0;
        int len = strlen(s);
        int break_flag = 0;

        for (i=0; i<len; i++) {
            for (j=0; j<(i+1); j++) {
                if (checkLetter(s, j, len - i, k) == 1) {
                    break_flag = 1;
                    break;
                }
            }
            if (break_flag == 1) {
                break;
            }
        }

        return (len - i);
    }

    int checkLetter(char * s, int start, int len, int input_k) {
        int char_array[26] = {0};
        int max_num = 0;
        int ret = 0;

        for (int i=start; i<(start+len); i++) {
            char_array[s[i] - 'A'] += 1;
        }

        for (int i=0; i<26; i++) {
            if (char_array[i] >= max_num) {
                max_num = char_array[i];
            }
        }

        if (max_num == len) {
            return 1;
        }

        for (int i=input_k; i>=0; i--) {
            if ((max_num + i) == len) {
                ret = 1;
                break;
            }
        }

        return ret;
    }
    ```
- 參考網路上的做法
    - 窗口只會變大或移動，不會縮小，窗口大小就是最終結果 (MAX_COUNTER只跟著右邊界更新)
        - [【Leetcode】python – [424] Longest Repeating Character Replacement 個人解法筆記 #重要題型](https://www.wongwonggoods.com/python/python_leetcode/leetcode-python-424/)
        - [LeetCode——424. 替換後的最長重複字元(Longest Repeating Character Replacement)——分析及程式碼（Java）](https://tw.java366.com/blog/detail/a909a8f90180e088cf4cff0c8a3ebbab)
        - [Leetcode每日一题：424.longest-repeating-character-replacement(替换后的最长重复字符)](https://blog.51cto.com/luweir/4861393)
        ```c
        #define MAX(a,b) (((a)>(b))?(a):(b))

        int characterReplacement(char * s, int k){
            int i = 0;
            int maxCnt = 0, start = 0, len = strlen(s);
            int char_array[26] = {0};

            for (i = 0; i < len; ++i) {
                char_array[s[i] - 'A'] += 1;
                maxCnt = MAX(maxCnt, char_array[s[i] - 'A']);
                if (i - start + 1 - maxCnt > k) {
                    --char_array[s[start] - 'A'];
                    ++start;
                }
            }
            return i - start;
        }
        ```
    - 窗口左邊界移動至符合題意為止，可能縮小 (MAX_COUNTER跟著右邊界、左邊界更新)
        - [【LeetCode】424. 替换后的最长重复字符 Longest Repeating Character Replacement（Python）](https://blog.csdn.net/fuxuemingzhu/article/details/79527303)
        ```c
        #define MAX(a,b) (((a)>(b))?(a):(b))

        int characterReplacement(char * s, int k){
            int i = 0;
            int res = 0, maxCnt = 0, start = 0, len = strlen(s);
            int char_array[26] = {0};

            for (i = 0; i < len; ++i) {
                char_array[s[i] - 'A'] += 1;
                maxCnt = MAX(maxCnt, char_array[s[i] - 'A']);
                while (i - start + 1 - maxCnt > k) {
                    --char_array[s[start] - 'A'];
                    maxCnt = MAX(maxCnt, char_array[s[start] - 'A']);
                    ++start;
                }
                res = MAX(res, i - start + 1);
            }
            return res;
        }
        ```
    - 窗口左邊界移動至符合題意為止，窗口可能縮小 (MAX_COUNTER只跟著右邊界更新)
        - [[LeetCode] Longest Repeating Character Replacement 最长重复字符置换](https://www.cnblogs.com/grandyang/p/5999050.html)
        ```c
        #define MAX(a,b) (((a)>(b))?(a):(b))

        int characterReplacement(char * s, int k){
            int i = 0;
            int res = 0, maxCnt = 0, start = 0, len = strlen(s);
            int char_array[26] = {0};

            for (i = 0; i < len; ++i) {
                char_array[s[i] - 'A'] += 1;
                maxCnt = MAX(maxCnt, char_array[s[i] - 'A']);
                while (i - start + 1 - maxCnt > k) {
                    --char_array[s[start] - 'A'];
                    ++start;
                }
                res = MAX(res, i - start + 1);
            }
            return res;
        }
        ```
    - 影片
        - [Longest Repeating Character Replacement - Leetcode 424 - Python - YouTube](https://www.youtube.com/watch?v=gqXU1UyA8pk)

