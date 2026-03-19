//#include <stdio.h>
//#include <iostream>
//
//using namespace std;
//
//int main() {
//    int flag = 1, t;
//    cin >> t;
//    while (t--) {
//        char s1[1000] = "\0", s2[1000] = "\0";
//        gets(s1);
//        gets(s2);
//        for (int i = 0; s1[i] != '\0'; i++) {
//            if (s1[i] != s2[i]) {
//                cout << (int)s1[i] - (int)s2[i];
//                flag = 0;
//            }
//        }
//        if (flag) cout << '0';
//        cout << endl;
//
//    }
//    return 0;
//}
#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // 读取换行符

    for (int i = 0; i < n; i++) {
        char s1[1001], s2[1001];

        // 使用fgets读取字符串，并检查返回值
        if (fgets(s1, 1001, stdin) == NULL) {
            // 处理读取错误
            continue;
        }
        if (fgets(s2, 1001, stdin) == NULL) {
            // 处理读取错误
            continue;
        }

        // 去除换行符
        s1[strcspn(s1, "\n")] = '\0';
        s2[strcspn(s2, "\n")] = '\0';

        int j = 0;
        // 逐个字符比较
        while (s1[j] != '\0' && s2[j] != '\0' && s1[j] == s2[j]) {
            j++;
        }

        // 计算第一个不同字符的差值
        int result = s1[j] - s2[j];
        printf("%d\n", result);
    }

    return 0;
}