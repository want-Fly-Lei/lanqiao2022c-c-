#include <stdio.h>
#include <string.h>

int main() {
    // puts("������Ž�����");
    char num[80] = "2022";
    unsigned long long res = 0;
    // scanf("%s", &num); 
    int len = strlen(num);
    for (int i = 0; i < len; ++i) {
        res = res * 9 + num[i] - '0';
    }
    printf("%llu",res);
    return 0;
}
