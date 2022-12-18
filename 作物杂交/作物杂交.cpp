#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <vector> // 不用vector太麻烦了
using namespace std;
#define MAX_SIZE 2000
int len, num_of_seed_have, num_of_choice_have, target;
int * growth_time; // 种植时间
int * get_seed_time; // 获取种子的时间
int * list; // 是否获取到种子
typedef struct node {
    public:
    int parent_a;
    int parent_b;
    int son;
    int g_time;
    void set_time() { // 计算获取到种子的时间时间
        g_time = growth_time[parent_a] > growth_time[parent_b] ? growth_time[parent_a] : growth_time[parent_b];
    }
}Node;
Node * node_ptr; // 可选择的交杂组合记录
vector<int> ve[MAX_SIZE + 1];

int get_target(int index) {
    if (list[index] == 1) {
        return get_seed_time[index];
    }
    // 迭代器
    // vector<int>::iterator begin, end;
    Node node;
    int temp, res = INT_MAX;
    int i, j; // vector使用传统的for更快
    for (i = 0, j = ve[index].size(); i < j; ++i) {
        node = node_ptr[ve[index][i]];
        temp = max(get_target(node.parent_a), get_target(node.parent_b)) + node.g_time;
        if (temp < res) {
            res = temp;
        }
    }
    // 进行记录避免对此重复遍历
    list[index] = 1;
    get_seed_time[index] = res;
    return res;
}

int main() {
    scanf("%d %d %d %d", &len, &num_of_seed_have, &num_of_choice_have, &target);
    register int i;
    int temp1, temp2, temp3;
    growth_time = (int *) malloc(sizeof(int) * (len + 1));
    list = (int *) malloc (sizeof(int) * (len + 1));
    get_seed_time = (int *) malloc (sizeof(int) * (len + 1));
    node_ptr = (Node *) malloc (sizeof(Node) * num_of_choice_have);
    for (i = 1; i <= len; ++i) {
        scanf("%d", growth_time + i);
        list[i] = 0;
    }

    for (i = 0; i < num_of_seed_have; ++i) {
        scanf("%d", &temp1);
        list[temp1] = 1;
        get_seed_time[temp1] = 0;
    }

    for (i = 0; i < num_of_choice_have; ++i) {
        scanf("%d %d %d", &temp1, &temp2, &temp3);
        node_ptr[i].parent_a = temp1;
        node_ptr[i].parent_b = temp2;
        node_ptr[i].son = temp3;
        node_ptr[i].set_time();
        ve[temp3].push_back(i);
    }

    // for (i = 1; i <= target; ++i) {
    //     if (list[i] == 1) {
    //         continue;
    //     }
    //     get_target(i);
    // }
    // 种子其他案例居然可以两个大的杂交小的，所以只能深度遍历
    get_target(target);
    
    printf("%d", get_seed_time[target]);
    free(growth_time);
    free(list);
    free(node_ptr);
    free(get_seed_time);
    return 0;
}
