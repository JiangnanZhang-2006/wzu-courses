#include <bits/stdc++.h>
using namespace std;

static bool judge(int input);

int main()
{
    for (int i = 1; i < 100; i++) {
        if (judge(i)) {
            cout << i << ' ';
        }
    }
    cout << endl;
    return 0;
}
static bool judge(int input) {
    if (input / 10 != 0) {
        return input * input % 100 == input;
    }
    else {
        return input * input % 10 == input;
    }
}