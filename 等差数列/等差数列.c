#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long ull;

int my_sort(const void * num1, const void * num2) {
    return *(ull *) num1 - *(ull *)num2; 
}

int gcd(int num1, int num2) {
    return num2 > 0 ? gcd(num2, num1 % num2) : num1;
}

int main() {
    int len;
    register int i, j;
    scanf("%d", &len);
    ull * arr = (ull *) malloc(sizeof(ull) * len);
    for (i = 0; i < len; ++i) {
        scanf("%llu", arr + i);
    }

    // 进行排序
    qsort(arr, len, sizeof(ull), my_sort);
    // 求最大公因数
    for (i = 1, j = 0; i < len; ++i) {
        j = gcd(arr[i] - arr[i - 1], j);
    }

    // 如果公因数为0，说明1是他们的最大公因数
    if (j == 0) {
        printf("%d", len);
    } else { // 就是最大数减去最小数，除以公因数 + 1就是项的多少
        printf("%d", (arr[len - 1] - arr[0]) / j + 1);
    }
    free(arr);
    return 0;
}
