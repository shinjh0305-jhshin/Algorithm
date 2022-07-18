#include <iostream>
#include <algorithm>
#define BLANK '.'
#define WALL '#'
#define COIN 'o'
#define INF 1234567890
using namespace std;

int drow[4] = { 1,0,-1,0 };
int dcol[4] = { 0,-1,0,1 };

pair<int, int> coins[2];
char map[21][21];
int rows, cols, answer = INF;

void initialize() {
	cin >> rows >> cols; cin.get();

	int coinTemp = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = cin.get();
			if (map[i][j] == COIN) {
				coins[coinTemp++] = { i,j };
				map[i][j] = BLANK; //���� ��ġ�� �̵� ���� ���� �� ĭ���� �����Ѵ�.
			}
		}
		cin.get();
	}
}

void DFS(int depth) {
	if (depth >= answer || depth > 10) return; //���� �̵� Ƚ���� �̹� ���� �ּڰ����� ũ�ų� ���� ���

	pair<int, int> coinsTemp[2]; //������ ���� ��ġ ����
	for (int i = 0; i < 2; i++) {
		coinsTemp[i].first = coins[i].first;
		coinsTemp[i].second = coins[i].second;
	}

	int coinOut; // ������ ������ ����
	int temprow, tempcol;
	for (int j = 0; j < 4; j++) { 
		coinOut = 0;
		for (int i = 0; i < 2; i++) { //���� 2�� �����δ�
			temprow = coinsTemp[i].first + drow[j];
			tempcol = coinsTemp[i].second + dcol[j];

			if (temprow < 0 || temprow >= rows || tempcol < 0 || tempcol >= cols) { //��������
				coinOut++;
			}
			else if (map[temprow][tempcol] == WALL) { //���̴�
				coins[i] = { temprow - drow[j], tempcol - dcol[j] }; //���� ��ġ ��´�
			}
			else { //��ĭ�̴�
				coins[i] = { temprow, tempcol }; //���ο� ��ġ ��´�
			}
		}

		if (coinOut == 2) continue;
		else if (coinOut == 1) { //���� 1���� ������ ���
			answer = min(answer, depth);
			//���󺹱� �� return
			return;
		}
		else { //������ ������ ���� ���
			DFS(depth + 1);
		}
	}

}

void operate() {
	DFS(1);

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