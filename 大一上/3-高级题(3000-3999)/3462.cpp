#include <bits/stdc++.h>

using namespace std;
int cnt[105];

int main() {
    int len;
    scanf("%d", &len);
    for (int i = 0; i < len; i++) {
        int temp;
        scanf("%d", &temp);
        cnt[temp]++;
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        printf("%d", cnt[temp]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
    return 0;
}