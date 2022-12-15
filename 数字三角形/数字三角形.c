#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value; // 值
    int des; // 左右移动次数
}Node;

int main() {
    int i = 0, j, len;
    int ** arr;
    Node **max;
    scanf("%d", &len);
    arr = (int **)malloc(sizeof(int *) * len);
    max = (Node **)malloc(sizeof(Node *) * len);
    for (i = 0; i < len; ++i) {
        arr[i] = (int *)malloc(sizeof(int) * (i + 1));
        max[i] = (Node *)malloc(sizeof(Node) * (i + 1));
        for (j = 0; j <= i; ++j) {
            scanf("%d", &arr[i][j]);
            // max[i][j].des = 0;
        }
    }

    max[0][0].value = arr[0][0];
    max[0][0].des = 0;
    for (i = 1; i < len; ++i) {
        // 第一个数只能等于上面
        max[i][0].value = max[i - 1][0].value + arr[i][0];
        max[i][0].des = max[i - 1][0].des - 1; // 向下走为减
        for (j = 1; j < i; ++j) {
            if (max[i - 1][j].value > max[i - 1][j - 1].value) {
                max[i][j].value = arr[i][j] + max[i - 1][j].value;
                max[i][j].des = max[i - 1][j].des - 1;
            } else {
                max[i][j].value = arr[i][j] + max[i - 1][j - 1].value;
                max[i][j].des = max[i - 1][j - 1].des + 1;
            }
        }
        // 最后一个只能来源于右上角
        max[i][j].value = arr[i][j] + max[i - 1][j - 1].value;
        max[i][j].des = max[i - 1][j - 1].des + 1;
    }

    // for (i = 0; i < len; ++i) {
    //     for (j = 0; j <= i; ++j) {
    //         printf("%d ", max[i][j]);
    //     }
    //     putchar('\n');
    // }

    int sum = 0;
    j = len - 1;
    for (i = 0; i < len; ++i) {
        if (max[j][i].des > -2 && max[j][i].des < 2 && max[j][i].value > sum) {
            sum = max[j][i].value;
        }
    }
    printf("%d", sum);
    for (i = 0; i < len; ++i) {
        free(arr[i]);
        free(max[i]);
    }
    free(arr);
    free(max);
    return 0;
}