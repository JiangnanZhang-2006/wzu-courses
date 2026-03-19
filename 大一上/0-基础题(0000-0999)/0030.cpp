#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> solution;	//二维的按下情况
vector<vector<bool>> currentBoard;
vector<vector<bool>> board;

vector<vector<bool>> Switch(vector<vector<bool>> board, int pos_x, int pos_y) {
	board[pos_y][pos_x] = !board[pos_y][pos_x];
	if (pos_y - 1 >= 0) {
		board[pos_y - 1][pos_x] = !board[pos_y - 1][pos_x];
	}
	if (pos_x - 1 >= 0) {
		board[pos_y][pos_x - 1] = !board[pos_y][pos_x - 1];
	}
	if (pos_y + 1 < 5) {
		board[pos_y + 1][pos_x] = !board[pos_y + 1][pos_x];
	}
	if (pos_x + 1 < 6) {
		board[pos_y][pos_x + 1] = !board[pos_y][pos_x + 1];
	}
	return board;
}
string toBinaryString(int n) {
	int i = 6;
	string bin_str;
	while (i--) {
		bin_str += (n % 2) ? '1' : '0';
		n /= 2;
	}
	reverse(bin_str.begin(), bin_str.end());
	return bin_str;
}
int main() {
	int t;
	cin >> t;
	for (int l = 0; l < t; l++) {
		board.clear();
		//输入
		for (int j = 0; j < 5; j++) {
			vector<bool> tempVec;
			for (int k = 0; k < 6; k++) {
				bool temp;
				cin >> temp;
				tempVec.push_back(temp);
			}
			board.emplace_back(tempVec);
		}
		for (int i = 0; i < 64; i++) {	
		//遍历所有第一行
			solution.clear();
			string temp = toBinaryString(i);
			vector<bool> tempSolution;	//第一行
			currentBoard = board;
			for (int j = 0; j < 6; j++) {

				if (temp[j] == '0') {
					tempSolution.push_back(false);
				}
				else {
					tempSolution.push_back(true);
					currentBoard = (Switch(currentBoard, j, 0));
				}
			}
			solution.push_back(tempSolution);
			//根据当前行决定下一行的按下情况
			for (int j = 0; j < 4; j++) {
				tempSolution.clear();
				for (int k = 0; k < 6; k++) {
					if (currentBoard[j][k]) {
						tempSolution.push_back(true);
						currentBoard = (Switch(currentBoard, k, j + 1));
					}
					else {
						tempSolution.push_back(false);
					}
				}
				solution.emplace_back(tempSolution);
			}
			//检查是否全为false;
			bool flag = true;
			for (int k = 0; k < 6; k++) {
				if (currentBoard[4][k]) {
					flag = false;
					break;
				}
			}
			if (flag) {
			//输出
				cout << "PUZZLE #" << l + 1 << endl;
				for (auto line : solution) {
					for (int j = 0; j < 6; j++) {
						cout << (j ? " " : "") << (line[j] ? '1' : '0');
					}
					cout << endl;
				}
				break;
			}
		}
		
	}
}