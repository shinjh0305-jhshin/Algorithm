#include <iostream>
#include <algorithm>
#define endl "\n"
#define INF 1234567890
using namespace std;

/***********
cols : ���μ��� ����
rows : �̹� ��ġ �� ���μ��� ����
avail : ���μ��� ���� �� �ִ� �ĺ����� ����
************/
int rows, cols, avail;
int answer = INF;
bool map[32][12] = { false };

void initialize() {
	cin >> cols >> rows >> avail;

	int a, b;
	for (int i = 0; i < rows; i++) {
		cin >> a >> b;
		map[a][b] = true;
	}
}

bool play_game() {
	int mov;
	for (int i = 1; i <= cols; i++) {
		mov = i;
		for (int j = 1; j <= avail; j++) {
			if (map[j][mov - 1]) mov--;
			else if (map[j][mov]) mov++;
		}
		if (mov == i) continue; //���� �������� �״�� ��������
		else return false; //�ٸ� ������ ���� ������ �� ������ �� ���� �ٷ� false�� �����Ѵ�.
	}
	return true;
}

void make_col(int row, int col, int depth) {
	// ���� ��� ������ ��� ������ �ʿ䰡 ����.
	if (play_game()) {
		answer = min(answer, depth);
		return;
	}
	if (depth == 3) return; //�� �̻� �� ���� ���̴�.

	for (; row <= avail; row++) {
		for (; col < cols; col++) {
			if (!map[row][col - 1] && !map[row][col + 1] && !map[row][col]) {
				map[row][col] = true;
				if (depth < answer) make_col(row, col + 1, depth + 1); //������ ���� �ּ� depth���� ũ�ų� ���� ��� ������ �ʿ䰡 ����.
				map[row][col] = false;
			}
		}
		col = 1;
	}
}

void operate() {
	make_col(1, 1, 0);
	if (answer == INF) cout << -1 << endl;
	else cout << answer << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
3 5 6
1 2
2 1
3 2
4 1
5 2
ans : 1
*/