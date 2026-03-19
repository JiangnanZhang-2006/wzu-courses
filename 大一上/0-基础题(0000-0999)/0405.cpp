#include <iostream>

using namespace std;
int cnt = 1;
static void judge(int cur, int pre);

int main() {
    int t;
    cin >> t;
    while (t--) {
        cnt = 1;
        int n;
        cin >> n;
        judge(1, n);
        cout << cnt << endl;
    }
}

void judge(int cur, int pre) {
    if (cur > 1 && cur <= pre / 2) {
        judge(1, cur);
    }
    if (cur <= pre / 2) {
        ++cnt;
        //cout << cur << '-' << pre << ' ';
        return judge(++cur, pre);
    }
    return;

}