#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long m;
    cin >> n >> m;
    vector<long long> price(n);
    
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    
    long long count = 0;
    long long sum = 0;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        sum += price[right];
        
        while (sum > m && left <= right) {
            sum -= price[left];
            left++;
        }
        
        count += (right - left + 1);
    }
    
    cout << count << endl;
    return 0;
}

