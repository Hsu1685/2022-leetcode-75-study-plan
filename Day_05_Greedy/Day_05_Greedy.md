# Day 5 Greedy

## 121. Best Time to Buy and Sell Stock

### 題目
>You are given an array prices where prices[i] is the price of a given stock on the ith day.</br>
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.</br>
Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.</br>

```c
int maxProfit(int* prices, int pricesSize){

}
```
>Constraints:
>- 1 <= prices.length <= $10^5$
>- 0 <= prices[i] <= $10^4$

### 過程
- 一開始使用雙迴圈計算所有可能情況，但是在測試項目較多時會產生**Time Limit Exceeded**
    ```c
    int maxProfit(int* prices, int pricesSize){
        int max_profit = 0;
        int temp_profit = 0;
        int i, j;
        
        for (i=0; i<pricesSize-1; i++) {
            for (j=i+1; j<pricesSize; j++) {
                temp_profit = prices[j] - prices[i];
                if (temp_profit <= 0) {
                    break;
                }
                if (temp_profit >= max_profit) {
                    max_profit = temp_profit;
                }
            }
        }
        return max_profit;
    }
    ```

- 後來想到一次走過找到最小值和最大值，但是最大獲利不等於**最大值-最小值**
    ```c
    int maxProfit(int* prices, int pricesSize){
        int max_price, min_price;
        int max_price_day = 0;
        int min_price_day = 0;
        int temp_price = 0;
        int i;
        
        max_price = prices[0];
        min_price = prices[0];
        
        for (i=1; i<pricesSize; i++) {
            temp_price = prices[i];
            if (temp_price >= max_price) {
                max_price = temp_price;
                max_price_day = i;
            }
            
            if (temp_price <= min_price) {
                min_price = temp_price;
                min_price_day = i;
            }        
        }
        
        if (max_price_day > min_price_day) {
            return max_price - min_price;
        } else {
            return 0;
        }
    }
    ```

- 過程中修改雙迴圈裡的[break; -> coninue]，可以通過測試但時間很不理想
    ```c
    if (temp_profit <= 0) {
        continue;
    }
    ```

- 參考網路上的解法，發現和找最大值、最小值方法比較接近，同樣是遍歷1次，從第一天開始遇到價錢更低的就買下，接著後面一直檢查獲利是否為最大
    - 雙迴圈方法的盲點在很多組合根本不需要計算
    ```c
    int maxProfit(int* prices, int pricesSize) {
        int min_price;
        int max_profit = 0;
        int i;
        
        min_price = prices[0];
        
        for (i=1; i<pricesSize; i++) {
            if (prices[i] < min_price) {
                min_price = prices[i];
            }
            
            if ((prices[i] - min_price) > max_profit) {
                max_profit = prices[i] - min_price;
            }
        }    
        return max_profit;
    }
    ```

---
## 409. Longest Palindrome

### 題目
> Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.</br>
Letters are case sensitive, for example, "Aa" is not considered a palindrome here.</br>


```c
int longestPalindrome(char * s){

}
```
>Constraints:
>- 1 <= s.length <= 2000
>- s consists of lowercase **and/or** uppercase English letters only.

### 過程
- 想法是用array記錄每個字元出現的次數，再全部一起處理
    - 若出現偶數次，則不論是否有一個或多個偶數都可以形成迴文
        - aa自己是迴文，**bb**a**bb**可以自己形成也可以配合形成迴文
    - 若出現的是奇數次，則分成兩種情況
        - 只有1個奇數次，則a自身是迴文，bbb也是迴文
        - 出現多個奇數次，則每次會增加[出現次數-1]的迴文長度
        - [aaabbb]，最長就是baaab或abbba，長度都是5(第1個奇數->3 + 第2個奇數->3 - 1)
        - [aaabbbbb]，最長就是abbbbba，長度是7(第1個奇數->3 + 第2個奇數->5 - 1)
    ```c
    int longestPalindrome(char * s){
        int char_array[128] = {0};
        int i;
        int only_one_char_flag = 0, odd_number_char_flag = 0, ret = 0;
            
        i = 0;
        while (s[i] != '\0') {
            char_array[s[i]] += 1;
            i++;
        }
        
        for (i=0; i<128; i++) {
            if (char_array[i] == 0) {
                continue;
            }
            
            if ((odd_number_char_flag == 0) && ((char_array[i] % 2) == 1)) {
                ret += char_array[i];
                odd_number_char_flag = 1;
            } else if ((char_array[i] % 2) == 1) {
                ret += char_array[i] - 1;
            } else if ((char_array[i] % 2) == 0) {
                ret += char_array[i];
            }
        }
        return ret;
    }
    ```
