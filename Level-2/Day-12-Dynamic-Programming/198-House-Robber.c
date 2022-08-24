#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rob(int*, int);
int robLeft(int, int, int*);
int robRight(int, int, int*);
int findMax(int, int, int*);
int findMax2(int, int, int);

int main() {
    // int array[] = {6,3,10,8,2,10,3,5,10,5,3};
    // int array[] = {2,7,9,3,1};
    int array[] = {183, 219, 57,  193, 94,  233, 202, 154, 65,  240,
                   97,  234, 100, 249, 186, 66,  90,  238, 168, 128,
                   177, 235, 50,  81,  185, 165, 217, 207, 88,  80,
                   112, 78,  135, 62,  228, 247, 211};
    // int result = rob(array, 5);
    int result = rob(array, 37);
    printf("output: %d", result);

    return 0;
}

int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];

    if (numsSize == 2) {
        if (nums[0] > nums[1]) {
            return nums[0];
        } else {
            return nums[1];
        }
    }

    if (numsSize == 3) {
        if (nums[1] > (nums[0] + nums[2])) {
            return nums[1];
        } else {
            return nums[0] + nums[2];
        }
    }

    if (numsSize == 4) {
        if ((nums[0] + nums[2]) > (nums[1] + nums[3])) {
            if (nums[2] > nums[3]) {
                return nums[0] + nums[2];
            } else {
                return nums[0] + nums[3];
            }
        } else {
            if (nums[0] > nums[1]) {
                return nums[0] + nums[3];
            } else {
                return nums[1] + nums[3];
            }
        }
    }

    int index1 = numsSize / 2;
    int result1 = robLeft(0, index1 - 2, nums) +
                  robRight(index1 + 2, numsSize - 1, nums) + nums[index1];
    // int result1 = 1;

    int index2 = (numsSize / 2) - 1;
    int result2 = robLeft(0, index2 - 2, nums) +
                  robRight(index2 + 2, numsSize - 1, nums) + nums[index2];
    // int result2 = 2;

    int index3 = (numsSize / 2) + 1;
    int result3 = robLeft(0, index3 - 2, nums) +
                  robRight(index3 + 2, numsSize - 1, nums) + nums[index3];
    // int result3 = 3;

    // if (result1 > result2) return result1;
    // else return result2;
    // return max_index;
    // return index1;
    // return result3;
    // return numsSize;
    return findMax2(result1, result2, result3);
}

int robLeft(int s, int e, int* nums) {
    // if ((s == e) || (e < s)) {
    // if (s >= e) {
    if (((e - s) < 0) || (e < 0)) {
        return 0;
    }

    if ((e - s) == 0) {
        return nums[s];
    }

    if ((e - s) == 1) {
        if (nums[s] > nums[s + 1]) {
            return nums[s];
        } else {
            return nums[s + 1];
        }
    }

    if ((e - s) == 2) {
        if (nums[s + 1] > (nums[s] + nums[s + 2])) {
            return nums[s + 1];
        } else {
            return nums[s] + nums[s + 2];
        }
    }

    if ((e - s) == 3) {
        return findMax2((nums[s] + nums[s + 2]), (nums[s + 1] + nums[s + 3]),
                        (nums[s] + nums[s + 3]));
    }

    // if ((e - s) == 4) {
    //     if ((nums[s] + nums[s + 2]) > (nums[s + 1] + nums[s + 3])) {
    //         if (nums[s + 2] > nums[s + 3]) {
    //             return nums[s] + nums[s + 2];
    //         } else {
    //             return nums[s] + nums[s + 3];
    //         }
    //     } else {
    //         if (nums[s] > nums[s + 1]) {
    //             return nums[s] + nums[s + 3];
    //         } else {
    //             return nums[s + 1] + nums[s + 3];
    //         }
    //     }
    // }

    // int max_index = findMax(s, e-1, nums);
    int left1 = s + ((e - s + 1) / 2);
    int left_result1 = robLeft(s, left1 - 2, nums) +
                       robRight(left1 + 2, e, nums) + nums[left1];

    int left2 = s + ((e - s + 1) / 2) - 1;
    int left_result2 = robLeft(s, left2 - 2, nums) +
                       robRight(left2 + 2, e, nums) + nums[left2];

    int left3 = s + ((e - s + 1) / 2) + 1;
    int left_result3 = robLeft(s, left3 - 2, nums) +
                       robRight(left3 + 2, e, nums) + nums[left3];

    // return robLeft(s, max_index-1, nums) + robRight(max_index+1, e, nums) +
    // nums[max_index];
    return findMax2(left_result1, left_result2, left_result3);
    // return result3;
}

int robRight(int s, int e, int* nums) {
    // if (s >= e) {
    // if ((e - s) < 0) {
    if (((e - s) < 0) || (e < 0)) {
        return 0;
    }

    if ((e - s) == 0) {
        return nums[e];
    }

    if ((e - s) == 1) {
        if (nums[s] > nums[s + 1]) {
            return nums[s];
        } else {
            return nums[s + 1];
        }
    }

    if ((e - s) == 2) {
        if (nums[s + 1] > (nums[s] + nums[s + 2])) {
            return nums[s + 1];
        } else {
            return nums[s] + nums[s + 2];
        }
    }

    if ((e - s) == 3) {
        return findMax2((nums[s] + nums[s + 2]), (nums[s + 1] + nums[s + 3]),
                        (nums[s] + nums[s + 3]));
    }

    // if ((e - s) == 4) {
    //     if ((nums[s + 1] + nums[s + 3]) > (nums[s + 2] + nums[s + 4])) {
    //         if (nums[s + 3] > nums[s + 4]) {
    //             return nums[s + 1] + nums[s + 3];
    //         } else {
    //             return nums[s + 1] + nums[s + 4];
    //         }
    //     } else {
    //         if (nums[s + 1] > nums[s + 2]) {
    //             return nums[s + 1] + nums[s + 4];
    //         } else {
    //             return nums[s + 2] + nums[s + 4];
    //         }
    //     }
    // }

    // int max_index = findMax(s+1, e, nums);
    int right1 = s + ((e - s + 1) / 2);
    int right_result1 = robLeft(s, right1 - 2, nums) +
                        robRight(right1 + 2, e, nums) + nums[right1];

    int right2 = s + ((e - s + 1) / 2) - 1;
    int right_result2 = robLeft(s, right2 - 2, nums) +
                        robRight(right2 + 2, e, nums) + nums[right2];

    int right3 = s + ((e - s + 1) / 2) + 1;
    int right_result3 = robLeft(s, right3 - 2, nums) +
                        robRight(right3 + 2, e, nums) + nums[right3];

    // return robLeft(s, max_index-1, nums) + robRight(max_index+1, e, nums) +
    // nums[max_index];
    return findMax2(right_result1, right_result2, right_result3);
    // return result3;
}

int findMax(int s, int e, int* nums) {
    int i;
    int max_index = s;
    int max_value = nums[s];

    for (i = s + 1; i <= e; i++) {
        if (nums[i] > max_value) {
            max_value = nums[i];
            max_index = i;
        }
    }
    return max_index;
}

int findMax2(int v1, int v2, int v3) {
    if (v1 > v2) {
        if (v1 > v3) {
            return v1;
        } else {
            return v3;
        }
    } else {
        if (v2 > v3) {
            return v2;
        } else {
            return v3;
        }
    }
}