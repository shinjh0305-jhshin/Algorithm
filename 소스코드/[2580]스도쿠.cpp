#include <iostream>
#include <stack>
#define endl "\n"
#define SQIDX(i,j) (((i) / 3) * 3 + (j) / 3)
#pragma warning (disable:4996)
using namespace std;

bool row[9][10] = { false }, col[9][10] = { false }, square[9][10] = { false };
int rawdata[9][9];
deque<pair<int, int>> tofill, done;

void initialize() {
	int target;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> target;
			rawdata[i][j] = target;			
			
			if (target == 0) {
				tofill.push_back({ i, j });
			}
			else {
				row[i][target] = true;
				col[j][target] = true;
				square[SQIDX(i, j)][target] = true;
			}
		}
	}
}

void operate() {
	bool found;
	int currow, curcol, to_start;

	while (!tofill.empty()) {
		currow = tofill.front().first; curcol = tofill.front().second;
		found = false; //rawdata[currow][curcol]�� ��� �� ���ڸ� ã�Ҵ���.

		for (int i = 1; i <= 9; i++) {
			if (!row[currow][i] && !col[curcol][i] && !square[SQIDX(currow, curcol)][i]) {
				row[currow][i] = col[curcol][i] = square[SQIDX(currow, curcol)][i] = true;
				rawdata[currow][curcol] = i;
				done.push_back({ currow, curcol });
				found = true;
				break;
			}
		}

		if (found) { //rawdata[currow][curcol]�� �� ���ڸ� ã�Ҵ�.
			tofill.pop_front();
			continue;
		} 

		//rawdata[currow][curcol]�� ��� �� ���ڸ� �� ã�Ҵ�.
		found = false; //done.back�� �ش�Ǵ� ��ǥ�� ��� �� ���ڸ� ã�Ҵ���

		while (1) {
			//1. done�� back���� index�� �����´�.
			currow = done.back().first; curcol = done.back().second;

			//2. back�� ��ġ�� ���� �� ���ڿ��� �� Ž���� �����Ѵ�.
			to_start = rawdata[currow][curcol];
			row[currow][to_start] = col[curcol][to_start] = square[SQIDX(currow, curcol)][to_start] = false;

			for (int i = to_start + 1; i <= 9; i++) {
			//3. ã���� :  �� ���ڸ� ������ �� ���� if�� �ȿ� �ִ� ������ �����Ѵ�.
				if (!row[currow][i] && !col[curcol][i] && !square[SQIDX(currow, curcol)][i]) {
					row[currow][i] = col[curcol][i] = square[SQIDX(currow, curcol)][i] = true;
					rawdata[currow][curcol] = i;
					found = true;
					goto next;
				}
			}

			//4. �� ã���� : �� ������ ������ �־������̱� ������, tofill�� currow, curcol�� push_front �ϰ� 1�� ���ư���.
			done.pop_back();
			tofill.push_front({ currow, curcol });
		}

	next:;
	}

	cout << endl;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << rawdata[i][j] << ' ';
		}
		cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
1 0 0 0 8 9 0 0 0
0 0 0 2 0 0 1 0 0
0 0 3 0 0 0 0 6 0
0 2 0 0 0 7 0 0 9
0 6 0 0 5 0 0 2 0
4 0 0 9 0 0 0 1 0
0 9 0 0 0 0 4 0 0
0 0 7 0 0 8 0 0 0
0 0 0 1 3 0 0 0 5

0 0 0 8 0 1 0 0 0
0 0 0 0 0 0 4 3 0
5 0 0 0 0 0 0 0 0
0 0 0 0 7 0 8 0 0
0 0 0 0 0 0 1 0 0
0 2 0 0 3 0 0 0 0
6 0 0 0 0 0 0 7 5
0 0 3 4 0 0 0 0 0
0 0 0 2 0 0 6 0 0
*/