#include <iostream>
#include <vector>

using namespace std;

void print(int sum);

int main() {
	vector<int> arr;
	char temp;
	while (temp = getchar()) {
		if (temp == '\n') break;
		arr.emplace_back(temp - '0');
	}
	int sum = 0;
	for (int i : arr) sum += i;
	print(sum);
	cout << endl;
}

void print(int sum)
{
	if (sum / 10 != 0) {
		print(sum / 10);

		cout << ' ';
		if (sum % 10 == 0) {
			cout << "ling";
		}
		else if (sum % 10 == 1) {
			cout << "yi";
		}
		else if (sum % 10 == 2) {
			cout << "er";
		}
		else if (sum % 10 == 3) {
			cout << "san";
		}
		else if (sum % 10 == 4) {
			cout << "si";
		}
		else if (sum % 10 == 5) {
			cout << "wu";
		}
		else if (sum % 10 == 6) {
			cout << "liu";
		}
		else if (sum % 10 == 7) {
			cout << "qi";
		}
		else if (sum % 10 == 8) {
			cout << "ba";
		}
		else if (sum % 10 == 9) {
			cout << "jiu";
		}
	}
	else {
		if (sum % 10 == 0) {
			cout << "ling";
		}
		else if (sum % 10 == 1) {
			cout << "yi";
		}
		else if (sum % 10 == 2) {
			cout << "er";
		}
		else if (sum % 10 == 3) {
			cout << "san";
		}
		else if (sum % 10 == 4) {
			cout << "si";
		}
		else if (sum % 10 == 5) {
			cout << "wu";
		}
		else if (sum % 10 == 6) {
			cout << "liu";
		}
		else if (sum % 10 == 7) {
			cout << "qi";
		}
		else if (sum % 10 == 8) {
			cout << "ba";
		}
		else if (sum % 10 == 9) {
			cout << "jiu";
		}
	}
}
