#include <iostream> 
#include <iomanip>
#include <math.h>

using namespace std;

int main() {
	double x;
	int n;
	cin >> x >> n;
	cout << fixed << setprecision(3) << pow(x, n) << endl;
}