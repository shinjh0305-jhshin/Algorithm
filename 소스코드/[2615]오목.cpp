#include <iostream>
using namespace std;

enum a {horiz, vertical, rightDiag, leftDiag}; //����, ����, ������밢��, ������밢��
bool visited[20][20][4] = { false }; //�� �������� �ش� �������� Ȯ���� �� ���Ҵ°�
int map[20][20];

void initialize() {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			cin >> map[i][j];
		}
	}
}

bool checkVictory(int row, int col, int rowInc, int colInc, int dir) { //rowInc, colInc = 1,0(vert), 0,1(horiz), 1,1(rightDiag), 1,-1(leftDiag)
	int i, curColor = map[row][col];
	for (i = 0;; i++) {
		if (row < 0 || row >= 19 || col < 0 || col >= 19 || map[row][col] != curColor) break;
		visited[row][col][dir] = true;
		row += rowInc;
		col += colInc;
	}
	if (i == 5) return true; //������ �ϼ���.
	else return false; //���� ������ ���ؼ� ������ �ϼ����� ����.
}

void operate() {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) { 
			if ((map[i][j] && !visited[i][j][horiz] && checkVictory(i, j, 0, 1, horiz)) || //���� ���� �밢�� �߿��� �ϳ��� ������ ���
				(map[i][j] && !visited[i][j][vertical] && checkVictory(i, j, 1, 0, vertical)) ||
				(map[i][j] && !visited[i][j][rightDiag] && checkVictory(i, j, 1, 1, rightDiag))) {

				cout << map[i][j] << endl;
				cout << i + 1 << ' ' << j + 1 << endl;
				return;
			}
			else if ((map[i][j] && !visited[i][j][leftDiag] && checkVictory(i, j, 1, -1, leftDiag))) { //������ �밢���� ������ ����Ʈ�Ѵ�.
				cout << map[i][j] << endl;
				cout << i + 5 <<  ' ' << j - 3 << endl;
				return;
			}
		}
	}

	cout << 0 << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}