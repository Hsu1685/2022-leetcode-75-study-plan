# Day 10 Dynamic Programming

## 509. Fibonacci Number

### 題目
>The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,</br>

$$F(0) = 0, F(1) = 1$$
$$F(n) = F(n - 1) + F(n - 2), for n > 1.$$

Given $n$, calculate $F(n)$.

```c
int fib(int n){

}
```
>Constraints:
>- 0 <= n <= 30

### 過程
- 最直覺的做法,但是不停的呼叫函數會較慢，時間複雜度$O(f(n))$
    ```c
    int fib(int n){
        if (n == 1) {
            return 1;
        } else if (n > 1) {
            return fib(n - 1) + fib(n - 2);
        } else {
            return 0;
        }
    }

- 使用陣列將已經計算過的結果存入，時間複雜度$O(n)$
    ```c
    int fib(int n){
        int f[31];

        f[0] = 0;
        f[1] = 1;
        for (int i=2; i<=n; ++i) {
            f[i] = f[i-1] + f[i-2];
        }
        return f[n];
    }
    ```
- 再來是不使用陣列的迴圈計算
    ```c
    int fib(int n){
        int f = 1;
        int fn1 = 0, fn2 = 1;

        for (int i=2; i<=n; ++i) {
            fn2 = f;
            f = f + fn1;
            fn1 = fn2;
        }

        if (n == 0) return 0;
        else if (n == 1) return 1;
        else return f;
    }
    ```

---
## 70. Climbing Stairs

### 題目
> You are climbing a staircase. It takes n steps to reach the top.</br>
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?</br>

```c
int climbStairs(int n){

}
```

>Constraints:
>- 1 <= n <= 45

### 過程
- 想法和[509. Fibonacci Number]相同，若是有4階，因為每步是1-2階，所以4階的踏法可以分成 (最後踏2階)+(最後踏1階)，(最後踏2階) -> (剩下2階) -> (2階的踏法)，(最後踏1階) -> (剩下3階) -> (3階的踏法)，所以 (4階的踏法)=(三階踏法)+(二階踏法)=3+2=5
    - $F(n) = F(n-1) + F(n-2)$
    ```c
    int climbStairs(int n){
        if (n == 0 || n == 1)
            return 1;
        else
            return climbStairs(n-1) + climbStairs(n-2);
    }
    ```
    - 算法在n=42會Time Limit Exceeded



- 修正算法，不會Time Limit Exceeded
    ```c
    int climbStairs(int n){
        int f[46];

        f[0] = 1;
        f[1] = 1;

        for (int i=2; i<=n; i++) {
            f[i] = f[i-1] + f[i-2];
        }
        return f[n];
    }
    ```