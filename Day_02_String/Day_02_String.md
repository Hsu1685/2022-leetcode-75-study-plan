# Day 2 String

## 205. Isomorphic Strings

### 題目
>Given two strings s and t, determine if they are isomorphic.</br>
Two strings s and t are isomorphic if the characters in s can be replaced to get t.</br>
All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.</br>

```c
bool isIsomorphic(char * s, char * t){

}
```
>Constraints:
>- 1 <= s.length <= 5 * 104
>- t.length == s.length
>- s and t consist of any valid ascii character.


### 過程
- 一開始想使用迴圈但不知道傳入array的長度，後來確認字元陣列的結尾固定是'\0'，可以利用來確認長度
    ```c
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    ```
- 再來想要利用取代字元的方式，把s中的字元嘗試用t中的字元取代，最後比較取代後的字串s是否與字串t相同
    ```c
    void doReplace(char * s, char * t, int num) {
        int char1 = s[num];
        int char2 = t[num];

        while (s[num] != '\0') {
            if (s[num] == char1) {
                s[num] = char2;
            }
            num++;
        }
    }
    ```
- 要比較相同時忘記strcmp()函數，自己又寫了一個，注意本機測試時strcmp()需要#include <string.h>，使用bool型態需要#include <stdbool.h>
    ```c
    bool isIdentical(char* s, char* t) {
        int i = 0;
        while (s[i] != '\0') {
            if (s[i] != t[i]) {
                return 0;
            }
            i++;
        }
        return 1;
    }
    ```
- 再來發現只要去檢查字元是否有被對應過，有重複對應就不合格
    - 對應的定義是paper和title之間，p對應t、a對應i、e對應l、r對應e，其中t不需要對應回p，只要2個元素不要到同一個元素即可，可以對應到自己
    - 無法通過char s[ ] = "badc"、char t[ ] = "baba" 測試項目，需要對調s, t順序來確認對應
    ```c
    bool isIsomorphic(char * s, char * t){
        return !(isConflict(s, t) || isConflict(t, s));
    }
    bool isConflict(char * s, char * t) {
        int i = 0;
        int char_table[26] = {0};
        
        while (s[i] != '\0') {
            if ((char_table[s[i] - 97] != 0) && (char_table[s[i] - 97] != t[i])) {
                return 1;
            } else {
                char_table[s[i] - 97] = t[i];
            }
            i++;
        }
        return 0;
    }
    ```
- 最後是測試項中也出現包含數字的字元陣列，注意題目中說明s and t consist of any valid ascii character.
    ```c
    /* 最後上傳 */
    bool isIsomorphic(char * s, char * t){
        return !(isConflict(s, t) || isConflict(t, s));  // 對調s, t順序確認字元對應
    }
    bool isConflict(char * s, char * t) {
        int i = 0;
        int char_table[128] = {0};
        
        while (s[i] != '\0') {
            if ((char_table[s[i]] != 0) && (char_table[s[i]] != t[i])) {
                return 1;
            } else {
                char_table[s[i]] = t[i];
            }
            i++;
        }
        return 0;
    }
    ```
---
## 392. Is Subsequence

### 題目
> Given two strings s and t, return true if s is a ***subsequence*** of t, or false otherwise.</br>
A **subsequence** of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).</br>

```c
bool isSubsequence(char * s, char * t){

}
```
>Constraints:
>- 0 <= s.length <= 100
>- 0 <= t.length <= 104
>- s and t consist only of lowercase English letters.

### 過程
- 查詢strchr()函數可以用來找出字元第一個出現的位置，需要#include <string.h>，回傳值是字元第一個出現位置的指標
    - https://cplusplus.com/reference/cstring/strchr/
    - https://en.cppreference.com/w/cpp/string/byte/strchr
    - 找不到時會回傳a null pointer
    ```c
    #include <string.h>
    char str[] = "This is a sample string";

    int main() {
        char * pch;
        pch = strchr(str,'s');
        printf ("found at %d\n", pch - str + 1);  // 1,2,3,第4個位置 
        return 0;
    }
    ```
- 嘗試寫出邏輯：從t[ ]當中找出是否有s[i]相同的字元，然後確認順序：相同字元的index要越來越大
    - 但是無法通過char s[] = "ab"、char t[] = "baab" 測試項目
    ```c
    bool isSubsequence(char * s, char * t){
        int i = 0;
        int found_index = 0;
        int max_index = 0;
        
        while (s[i] != '\0') {
            if (strchr(t, s[i]) != NULL) {  // 找不到時會回傳a null pointer
                found_index = (int)(strchr(t, s[i]) - t);
                if (found_index >= max_index) {
                    t[found_index] = 'A';
                    max_index = found_index;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
            i++;
        }
        return 1;
    }
    ```
- 後來拿 t[i] 來與 s[j] 比較相同與否
    - 相同時：s[j] = 'A'，j++，i++
    - 不同時：i++
    - 最後比較 s[ ] 是否全部為'A'
    ```c
    /* 最後上傳 */
    bool checkChar(char*);

    bool isSubsequence(char * s, char * t){
        int i = 0;
        int s_index = 0;
        
        while (t[i] != '\0') {
            if (t[i] == s[s_index]) {
                s_index++;
                s[s_index - 1] = 65;
            }
            i++;
        }
        return checkChar(s);    
    }

    bool checkChar(char* s) {
        int i = 0;
        while (s[i] != '\0') {
            if ((s[i]) != 65) {
                return 0;
            }
            i++;
        }
        return 1;
    }

    ```