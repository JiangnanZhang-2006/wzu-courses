#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> weight(n);
    vector<int> milk(n, 200);
    
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        if (weight[i + 1] > weight[i]) {
            milk[i + 1] = max(milk[i + 1], milk[i] + 100);
        }
    }
    
    for (int i = n - 1; i > 0; i--) {
        if (weight[i - 1] > weight[i]) {
            milk[i - 1] = max(milk[i - 1], milk[i] + 100);
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i > 0 && weight[i] == weight[i - 1]) {
            int max_milk = max(milk[i], milk[i - 1]);
            milk[i] = max_milk;
            milk[i - 1] = max_milk;
        }
    }
    
    for (int i = 0; i < n - 1; i++) {
        if (weight[i + 1] > weight[i]) {
            milk[i + 1] = max(milk[i + 1], milk[i] + 100);
        }
    }
    
    for (int i = n - 1; i > 0; i--) {
        if (weight[i - 1] > weight[i]) {
            milk[i - 1] = max(milk[i - 1], milk[i] + 100);
        }
    }
    
    for (int i = 0; i < n; i++) {
        cerr << "pos[" << i << "] weight=" << weight[i] << " milk=" << milk[i] << endl;
    }
    
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += milk[i];
    }
    cout << total << endl;
    return 0;
}
