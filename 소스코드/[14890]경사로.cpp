#include <iostream>
#include <cstring>
using namespace std;

bool installed[103][103] = { false };
int map[103][103];
int sz_map, length;

void initialize() {
	cin >> sz_map >> length;
	for (int i = 0; i < sz_map; i++) {
		for (int j = 0; j < sz_map; j++) {
			cin >> map[i][j];
		}
	}
}

int operate() {
	int ans = 0;
	//1. ���� ��
	for (int row = 0; row < sz_map; row++) {
		for (int col = 1; col < sz_map; col++) {
			if (map[row][col - 1] > map[row][col]) { //�� �������� ���̰� ���� ���
				for (int dist = 0; dist < length; dist++) {
					if (col + dist >= sz_map || (map[row][col + dist] != map[row][col - 1] - 1)) {
						goto nextRow;
					}
					installed[row][col + dist] = true; //���ΰ� ��ġ��
				}
				col = col + length - 1; //���ΰ� ��ġ �� �������� �Ѿ��.
			}
			else if (map[row][col - 1] < map[row][col]) { //�� �������� ���̰� ū ���
				for (int dist = 1; dist <= length; dist++) {
					if (col - dist < 0 || (map[row][col - dist] != map[row][col] - 1) || installed[row][col - dist]) {
						goto nextRow;
					}
					installed[row][col - dist] = true; //���ΰ� ��ġ��
				}
			}
		}
		ans++;
	nextRow:;
	}

	memset(installed, false, sizeof(installed));

	//2. ���� ��
	for (int col = 0; col < sz_map; col++) {
		for (int row = 1; row < sz_map; row++) {
			if (map[row - 1][col] > map[row][col]) { //�� �������� ���̰� ���� ���
				for (int dist = 0; dist < length; dist++) {
					if (row + dist >= sz_map || (map[row + dist][col] != map[row - 1][col] - 1)) {
						goto nextCol;
					}
					installed[row + dist][col] = true; //���ΰ� ��ġ��
				}
				row = row + length - 1; //���ΰ� ��ġ �� �������� �Ѿ��.
			}
			else if (map[row - 1][col] < map[row][col]) { //�� �������� ���̰� ū ���
				for (int dist = 1; dist <= length; dist++) {
					if (row - dist < 0 || (map[row - dist][col] != map[row][col] - 1) || installed[row - dist][col]) {
						goto nextCol;
					}
					installed[row - dist][col] = true; //���ΰ� ��ġ��
				}
			}
		}
		ans++;
	nextCol:;
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	cout << operate() << endl;

	return 0;
}