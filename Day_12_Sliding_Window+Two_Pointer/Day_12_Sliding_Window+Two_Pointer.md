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