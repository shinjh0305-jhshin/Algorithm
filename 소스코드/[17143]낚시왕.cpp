#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct info {
	int speed, dir, size;
};
vector<info> rawdata[2][103][103];
int after = 0, current = 1;  
stack<pair<int, int>> curShark; //row, col

int rows, cols, sharks, curfisher = 0, ans = 0;

void initialize() {
	cin >> rows >> cols >> sharks;
	//row col speed dir size

	int row, col, speed, dir, size;

	for (int i = 0; i < sharks; i++) {
		cin >> row >> col >> speed >> dir >> size;
		rawdata[current][row][col].push_back({ speed, dir, size });
	}
}

void catchShark() {
	curfisher++;
	bool fishCaught = false;

	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			auto& sharkInfo = rawdata[current][i][j];

			if (sharkInfo.empty()) continue;

			if (j == curfisher && !fishCaught) { //���� ������ �� ��µ�, ���� �� �� ���� ���¸�, �� ���� ���
				ans += sharkInfo[0].size;
				sharkInfo.pop_back();
				fishCaught = true;
			}
			else curShark.push({ i, j });
		}
	}
}

void moveShark() {
	int sz_stack = curShark.size();

	int currow, curcol, curdir, curspeed, cursize;

	while (sz_stack--) {
		currow = curShark.top().first;
		curcol = curShark.top().second;
		curShark.pop();

		auto& sharkInfo = rawdata[current][currow][curcol];
		curdir = sharkInfo[0].dir;
		curspeed = sharkInfo[0].speed;
		cursize = sharkInfo[0].size;
		sharkInfo.pop_back();
		
		int mod;
		if (curdir == 1 || curdir == 2) mod = 2 * (rows - 1);
		else mod = 2 * (cols - 1);

		int mov = curspeed % mod;

		while (mov--) {
			if (curdir == 1) { //���� ����
				if (currow != 1) currow--;
				else { //�Ʒ� �������� �ٲ۴�
					currow = 2; curdir = 2;
				}
			}
			else if (curdir == 2) { //�Ʒ��� ����
				if (currow != rows) currow++;
				else { //�� �������� �ٲ۴�
					currow = rows - 1; curdir = 1;
				}
			}
			else if (curdir == 3) { //���������� ����
				if (curcol != cols) curcol++;
				else { //���� �������� �ٲ۴�
					curcol = cols - 1; curdir = 4;
				}
			}
			else { //�������� ����
				if (curcol != 1) curcol--;
				else { //������ �������� �ٲ۴�
					curcol = 2; curdir = 3;
				}
			}
		}
		if (rawdata[after][currow][curcol].empty()) rawdata[after][currow][curcol].push_back({ curspeed, curdir, cursize });
		else if (rawdata[after][currow][curcol].front().size < cursize) {
			rawdata[after][currow][curcol].pop_back();
			rawdata[after][currow][curcol].push_back({ curspeed, curdir, cursize });
		}
	}
	swap(current, after);
}

void operate() {
	for (int i = 0; i < cols; i++) {
		catchShark(); //��� ���
		moveShark();  //��� �̵�
	}

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}