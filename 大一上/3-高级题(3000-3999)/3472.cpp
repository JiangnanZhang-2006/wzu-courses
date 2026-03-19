#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string A, B;
    cin >> A >> B;
    
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());

    if (B.length() < A.length()) {
        B.append(A.length() - B.length(), '0');
    }
    
    string result;
    
    string odd_map = "0123456789JQK";
    
    for (int i = 0; i < B.length(); ++i) {
        int a_digit = (i < A.length()) ? A[i] - '0' : 0;
        int b_digit = B[i] - '0';
        
        if ((i + 1) % 2 == 1) {  
            result += odd_map[(a_digit + b_digit) % 13];
        } else {  
            int diff = (b_digit - a_digit + 10) % 10;
            result += '0' + diff;
        }
    }
    

    reverse(result.begin(), result.end());
    
    cout << result << endl;
    
    return 0;
}