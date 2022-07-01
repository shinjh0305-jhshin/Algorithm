#include <iostream>
#include <deque>
#include <vector>
using namespace std;

struct info {
	int row, col, dir;
};
enum a {white, red, blue};
enum d {toright = 1, toleft, toup, todown};
int sz_map, players; //���� ũ��, �� ����
info player[11]; //���� ���� ��ġ, �̵� ����
vector<int> curPlayer[15][15]; //���� �ش� ��ġ�� �ִ� ���� index ����
int map[15][15]; //������ ���� ����
deque<int> tempPlayer; //���� �̵����� ���� �ӽ������

void initialize() {
	cin >> sz_map >> players;

	for (int i = 1; i <= sz_map; i++) {
		for (int j = 1; j <= sz_map; j++) {
			cin >> map[i][j];
		}
	}

	int row, col, dir;
	for (int i = 0; i < players; i++) {
		cin >> row >> col >> dir;
		player[i].row = row; player[i].col = col; player[i].dir = dir;
		curPlayer[row][col].push_back(i);
	}
}

bool movePlayer() {
	int currow, curcol, nextrow, nextcol, curdir;
	for (int i = 0; i < players; i++) { //�� �ϳ��� ����
		currow = nextrow = player[i].row; 
		curcol = nextcol = player[i].col;
		curdir = player[i].dir;

		do { //���� ������
			tempPlayer.push_back(curPlayer[currow][curcol].back());
			curPlayer[currow][curcol].pop_back();
		} while (tempPlayer.back() != i);

		if (curdir == toup) nextrow--;
		else if (curdir == todown) nextrow++;
		else if (curdir == toleft) nextcol--;
		else nextcol++;

		if (nextrow <= 0 || nextrow > sz_map || nextcol <= 0 || nextcol > sz_map || map[nextrow][nextcol] == blue) { //���� ����ų� ������ �Ķ��� ĭ�̴�.
			//���� ���� ������ �ٲٰ�, ���� ���� ��ġ�� �����Ѵ�.
			if (curdir == toup) {
				player[i].dir = todown;
				nextrow += 2;
			}
			else if (curdir == todown) {
				player[i].dir = toup;
				nextrow -= 2;
			}
			else if (curdir == toleft) {
				player[i].dir = toright;
				nextcol += 2;
			}
			else {
				player[i].dir = toleft;
				nextcol -= 2;
			}
		}

		int temp;
		if (nextrow <= 0 || nextrow > sz_map || nextcol <= 0 || nextcol > sz_map || map[nextrow][nextcol] == blue) { //�Ķ� ĭ�� ����ġ�� ���� ��ġ�� ���� ������� �ִ´�.
			while (!tempPlayer.empty()) {
				temp = tempPlayer.back();
				curPlayer[currow][curcol].push_back(temp);
				tempPlayer.pop_back();
			}
		}
		else if (map[nextrow][nextcol] == white) { //�Ͼ� ĭ�� ����ġ�� �� ���� �״�� ��������
			while (!tempPlayer.empty()) {
				temp = tempPlayer.back();
				player[temp].row = nextrow;
				player[temp].col = nextcol;
				curPlayer[nextrow][nextcol].push_back(temp);
				tempPlayer.pop_back();
			}
			if (curPlayer[nextrow][nextcol].size() >= 4) return true;
		}
		else if (map[nextrow][nextcol] == red) { //���� ĭ�� ����ġ�� ������ �ٲ۴�.
			while (!tempPlayer.empty()) {
				temp = tempPlayer.front();
				player[temp].row = nextrow;
				player[temp].col = nextcol;
				curPlayer[nextrow][nextcol].push_back(temp);
				tempPlayer.pop_front();
			}
			if (curPlayer[nextrow][nextcol].size() >= 4) return true;
		}

	}

	return false;
}

void operate() {
	for (int i = 1; i <= 1000; i++) {
		if (movePlayer()) {
			cout << i << endl;
			return;
		}
	}

	cout << -1 << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}