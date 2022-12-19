#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef long long LL;
const int N = 5005;
int arr[N][N];
const int mod = 1e9 + 7;
char str[N];
int len;
LL get() {
    memset(arr, 0, sizeof(arr));
    arr[0][0] = 1;
    int i, j;
    for (i = 1; i <= len; ++i) {
        if (str[i - 1] == '(') {
            for (j = 1; j <= len; ++j) {
                arr[i][j] = arr[i - 1][j - 1];
            }
        } else {
            arr[i][0] = (arr[i - 1][1] + arr[i - 1][0]) % mod;
            for (j = 1; j <= len; ++j) {
                arr[i][j] = (arr[i - 1][j + 1] + arr[i][j - 1]) % mod;
            }
        }
    }
    for (i = 0; i <= len; ++i) {
        if (arr[len][i]) {
            return arr[len][i];
        }
    }
    return -1;
}

int main() {
    scanf("%s", str);
    len = strlen(str);
    register int i, j;
    LL res1 = get();	//记录左括号的插入方案数
    //将原序列逆置
    register char ch;
    for (i = 0, j = len - 1; i < j; ++i, --j) {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }

    for (i = 0; i < len; ++i) {
        if (str[i] == ')') {
            str[i] = '(';
        } else {
            str[i] = ')';
        }
    }
    LL res2 = get();	//记录右括号的插入方案数
    printf("%lld", (res1 * res2) % mod);
    return 0;
}
