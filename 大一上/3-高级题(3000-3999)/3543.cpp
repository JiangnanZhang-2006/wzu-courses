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
    
    bool changed = true;
    int iterations = 0;
    while (changed && iterations < n * 2) {
        changed = false;
        iterations++;
        
        for (int i = 0; i < n - 1; i++) {
            if (weight[i + 1] > weight[i]) {
                if (milk[i + 1] < milk[i] + 100) {
                    milk[i + 1] = milk[i] + 100;
                    changed = true;
                }
            } else if (weight[i] > weight[i + 1]) {
                if (milk[i] < milk[i + 1] + 100) {
                    milk[i] = milk[i + 1] + 100;
                    changed = true;
                }
            }
        }
        
        for (int i = n - 1; i > 0; i--) {
            if (weight[i - 1] > weight[i]) {
                if (milk[i - 1] < milk[i] + 100) {
                    milk[i - 1] = milk[i] + 100;
                    changed = true;
                }
            } else if (weight[i] > weight[i - 1]) {
                if (milk[i] < milk[i - 1] + 100) {
                    milk[i] = milk[i - 1] + 100;
                    changed = true;
                }
            }
        }
        
        for (int i = 0; i < n - 1; i++) {
            if (weight[i] == weight[i + 1]) {
                int max_milk = max(milk[i], milk[i + 1]);
                if (milk[i] != max_milk) {
                    milk[i] = max_milk;
                    changed = true;
                }
                if (milk[i + 1] != max_milk) {
                    milk[i + 1] = max_milk;
                    changed = true;
                }
            }
        }
        
        for (int i = n - 1; i > 0; i--) {
            if (weight[i] == weight[i - 1]) {
                int max_milk = max(milk[i], milk[i - 1]);
                if (milk[i] != max_milk) {
                    milk[i] = max_milk;
                    changed = true;
                }
                if (milk[i - 1] != max_milk) {
                    milk[i - 1] = max_milk;
                    changed = true;
                }
            }
        }
    }
    
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += milk[i];
    }
    cout << total << endl;
    return 0;
}
