#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// 求最大公约数
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 分数结构体
struct Fraction {
    long long numerator;
    long long denominator;

    Fraction(long long n = 0, long long d = 1) : numerator(n), denominator(d) {
        simplify();
    }

    // 化简分数
    void simplify() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        long long g = gcd(abs(numerator), denominator);
        numerator /= g;
        denominator /= g;
    }

    // 转换为字符串表示
    string toString() const {
        if (denominator == 0) return "Inf";
        if (numerator == 0) return "0";

        string result;
        long long num = abs(numerator);
        long long den = denominator;
        bool negative = (numerator < 0);

        // 整数部分
        long long integer = num / den;
        num = num % den;

        if (integer > 0) {
            result += to_string(integer);
            if (num > 0) {
                result += " " + to_string(num) + "/" + to_string(den);
            }
        }
        else {
            if (num > 0) {
                result += to_string(num) + "/" + to_string(den);
            }
        }

        // 处理负数
        if (negative) {
            result = "(-" + result + ")";
        }

        return result;
    }
};

// 四则运算
Fraction add(const Fraction& a, const Fraction& b) {
    long long num = a.numerator * b.denominator + b.numerator * a.denominator;
    long long den = a.denominator * b.denominator;
    return Fraction(num, den);
}

Fraction subtract(const Fraction& a, const Fraction& b) {
    long long num = a.numerator * b.denominator - b.numerator * a.denominator;
    long long den = a.denominator * b.denominator;
    return Fraction(num, den);
}

Fraction multiply(const Fraction& a, const Fraction& b) {
    long long num = a.numerator * b.numerator;
    long long den = a.denominator * b.denominator;
    return Fraction(num, den);
}

Fraction divide(const Fraction& a, const Fraction& b) {
    if (b.numerator == 0) {
        return Fraction(1, 0); // 表示无穷大
    }
    long long num = a.numerator * b.denominator;
    long long den = a.denominator * b.numerator;
    return Fraction(num, den);
}

int main() {
    long long a1, b1, a2, b2;
    scanf("%lld/%lld %lld/%lld", &a1, &b1, &a2, &b2);

    Fraction f1(a1, b1);
    Fraction f2(a2, b2);

    string s1 = f1.toString();
    string s2 = f2.toString();

    // 加法
    cout << s1 << " + " << s2 << " = " << add(f1, f2).toString() << endl;
    // 减法
    cout << s1 << " - " << s2 << " = " << subtract(f1, f2).toString() << endl;
    // 乘法
    cout << s1 << " * " << s2 << " = " << multiply(f1, f2).toString() << endl;
    // 除法
    string divResult = divide(f1, f2).toString();
    cout << s1 << " / " << s2 << " = " << divResult << endl;

    return 0;
}