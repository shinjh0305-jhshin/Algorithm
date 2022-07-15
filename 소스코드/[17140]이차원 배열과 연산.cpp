#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int rows, cols;
int rawdata[2][103][103];
int targetRow, targetCol, target;
int current = 0, after = 1;

void initialize() {
	rows = cols = 3;
	cin >> targetRow >> targetCol >> target;
	targetRow--; targetCol--;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> rawdata[current][i][j];
		}
	}
}

void operateR() {
	vector<int> temp;
	vector<pair<int, int>> tempPair; //count, number
	const auto& curData = rawdata[current];

	memset(rawdata[after], 0, sizeof(rawdata[after])); //���� �迭 0���� �ʱ�ȭ

	int nextcols = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (curData[i][j]) temp.push_back(curData[i][j]); //0������ �� row������ ��� ���ڸ� �ִ´�
		}
		sort(temp.begin(), temp.end());  //������������ �����Ѵ�

		int sz_temp = temp.size();
		int curNum = temp[0], curcnt = 1;

		for (int k = 1; k < sz_temp; k++) {
			if (temp[k] != curNum) {
				tempPair.push_back({ curcnt, curNum});
				curNum = temp[k]; curcnt = 1;
			}
			else curcnt++;
		}
		tempPair.push_back({ curcnt, curNum }); //������ ������ �־��ش�

		sort(tempPair.begin(), tempPair.end()); //����Ƚ�� -> ���� ������������ �����Ѵ�

		int x = 0;
		for (const auto it : tempPair) {
			if (x >= 100) break; //ù 100���� ������ �������� ������.
			rawdata[after][i][x++] = it.second;
			rawdata[after][i][x++] = it.first;
		}

		nextcols = max(nextcols, x); //������ row�� ũ�⸦ �˾ƺ���
		tempPair.clear();
		temp.clear();
	}

	swap(after, current);
	cols = nextcols;
}

void operateC() {
	vector<int> temp;
	vector<pair<int, int>> tempPair; //count, number
	const auto& curData = rawdata[current];

	memset(rawdata[after], 0, sizeof(rawdata[after])); //���� �迭 0���� �ʱ�ȭ

	int nextrows = 0;
	for (int j = 0; j < cols; j++) {
		for (int i = 0; i < rows; i++) {
			if (curData[i][j]) temp.push_back(curData[i][j]); //0������ �� col������ ��� ���ڸ� �ִ´�
		}
		sort(temp.begin(), temp.end());  //������������ �����Ѵ�

		int sz_temp = temp.size();
		int curNum = temp[0], curcnt = 1;

		for (int k = 1; k < sz_temp; k++) {
			if (temp[k] != curNum) {
				tempPair.push_back({ curcnt, curNum });
				curNum = temp[k]; curcnt = 1;
			}
			else curcnt++;
		}
		tempPair.push_back({ curcnt, curNum }); //������ ������ �־��ش�

		sort(tempPair.begin(), tempPair.end()); //����Ƚ�� -> ���� ������������ �����Ѵ�

		int x = 0;
		for (const auto it : tempPair) {
			if (x >= 100) break; //ù 100���� ������ �������� ������.
			rawdata[after][x++][j] = it.second;
			rawdata[after][x++][j] = it.first;
		}

		nextrows = max(nextrows, x); //������ row�� ũ�⸦ �˾ƺ���
		tempPair.clear();
		temp.clear();
	}

	swap(after, current);
	rows = nextrows;
}

void operate() {
	for (int iter = 0; iter < 100; iter++) {
		if (rawdata[current][targetRow][targetCol] == target) {
			cout << iter << endl;
			return;
		}
		if (rows >= cols) operateR();
		else operateC();
	}

	if (rawdata[current][targetRow][targetCol] == target) {
		cout << 100 << endl;
	}
	else cout << -1 << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}