# Day 14 Stack

## 844. Backspace String Compare

### 題目
>Given two strings $s$ and $t$, return $true$ *if they are equal when both are typed into empty text editors*. $'#'$ means a backspace character.</br>
Note that after backspacing an empty text, the text will continue empty.</br>


```c
bool backspaceCompare(char * s, char * t){

}
```
>Constraints:
>- $1 <= s.length, t.length <= 200$
>- $s$ and $t$ only contain lowercase letters and '#' characters.

### Process
- 複習Stack
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int key;
} element;

void push(element);
element pop(void);
int isEmpty(void);

element stack[MAX_STACK_SIZE];
int top;

int main() {
    element item1, item2;

    top = -1;
    item1.key = 7;
    item2.key = 9;
    push(item1);
    push(item2);
    printf ("pop: %d\n", pop().key);
    printf ("pop: %d\n", pop().key);
    return 0;
}

void push(element item) {
    // if (top >= MAX_STACK_SIZE - 1) {
    //     stackFull();
    // }
    stack[++top] = item;
}

element pop(void) {
    // if (top == -1) {
    //     stackEmpty();
    // }
    return stack[top--];
}

int isEmpty(void) {
    if (top == -1) return 1;
    else return 0;
}
```
- 想法是將s[i]字元依次丟入stack1中，如果遇到'#'又stack1不空時pop()，方法相同處理t[i]至stack2中，最後將stack1與stack2做比較
  - 如果都是空的 -> TRUE
  - 如果元素數量不同 -> FALSE
  - 最後一個一個比較元素是否相同
- 2022-07-20 Submissions
```c
#define MAX_STACK_SIZE 200

void push(char *, int *, char);
char pop(char *, int *);
int isEmpty(int *);

char stack_s[MAX_STACK_SIZE];
char stack_t[MAX_STACK_SIZE];
int top_s;
int top_t;


bool backspaceCompare(char * s, char * t){
    int i;

    top_s = -1;
    top_t = -1;
    i = 0;
    while (s[i] != '\0') {
        if (s[i] != 35) {
            push(stack_s, &top_s, s[i]);
        } else if (!isEmpty(&top_s) && (s[i] == 35)) {
            pop(stack_s, &top_s);
        }
        i++;
    }

    i = 0;
    while (t[i] != '\0') {
        if (t[i] != 35) {
            push(stack_t, &top_t, t[i]);
        } else if (!isEmpty(&top_t) && (t[i] == 35)) {
            pop(stack_t, &top_t);
        }
        i++;
    }

    if ((top_s == -1) && (top_t == -1)) {
        return true;
    } else if (top_s != top_t) {
        return false;
    } else {
        i = 0;
        while (top_s >= 0) {
            if (pop(stack_s, &top_s) != pop(stack_t, &top_t))
                return false;
        }
        return true;
    }
}

void push(char *s, int *top, char item) {
    // if (top >= MAX_STACK_SIZE - 1) {
    //     stackFull();
    // }
    s[++(*top)] = item;
}

char pop(char *s, int *top) {
    // if (top == -1) {
    //     stackEmpty();
    // }
    return s[(*top)--];
}

int isEmpty(int *top) {
    if (*top == -1) return 1;
    else return 0;
}
```

---
## 394. Decode String

### 題目
> Given an encoded string, return its decoded string.</br>
The encoding rule is: $k[encoded_string]$, where the $encoded_string$ inside the square brackets is being repeated exactly $k$ times. Note that $k$ is guaranteed to be a positive integer.</br>
You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, $k$. For example, there will not be input like $3a$ or $2[4]$.</br>
The test cases are generated so that the length of the output will never exceed $10^5$.</br>

```c
int numIslands(char** grid, int gridSize, int* gridColSize){

}
```

>Constraints:
>- $1 <= s.length <= 30$
>- $s$ consists of lowercase English letters, digits, and square brackets $'[]'$.
>- s is guaranteed to be **a valid** input.
>- All the integers in $s$ are in the range $[1, 300]$.

### Process
- 最初想法是把s[i]依序處理，遇到數字就push(s[i])到stack2，遇到'['就push()後面準備等']'，遇到字母push(s[i])到stack1，最後遇到']'就進行處理，由stack2中計算應該重複幾次，由stack1中計算要重複字元的範圍[i~j]，最後進行計算
- 2022-07-20嘗試
```c

#define MAX_STACK_SIZE 200

void push(char *, int *, char);
char pop(char *, int *);
int isEmpty(int *);
char peek(char *, int);

char stack1[MAX_STACK_SIZE];
char stack2[MAX_STACK_SIZE];
int top1;
int top2;
char *ptr;

