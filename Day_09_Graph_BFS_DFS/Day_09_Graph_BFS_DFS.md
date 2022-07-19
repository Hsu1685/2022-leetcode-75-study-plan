# Day 9 Graph/BFS/DFS

## 733. Flood Fill

### 題目
>An image is represented by an m x n integer grid image where image\[ i ][ j ] represents the pixel value of the image.</br>
You are also given three integers sr, sc, and color. You should perform a flood fill on the image starting from the pixel image\[ sr ][ sc ].</br>
To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with color.</br>
Return the modified image after performing the flood fill.</br>
```c
//**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */


int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize, int** returnColumnSizes){

}
```
>Constraints:
>- m == image.length
>- n == image[ i ].length
>- 1 <= m, n <= 50
>- 0 <= image\[ i ][ j ], color < $2^{16}$
>- 0 <= sr < m
>- 0 <= sc < n

### 過程
- 想法是利用遞迴，每次檢查位置是不是要改變的顏色，接著改變顏色，再依序確認右方、上方、左方、下方位置是否超出範圍，若範圍合理則代入新位置再呼叫1次函數
- 2022-07-19 Submissions
    ```c
    #define ROW 50
    #define COL 50

    int color1, color2;
    int a_limit, b_limit;

    int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize, int** returnColumnSizes){
        int **dynArr2D = (int **)malloc(sizeof(int *) * ROW);

        for (int i=0; i<ROW; i++) {
            dynArr2D[i] = (int *)malloc(sizeof(int) * COL);
        }

        color1 = image[sr][sc];
        color2 = color;

        a_limit = imageSize;
        b_limit = imageColSize[0];

        for (int i=0; i<a_limit; i++) {
            for (int j=0; j<b_limit; j++) {
                dynArr2D[i][j] = image[i][j];
            }
        }

        if (color1 != color2) {
            do_fill(sr, sc, dynArr2D);
        }

        *returnColumnSizes = imageColSize;
        *returnSize = imageSize;
        return dynArr2D;
    }

    void do_fill(int a, int b, int **img) {
        if (img[a][b] != color1) {
            return;
        }
        img[a][b] = color2;

        if (check_b_range(b + 1)) {  // 向右塗滿
            do_fill(a, b + 1, img);
        }

        if (check_a_range(a - 1)) {  // 向上塗滿
            do_fill(a - 1, b, img);
        }

        if (check_b_range(b - 1) == 1) {  // 向左塗滿
            do_fill(a, b - 1, img);
        }

        if (check_a_range(a + 1)) {  // 向下塗滿
            do_fill(a + 1, b, img);
        }
    }

    int check_a_range(int a) {
        if ((a < a_limit) && (a >= 0)) {
            return 1;
        } else {
            return 0;
        }
    }

    int check_b_range(int b) {
        if ((b < b_limit) && (b >= 0)) {
            return 1;
        } else {
            return 0;
        }
    }

    ```

- 第二想法是利用迴圈及Queue進行計算，取第一個位置(sr, sc)，放入Queue再進入迴圈 (進行到Queue空為止)。迴圈裡：取出Queue判斷該位置要不要變更顏色，若要變更再判斷向4方向前進是否合理 (未超出範圍)，再把合理的4方向位置加入Queue，結束這一輪迴圈；若該位置不需要變更顏色 (可能是已經變更過了可能是要變更成的顏色和現在顏色相同)，則直接結束迴圈。接著重複至Queue空為止。
```c
```


---
## 200. Number of Islands

### 題目
> Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.</br>
An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.</br>

```c
int numIslands(char** grid, int gridSize, int* gridColSize){

}
```

>Constraints:
>- m == grid.length
>- n == grid[ i ].length
>- 1 <= m, n <= 300
>- grid\[ i ][ j ] is '0' or '1'.

### 過程
- 想法是產生一個同樣大小的ARRAY標記該位置是否檢查過，從頭(0, 0)開始若是LAND則COUNTER++，接著找出所有相鄰的LAND並標記是否檢查過，若是SEA則找出所有相鄰的SEA並標記，再來找到下一個未檢查過的位置(i, j)重複過程直到所有的位置都檢查過
- 2022-07-19 Submissions
    ```c
    int total, row, col;
    int **dynArr2D;

    int numIslands(char** grid, int gridSize, int* gridColSize){
        int number = 0, counter = 0;

        total = gridSize * gridColSize[0];
        row = gridSize;
        col = gridColSize[0];

        dynArr2D = (int **)malloc(sizeof(int *) * gridSize);
        for (int i=0; i<gridSize; i++) {
            dynArr2D[i] = (int *)calloc(gridColSize[0], sizeof(int));
        }

        while (number != -1) {
            char is_land = grid[number / col][number % col];

            if (is_land == 49) {
                counter++;
            }

            find_adjacent_area(number / col, number % col, grid, is_land);
            number = find_unchecked(number);
        }
        return counter;
    }

    int find_unchecked(int num) {
        int ret = -1;
        for (int i=num; i<total; i++) {
            if (dynArr2D[i / col][i % col] == 0) {
                ret = i;
                break;
            }
        }
        return ret;
    }

    void find_adjacent_area(int a, int b, char **map, char is_land) {
        if (map[a][b] != is_land) {
            return;
        }
        dynArr2D[a][b] = 1;  // 標記已檢查過

        if (check_b_range(b + 1) && (dynArr2D[a][b + 1] != 1)) {  // 向右塗滿
            find_adjacent_area(a, b + 1, map, is_land);
        }

        if (check_a_range(a - 1) && (dynArr2D[a - 1][b] != 1)) {  // 向上塗滿
            find_adjacent_area(a - 1, b, map, is_land);
        }

        if (check_b_range(b - 1) && (dynArr2D[a][b - 1] != 1)) {  // 向左塗滿
            find_adjacent_area(a, b - 1, map, is_land);
        }

        if (check_a_range(a + 1) && (dynArr2D[a + 1][b] != 1)) {  // 向下塗滿
            find_adjacent_area(a + 1, b, map, is_land);
        }
    }

    int check_a_range(int a) {
        if ((a < row) && (a >= 0)) {
            return 1;
        } else {
            return 0;
        }
    }

    int check_b_range(int b) {
        if ((b < col) && (b >= 0)) {
            return 1;
        } else {
            return 0;
        }
    }
    ```