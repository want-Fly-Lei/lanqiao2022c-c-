#include <stdio.h>

int main() {
    // 由题目直到最大长度就是距离左侧或者右侧距离的两倍
    int len, i, temp, right, left;
    scanf("%d", &len);
    for(i = 1; i <= len; ++i) {
			left = i - 1; // 距离左侧长度
			right = len - i; // 距离右侧长度
			temp = (left > right? left : right) * 2;
            printf("%d\n", temp);
		}
    return 0;
}