#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    string s[102] = { "" };
    int idx[102] = { -1 };
    cin >> t;
    if (t < 1) return 0;
    for (int i = 0; i < t; i++) {
        cin >> s[i];
        idx[i] = i + 1;
    }
    int head = 0;
    idx[t - 1] = -1;
    for (int i = 0; i < t; i++) {
        int pre = head, cur = head, next = idx[cur];
        while (next != -1) {
            if (s[cur] > s[next]) {
                if (pre == cur) {
                    idx[cur] = idx[next];
                    idx[next] = cur;
                    head = next;
                    pre = head;
                    cur = idx[pre];
                    next = idx[cur];
                }
                else {
                    idx[cur] = idx[next];
                    idx[next] = cur; // pre -> cur -> next   pre -> next -> cur
                    idx[pre] = next;
                    pre = next;
                    cur = idx[pre];
                    next = idx[cur];
                }
            }
            else {
                pre = cur;
                cur = next;
                next = idx[next];
            }

        }
    }
    //output
    int cur = head;
    while (cur != -1) {
        cout << s[cur] << endl;
        cur = idx[cur];
    }
    return 0;
}