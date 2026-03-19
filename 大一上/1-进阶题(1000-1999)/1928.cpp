#include <bits/stdc++.h>
using namespace std;
int ftoc(int f) {

    return (5.0 / 9.0) * (f - 32);
}
int main()
{
    for (int i = 0; i <= 300; i += 20) {
        cout << i << "    " << (int)ftoc(i) << endl;
    }
    return 0;
}