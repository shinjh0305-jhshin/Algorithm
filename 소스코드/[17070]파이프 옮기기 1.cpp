#include <iostream>
#include <vector>
using namespace std;

enum direction { horiz, vert, diag }; //���� ���� �밢��
enum status { avail = -1, wall = 1234567890 };
vector<int> movType[3] = { {0,2}, {1,2}, {0,1,2} };//���� ���� �밢�� ���� ������ �� �ִ� ����� ��
int map[3][17][17];
int sz_map;
//�������� index�� ������ ���� �������� �Ѵ�

void initialize() {
	cin >> sz_map;
	
	int temp;
	for (int i = 0; i < sz_map; i++) {
		for (int j = 0; j < sz_map; j++) {
			cin >> temp;
			if (temp == 0) map[horiz][i][j] = map[vert][i][j] = map[diag][i][j] = avail;
			else map[horiz][i][j] = map[vert][i][j] = map[diag][i][j] = wall;
			
		}
	}
}

bool horizPossible(int row, int col) {
	if (col + 1 < sz_map && map[horiz][row][col + 1] != wall) return true;
	return false;
}

bool vertPossible(int row, int col) {
	if (row + 1 < sz_map && map[vert][row + 1][col] != wall) return true;
	return false;
}

bool diagPossible(int row, int col) {
	if (col + 1 < sz_map && row + 1 < sz_map &&
		map[vert][row][col + 1] != wall && map[vert][row + 1][col] != wall && map[vert][row + 1][col + 1] != wall) return true;
	return false;
}

int DFS(int row, int col, int dir) { //row, col�� �������� ������ ���� ���󰣴�
	if (row == sz_map - 1 && col == sz_map - 1) return 1; //���� ����

	map[dir][row][col] = 0; //�ʱ�ȭ
	for (int i = 0; i < movType[dir].size(); i++) {
		if (movType[dir][i] == horiz && horizPossible(row, col)) { //case horiz
			if (map[horiz][row][col + 1] == avail) { //��Ž�� ����
				map[dir][row][col] += DFS(row, col + 1, horiz); //���� dir�� ���� ĭ�� horiz ����� ���� ������� ���Ѵ�
			}
			else map[dir][row][col] += map[horiz][row][col + 1]; //�̹� Ž���� ��� �� ����� ������ ����
		}

		else if (movType[dir][i] == vert && vertPossible(row, col)) { //case vert
			if (map[vert][row + 1][col] == avail) { //��Ž�� ����
				map[dir][row][col] += DFS(row + 1, col, vert); //���� dir�� ���� ĭ�� vert ����� ���� ������� ���Ѵ�
			}
			else map[dir][row][col] += map[vert][row + 1][col]; //�̹� Ž���� ��� �� ����� ������ ����
		}

		else if (horizPossible(row, col) && vertPossible(row, col) && diagPossible(row, col)) { //case diagonal
			if (map[diag][row + 1][col + 1] == avail) { //��Ž�� ����
				map[dir][row][col] += DFS(row + 1, col + 1, diag); //���� dir�� ���� ĭ�� vert ����� ���� ������� ���Ѵ�
			}
			else map[dir][row][col] += map[diag][row + 1][col + 1]; //�̹� Ž���� ��� �� ����� ������ ����
		}
	}

	return map[dir][row][col];
}

void operate() {
	cout << DFS(0, 1, horiz) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}