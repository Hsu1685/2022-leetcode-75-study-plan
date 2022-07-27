# Day 11 Dynamic Programming

## 746. Min Cost Climbing Stairs

### 題目
>You are given an integer array $cost$ where $cost[i]$ is the cost of $i^{th}$ step on a staircase. Once you pay the cost, you can either climb one or two steps..</br>
You can either start from the step with index $0$, or the step with index $1$..</br>
Return *the minimum cost to reach the top of the floor*.</br>


```c
int minCostClimbingStairs(int* cost, int costSize){

}
```
>Constraints:
>- 2 <= cost.length <= 1000
>- 0 <= cost[i] <= 999

### 過程
- 參考網路上的做法
    - [[LeetCode] 746. Min Cost Climbing Stairs 爬楼梯的最小损失](https://www.cnblogs.com/grandyang/p/8343874.html)
    - 想法1: dp[i] -> 踩上[ i ]階所需要的花費，題目總共有3階(第0、第1、第2)的話，求就是dp[3]也就是踩上第3階的花費，踩上第3階的方法就是先踩上第2階或第1階，選擇最小花費dp[3] = MIN(dp[2] + cost[2], dp[1] + cost[1])，可以選擇從0或1出發，於是dp[0] = 0、dp[1] = 0。
        ```c
        #define MIN(x, y) (((x) < (y)) ? (x) : (y))

        int minCostClimbingStairs(int* cost, int costSize){

            int dp[1001] = {0};

            dp[0] = 0;
            dp[1] = 0;

            for (int i=2; i<costSize+1; i++) {
                dp[i] = MIN(cost[i - 1] + dp[i - 1], cost[i - 2] + dp[i - 2]);
            }
            return dp[costSize];
        }

    - 想法2: dp[i] -> 踩上[ i + 1 ]階所需要的花費，題目有3階的話，所求就是MIN(dp[2 - 1], dp[2 - 2])，dp[2] = MIN(dp[1], dp[0]) + cost[2]
        - dp[0] = 踩上[ 1 ]階所需要的花費，可以從0階開始所以踩上0不需要花費，dp[0]需要cost[0]
        - dp[1] = 踩上[ 2 ]階所需要的花費，可以從0階開始所以踩上1不需要花費，dp[1]需要cost[1]
```c
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int minCostClimbingStairs(int* cost, int costSize){

    int dp[1001] = {0};

    dp[0] = cost[0];
    dp[1] = cost[1];

    for (int i=2; i<costSize; i++) {
        dp[i] = MIN(dp[i - 1], dp[i - 2]) + cost[i];
    }
    return MIN(dp[costSize - 1], dp[costSize - 2]);
}

```


---
## 62. Unique Paths

### Description
> There is a robot on an $m x n$ grid. The robot is initially located at the **top-left corner** (i.e., $grid[0][0]$). The robot tries to move to the *bottom-right corner* (i.e., $grid[m - 1][n - 1]$). The robot can only move either down or right at any point in time.</br>
Given the two integers $m$ and $n$, return *the number of possible unique paths that the robot can take to reach the bottom-right corner*.</br>
The test cases are generated so that the answer will be less than or equal to $2 * 10^9$.</br>

```c
int climbStairs(int n){

}
```

>Constraints:
>- 1 <= m, n <= 100

### Process
- 初始想法是考慮簡單的(m. n)=(3, 2)問題，F(m, n) = F(m-1, n) + F(m, n-1)
    ```c
    int uniquePaths(int m, int n){
        if ((m == 0) || (n == 0)) return 0;
        if ((m == 1) || (n == 1)) return 1;
        return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
    }
    ```
    - 但這樣計算在(m. n)=(51, 9)問題時會Time Limit Exceeded

- 考慮使用迴圈計算從F(2, 2)一直算到F(m, n)並用陣列儲存
    - F(i, 1)和F(1, j)都是1
    - F(i, 0)和F(0, j)都是0，F(0, 1)和F(1, 0)都是0
    ```c
    int uniquePaths(int m, int n){

        int **dynArr2D = (int **)malloc(sizeof(int *) * (m+1));  /* 動態記憶體配置 */
        for (int i=0; i<(m+1); i++) {
            dynArr2D[i] = (int *)malloc(sizeof(int) * (n+1));  /* 動態記憶體配置 */
            memset(dynArr2D[i], -1, (n+1) * sizeof(int));  /* 記憶體區塊設定 -> 用來初始化 */
        }

        for (int i=0; i<(m+1); i++) {
            for (int j=0; j<(n+1); j++) {
                if ((i == 1) || (j == 1)) {
                    dynArr2D[i][j] = 1;
                }

                if ((i == 0) || (j == 0)) {
                    dynArr2D[i][j] = 0;
                }
            }
        }

        for (int i=2; i<(m+1); i++) {
            for (int j=2; j<(n+1); j++) {
                if (dynArr2D[i][j] == -1) {
                    dynArr2D[i][j] = dynArr2D[i - 1][j] + dynArr2D[i][j - 1];
                }
            }
        }
        return dynArr2D[m][n];
    }
    ```