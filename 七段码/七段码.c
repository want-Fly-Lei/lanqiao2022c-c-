#include <stdio.h>
enum code { a = 0, b, c, d, e, f, g };
#define SIZE 7
int arr[SIZE][SIZE + 1] = {
    //第一个数是相连的个数，后面是依次的相邻的色管，加快遍历
    {2, b, f}, // a
    {3, a, c, g}, // b
    {3, b, d, g}, // c
    {2, c, e}, // d
    {3, d, f, g}, // e
    {3, a, e, g}, // f
    {4, b, c, e, f} // g
};
int res = 0; // 结果
int code_choice[SIZE]; // 数码管选择情况
int list[SIZE]; // 数码管的选择情况，以从小到大的形式记录
int find[SIZE]; // 并查集

int find_code(int code) {
    if (find[code] != code) {
        find[code] = find_code(find[code]);
    }
    return find[code];
}

// 处理集合
void deal_with_code() {
    // 避免多次开辟空间
    static int i, j, len1, len2, k1, k2;
    // 统计选择的个数和把code_choice存入到list中，加快后续遍历
    for (i = 0, len1 = 0; i < SIZE; ++i) {
        if (code_choice[i] == 1) {
            list[len1++] = i;
        }
    }

    // 如果只有一个或者缺一个，全部都有，则肯定可以
    if (len1 == 1 || len1 >= SIZE - 1) {
        ++res; // 记录次数加1
        return;
    }
    else if (len1 == 0) { // 一个都不亮，肯定不行
        return;
    }

    //其他情况则需要，重新初始化并查集
    for (i = 0; i < SIZE; ++i) {
        find[i] = i;
    }

    for (i = 0; i < len1; ++i) {
        k1 = list[i];
        len2 = arr[k1][0];
        for (j = 1; j <= len2; ++j) {
            k2 = arr[k1][j];
            // 如果存在相邻，则添加进入集合
            if (code_choice[k2] == 1) {
                find[find_code(k1)] = find_code(k2);
            }
        }
    }

    for (i = 0, k2 = 0; i < len1; ++i) {
        k1 = list[i];
        // 判断有几个集合
        if (find[k1] == k1) {
            ++k2;
        }
    }

    if (k2 == 1) {
        ++res;
    }
}

void choose(int index) {
    // 已经是最后一根选择了
    if (index == SIZE) {
        deal_with_code();
    }
    else {
        code_choice[index] = 0;
        choose(index + 1);
        code_choice[index] = 1;
        choose(index + 1);
    }
}

int main() {
    choose(a);
    printf("%d", res);
    return 0;
}