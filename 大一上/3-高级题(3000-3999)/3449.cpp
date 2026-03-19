#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> linked_list(100005, {-1, -1}); 
int main() {
	int head, len, k;
	if (!(cin >> head >> len >> k)) return 0;

	for (int i = 0; i < len; ++i) {
		int addr, val, next;
		cin >> addr >> val >> next;
		linked_list[addr] = {val, next};
	}

	// build the actual list starting from head
	vector<pair<int, int>> actual_list;
	int p = head;
	while (p != -1) {
		actual_list.push_back({p, linked_list[p].first});
		p = linked_list[p].second;
	}

	// reverse in groups of k
	for (size_t i = 0; i + k <= actual_list.size(); i += k) {
		reverse(actual_list.begin() + i, actual_list.begin() + i + k);
	}

	// output the resulting list
	for (size_t i = 0; i < actual_list.size(); ++i) {
		int addr = actual_list[i].first;
		int val = actual_list[i].second;
		int nextAddr = (i + 1 < actual_list.size()) ? actual_list[i + 1].first : -1;
		printf("%05d %d ", addr, val);
		if (nextAddr != -1) {
			printf("%05d\n", nextAddr);
		} else {
			printf("-1\n");
		}
	}

	return 0;
}