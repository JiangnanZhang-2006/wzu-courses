#include <bits/stdc++.h>

using namespace std;

int main() {
	vector<int> targetArr;
	vector<int> insertionArr;
	vector<int> mergeArr;
	int n;
	bool isInsertion = false, isMerge = false;

	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		insertionArr.push_back(temp);
		mergeArr.push_back(temp);
	}
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		targetArr.push_back(temp);
	}
	//ins
	for (int i = 1; i < n; i++) {
		int temp = insertionArr[i];
		int j = i - 1;
		while (j >= 0 and temp < insertionArr[j]) {
			insertionArr[j + 1] = insertionArr[j];
			j--;
		}
		insertionArr[j + 1] = temp;
		if (isInsertion) {
			for (int i = 0; i < n; i++) {
				cout << (i == 0? "":" ") << insertionArr[i];
			}
			break;
		}
		if (insertionArr == targetArr) {
			cout << "Insertion Sort\n";
			isInsertion = true;
		}
	}
	//merge
	if (!isInsertion) {
		cout << "Merge Sort\n";
		int step = 2;
		while (!isMerge) {
			if (mergeArr == targetArr) {
				isMerge = true;
			}
			for (int i = 0; i < n; i += step) {
				int end = min(i + step, n);
				sort(mergeArr.begin() + i, mergeArr.begin() + end);
			}

			step = step * 2;
			if (isMerge) {
				for (int i = 0; i < n; i++) {
					cout << (i == 0 ? "" : " ") << mergeArr[i];
				}
				break;
			}
		}
	}
	cout << endl;
}