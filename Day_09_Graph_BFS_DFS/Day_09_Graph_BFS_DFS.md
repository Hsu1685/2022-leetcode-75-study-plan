# Day 9 Graph/BFS/DFS

## 733. Flood Fill

### 題目
>An image is represented by an m x n integer grid image where image[i][j] represents the pixel value of the image.</br>
You are also given three integers sr, sc, and color. You should perform a flood fill on the image starting from the pixel image[sr][sc].</br>
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
>- n == image[i].length
>- 1 <= m, n <= 50
>- 0 <= image[i][j], color < $2^{16}$
>- 0 <= sr < m
>- 0 <= sc < n

### 過程
- 2022-07-18過程程式碼
```c
#define HEIGHT 6
#define ROW 6
#define COL 6


int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize, int** returnColumnSizes){
    int *dynArr = (int *)calloc(HEIGHT, sizeof(int));

    int **dynArr2D = (int **)malloc(sizeof(int *) * ROW);
    for (int i=0; i<ROW; i++) {
        dynArr2D[i] = (int *)malloc(sizeof(int) * COL);
    }

    dynArr[0] = 3;
    dynArr[1] = 3;
    dynArr[2] = 3;

    dynArr2D[0][0] = imageSize;
    dynArr2D[0][1] = 2;
    dynArr2D[0][2] = 2;

    dynArr2D[1][0] = imageColSize[0];
    dynArr2D[1][1] = imageColSize[1];
    dynArr2D[1][2] = imageColSize[2];

    dynArr2D[2][0] = 2;
    dynArr2D[2][1] = 0;
    dynArr2D[2][2] = 1;

    *returnColumnSizes = dynArr;
    *returnSize = 3;
    return dynArr2D;
}

int do_fill(int x, int y, int **img) {
    if (img[x][y] != color1) {
        return 0;
    }

    // if ()


    return 0;
}

int check_x_range(int x) {

}

int check_y_range(int x) {

}

```