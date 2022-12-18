#include <stdio.h>
#include <stdlib.h>
#include <vector> // vector还是方便得多
using namespace std;
using uint = unsigned int;
vector<int> * ve;
int len;

// 自定义max，使用c++自带的max是泛型，性能会差一点
static uint max(const uint num1, const uint num2) {
    return num1 > num2 ? num1 : num2;
}

uint dfs(int node) {
    uint size = ve[node].size();
    // 判断是否是叶节点
    if (size == 0) {
        return 1;
    }
    uint res, i;
    vector<int> temp = ve[node];
    // 寻找最深节点
    for (i = 0, res = 0; i < size; ++i) {
        res = max(res, dfs(temp[i]));
    }
    return size + res;
}

int main() {
    scanf("%d", &len);
    ve = (vector<int> *) malloc (sizeof(vector<int>) * (len + 1 ));
    int i, temp;
    for (i = 2; i <= len; ++i) {
        scanf("%d", &temp);
        ve[temp].push_back(i); // 把temp的子节点添加进去
    }
    printf("%u", dfs(1) - 1);
    free(ve);
    return 0;
}