char * decodeString(char * s){
    int i, j, k, bracket, repeat, power, pos;

    top1 = -1;
    top2 = -1;
    i = 0;
    while (s[i] != '\0') {
        // 1-9
        if ((s[i] >= 48) && (s[i] <= 57)) {
            push(stack2, &top2, s[i]#include <string.h>);
        // '['
        } else if (s[i] == 91) {
            push(stack1, &top1, s[i]);
            push(stack2, &top2, s[i]);
        // a-z
        } else if ((s[i] >= 97) && (s[i] <= 122)) {
            push(stack1, &top1, s[i]);
        // ']'
        } else if (s[i] == 93) {
            pop(stack2, &top2);
            repeat = 0;
            power = 0;
            /* 找出重複次數 */
            while (top2 != -1) {
                if ((peek(stack2, top2) >= 48) && (peek(stack2, top2) <= 57)) {
                    repeat += (pop(stack2, &top2) - 48) * pow(10, power);
                    power++;
                }
            }
            /* 找出從top到最近的'['位置 -> 確定重複字串的範圍 */
            pos = 0;
            j = top1;
            while (peek(stack1, j) != 91) {
                pos = j;
                j--;
            }

            /* 利用重複次數及重複字串範圍進行重複 */
            k = 0;
            int num = top1;
            while (k < repeat-1) {
                for (int n=pos; n<=num; n++) {
                    push(stack1, &top1, peek(stack1, n));
                    /* 問題在push()完後stack1裡面還有'['又會影響到下一次的計算 */
                }
                k++;
            }
        }
        i++;
    }

    ptr = (char *)malloc(MAX_STACK_SIZE * sizeof(char));

    i = 0;
    while (i <= top1) {
        ptr[i] = peek(stack1, i);
        i++;
    }
    ptr[i] = '\0';

    return ptr;
}

void push(char *s, int *top, char item) {
    // if (top >= MAX_STACK_SIZE - 1) {
    //     stackFull();
    // }
    s[++(*top)] = item;
}

char pop(char *s, int *top) {
    // if (top == -1) {
    //     stackEmpty();
    // }
    return s[(*top)--];
}

char peek(char *s, int top) {
    // if (top == -1) {
    //     stackEmpty();
    // }
    return s[top];
}

int isEmpty(int *top) {
    if (*top == -1) return 1;
    else return 0;
}
```

- 參考他人的作法後，發現應該放入stack的不是char，應該把 '[' 之前的數字解析為int後放入stack，把 '[' 和 ']' 中間的字串放入stack，為此stack要修改為一個stack是元素是int，一個stack元素是字元陣列
    - [[LeetCode] 394. Decode String 解码字符串](https://www.cnblogs.com/grandyang/p/5849037.html)
```c
#include <string.h>

#define MAX_STACK_SIZE 200
#define MAX_STRING_SIZE 5000

typedef struct {
    char str[MAX_STRING_SIZE];
    int num;
} element;

void push(element, element *, int *);
element pop(element *, int *);
int isEmpty(int *);
element peek(element *, int *);

element stack1[MAX_STACK_SIZE];
element stack2[MAX_STACK_SIZE];
int top1;
int top2;
char *ptr;
char str_temp[MAX_STRING_SIZE];

char * decodeString(char * s){
    int i, repeat, number;
    char str_strcat[100];
    char char_temp[4];
    element input;

    top1 = -1;
    top2 = -1;
    repeat = 0;
    strcpy(str_temp, "");
    strcpy(str_strcat, "");
    strcpy(char_temp, "");

    i = 0;
    while (s[i] != '\0') {
        /* 1-9 */
        if ((s[i] >= '0') && (s[i] <= '9')) {
            repeat = (10 * repeat) + (s[i] - '0');
        /* '[' */
        /* 數字結束了，要準備收字串 */
        } else if (s[i] == '[') {
            /* 当前 cnt 压入数字栈中 */
            input.num = repeat;
            push(input, stack2, &top2);  // stack2[i]放數字
            repeat = 0;

            /* 当前t压入字符串栈中 */
            strcpy(input.str, "");
            strcpy(input.str, str_temp);
            push(input, stack1, &top1);  // stack1[i]放字串
            strcpy(str_temp, "");
        /* a-z */
        } else if ((s[i] >= 'a') && (s[i] <= 'z')) {
            strcpy(char_temp, "");
            char_temp[0] = s[i];
            char_temp[1] = '\0';
            strcat(str_temp, char_temp);
        // ']'
        } else {
            /* 取出数字栈中顶元素，存入变量k */
            number = pop(stack2, &top2).num;

            /* 给字符串栈的顶元素循环加上k个t字符串 */
            // strcpy(str_strcat, "");
            // strcpy(str_strcat, str_temp);
            for (int j=0; j<(number); j++) {
                strcat(stack1[top1].str, str_temp);
            }
            /* 然后取出顶元素存入字符串t中 */
            strcpy(str_temp, "");
            strcpy(str_temp, stack1[top1].str);
            pop(stack1, &top1);
        }
        i++;
    }

    // if (isEmpty(&top1)) {
        return str_temp;
    // } else {
        // return stack1[top1].str;
    // }
}

void push(element item, element *s, int *t) {
    // if (top >= MAX_STACK_SIZE - 1) {
    //     stackFull();
    // }
    s[++(*t)] = item;
}

element pop(element *s, int *t) {
    // if (top == -1) {
    //     stackEmpty();
    // }
    return s[(*t)--];
}

element peek(element *s, int *t) {
    // if (top == -1) {
    //     stackEmpty();
    // }
    return s[*t];
}

int isEmpty(int *t) {
    if (*t == -1) return 1;
    else return 0;
}
```