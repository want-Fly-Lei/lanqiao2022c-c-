#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
// 长度
#define SIZE 21
// 最大数字
#define MAX_NUM (1 << SIZE) 
typedef unsigned long long ull;

bool is_union[SIZE][SIZE]; // 是否连通
ull dp[1 << SIZE][SIZE];
int gcd(int num1, int num2) {
    return num2 == 0 ? num1 : gcd(num2, num1 % num2);
}

int main() {
    // 貌似这些都要超时，把结果输出即可
    // puts("881012367360");
    // time_t start = clock(), end;
    ull res = 0;
    register int i, j;
    // 存边
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (gcd(i + 1, j + 1) == 1) { // 两个数互质
                is_union[i][j] = is_union[j][i] = true;
            } else {
                is_union[i][j] = is_union[j][i] = false;
            }
        }
    }

    dp[1][0] = 1;
    int k;
    for (i = 1; i < MAX_NUM; ++i) {
        for (j = 0; j < SIZE; ++j) {
            // 如果当前状态中不存在楼j，跳过 
            if (!(i >> j & 1)) {
                continue;
            }

            // 寻找从楼j能够到达的下一栋楼
            for (k = 0; k < SIZE; ++k) {
                //楼k已经访问或者j到k无边，跳过 
                if ((i >> k & 1) || !is_union[j][k]) {
                    continue;
                }
                dp[i + (1 << k)][k] += dp[i][j];
            }
        }
    }

    //将以i为结尾点的回路求和 
    for (i = 0; i < SIZE; ++i) {
        res += dp[MAX_NUM - 1][i];
    }

    printf("%llu", res);
    // end = clock();
    // printf("共耗时:%lldms", end - start);
    return 0;
}
