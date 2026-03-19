//#include <bits/stdc++.h>
//
//using namespace std;
//int head = 0;
//int len = 0;
//int idx[102] = { -1 };
//static void bubbleSort(string s[102], bool ascent, int& head, int len);
//int main() {
//    string method, s[102] = { "" }, sTemp[102] = { "" };
//    cin >> method >> len;
//    cin.ignore();
//    for (int i = 0; i < len; i++) {
//        getline(cin, s[i]);
//        //去空格
//        sTemp[i] = s[i];
//        sTemp[i].erase(remove(sTemp[i].begin(), sTemp[i].end(), ' '), sTemp[i].end());//deepseek说的
//        idx[i] = i + 1;
//    }
//    idx[len - 1] = -1;
//    if (idx[head] == -1) return 0;
//    if (method == "inc") bubbleSort(sTemp, true, head, len);
//    else if (method == "dec")bubbleSort(sTemp, false, head, len);
//    else {
//        //都转为小写
//        for (int i = 0; i < len; i++) {
//            string temp = s[i];  // 使用原始字符串
//            for (char& c : temp) {
//                c = tolower(c);
//            }
//            // 转换后再去空格
//            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
//            sTemp[i] = temp;
//        }
//        if (method == "ncinc") bubbleSort(sTemp, true, head, len);
//        else if (method == "ncdec") bubbleSort(sTemp, false, head, len);
//        else return 0;
//    }
//    int cur = head;
//    while (cur != -1) {
//        cout << s[cur] << endl;
//        cur = idx[cur];
//    }
//    return 0;
//}
//void bubbleSort(string s[102], bool ascent, int& head, int len) {
//    for (int i = 0; i < len; i++) {
//        int pre = head, cur = head, next = idx[cur];
//        while (next != -1) {
//            if ((s[cur] > s[next] && ascent) || (s[cur] < s[next] && !ascent)) {
//                if (pre == cur) {
//                    idx[cur] = idx[next];
//                    idx[next] = cur;
//                    head = next;
//                    pre = head;
//                    cur = idx[pre];
//                    next = idx[cur];
//                }
//                else {
//                    idx[cur] = idx[next];
//                    idx[next] = cur; // pre -> cur -> next   pre -> next -> cur
//                    idx[pre] = next;
//                    pre = next;
//                    cur = idx[pre];
//                    next = idx[cur];
//                }
//            }
//            else {
//                pre = cur;
//                cur = next;
//                next = idx[next];
//            }
//
//        }
//    }
//} 
// 不应该去除所有的空格
#include <bits/stdc++.h>
using namespace std;

int head = 0;
int len = 0;
int idx[102] = { -1 };

static void bubbleSort(string s[102], bool ascent, int& head, int len);

// 去除字符串前后空格的函数
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

int main() {
    string method, s[102] = { "" }, sTemp[102] = { "" };
    cin >> method >> len;
    cin.ignore();

    for (int i = 0; i < len; i++) {
        getline(cin, s[i]);
        // 只去除前后空格，保留中间空格
        sTemp[i] = trim(s[i]);
        idx[i] = i + 1;
    }
    idx[len - 1] = -1;

    if (len == 0) return 0;

    if (method == "inc") {
        bubbleSort(sTemp, true, head, len);
    }
    else if (method == "dec") {
        bubbleSort(sTemp, false, head, len);
    }
    else if (method == "ncinc" || method == "ncdec") {
        // 转为小写（只对去除了前后空格的字符串）
        for (int i = 0; i < len; i++) {
            string temp = sTemp[i];
            for (char& c : temp) {
                c = tolower(c);
            }
            sTemp[i] = temp;
        }
        if (method == "ncinc") {
            bubbleSort(sTemp, true, head, len);
        }
        else {
            bubbleSort(sTemp, false, head, len);
        }
    }
    else {
        return 0;
    }

    int cur = head;
    while (cur != -1) {
        cout << s[cur] << endl;  // 输出原始字符串（包含前后空格）
        cur = idx[cur];
    }
    return 0;
}

void bubbleSort(string s[102], bool ascent, int& head, int len) {
    for (int i = 0; i < len - 1; i++) {
        bool swapped = false;
        int prev = -1;
        int curr = head;

        while (curr != -1 && idx[curr] != -1) {
            int next = idx[curr];
            bool shouldSwap = false;

            if (ascent) {
                shouldSwap = s[curr] > s[next];
            }
            else {
                shouldSwap = s[curr] < s[next];
            }

            if (shouldSwap) {
                swapped = true;

                // 交换 curr 和 next
                if (prev == -1) {
                    // 交换头两个节点
                    idx[curr] = idx[next];
                    idx[next] = curr;
                    head = next;
                    prev = head;
                }
                else {
                    // 交换中间节点
                    idx[curr] = idx[next];
                    idx[next] = curr;
                    idx[prev] = next;
                    prev = next;
                }
                // curr 已经在正确位置
            }
            else {
                prev = curr;
                curr = idx[curr];
            }
        }

        // 如果这一轮没有交换，说明已经有序
        if (!swapped) break;
    }
}