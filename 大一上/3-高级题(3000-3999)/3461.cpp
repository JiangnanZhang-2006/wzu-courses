#include <iostream>
using namespace std;

int main() {
    long long g1, s1, k1; // 应付的价钱P
    long long g2, s2, k2; // 实付的钱A

    // 读取输入
    scanf("%lld.%lld.%lld %lld.%lld.%lld", &g1, &s1, &k1, &g2, &s2, &k2);

    // 将两个金额都转换为纳特(Knut)
    long long totalP = g1 * 17 * 29 + s1 * 29 + k1;
    long long totalA = g2 * 17 * 29 + s2 * 29 + k2;

    // 计算差值（实付 - 应付）
    long long diff = totalA - totalP;

    // 处理负值情况
    if (diff < 0) {
        printf("-");
        diff = -diff; // 取绝对值
    }

    // 将差值转换回加隆.西可.纳特格式
    long long g3 = diff / (17 * 29);
    diff %= (17 * 29);
    long long s3 = diff / 29;
    long long k3 = diff % 29;

    // 输出结果
    printf("%lld.%lld.%lld\n", g3, s3, k3);

    return 0;
}