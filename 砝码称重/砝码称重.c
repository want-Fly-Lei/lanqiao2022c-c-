#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100000

int main() {
    int len, i, j, temp;
    scanf("%d", &len);
    // calloc函数赋值为0，懒得重新置为0
    int (* dq) [MAX_SIZE + 1] = (int (*) [MAX_SIZE + 1])calloc (len + 1, sizeof(int) * (MAX_SIZE + 1));

    dq[0][0] = 1;
    for (i = 1; i <= len; ++i) {
        scanf("%d", &temp);
        for (j = 0; j <= MAX_SIZE; ++j) {
            if (dq[i - 1][j]) {
                dq[i][j] = dq[i][j + temp] = dq[i][abs(j - temp)] = 1;
            }
        }
    }
    unsigned int res = 0;
    for (i = 1; i <= MAX_SIZE; ++i) {
        if (dq[len][i]) {
            ++res;
        }
    }
    printf("%u", res);
    free(dq);
    return 0;
}