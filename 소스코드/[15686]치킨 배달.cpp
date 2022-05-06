//1. ���� ġŲ���� ���ش�
//2. ���� ġŲ���� ���ε��Ǿ��� ���� �ٸ� ġŲ���� ã�� ������
//3. ���� ġŲ������ �̵��Ѵ�.
//3-1. ���� ġŲ������ �̵� �� ���� ���� ġŲ�Ÿ��� �ո� �����ϸ� �ȴ�.

//�ʿ� �Լ� : ��� �� �Լ�, ����Լ�, ġŲ �Ÿ� ã�� �Լ�

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#define endl "\n"
using namespace std;

struct pos {
	int row, col;
};

int map[52][52];
bool closed[15] = { false };
enum a { _home = 1, _chicken };
vector<pos> chicken, house;
int sz_map, close, result = 1234567890;

void initialize() {
	cin >> sz_map >> close;
	for (int i = 0; i < sz_map; i++) {
		for (int j = 0; j < sz_map; j++) {
			cin >> map[i][j];
			if (!map[i][j]) continue;
			if (map[i][j] == _home) { //house
				house.push_back({ i, j });
			}
			else if (map[i][j] == _chicken) { //chicken
				chicken.push_back({ i, j });
			}
		}
	}
}

void findChickenDist(int houseIdx, int &distance) { //���� �� ���� ġŲ �Ÿ��� ����ؼ� ��ü ġŲ �Ÿ��� �ݿ��Ѵ�.
	int houseRow = house[houseIdx].row, houseCol = house[houseIdx].col; //���� ���� index
	int chickenDist = 1234567890, temp, iter = 0;

	for (auto it : chicken) { //ġŲ������ ��ȸ�Ѵ�
		if (!closed[iter]) { //������� ���� ġŲ���̶��
			temp = abs(it.row - houseRow) + abs(it.col - houseCol);
			chickenDist = min(chickenDist, temp); //���� ġŲ���� �� ������ ���� ����� ���ΰ�?
		}
		iter++;
	}
	
	distance += chickenDist; //���� ġŲ �Ÿ��� ���Ѵ�.
}

void closeChicken(int start, int togo) { //start : �۾� �����ϴ� ġŲ�� �ε���, togo : �ݾƾ� �� �ܿ� ġŲ�� ����
	if (togo == 0) { //���� ġŲ���� ����.
		int dist = 0, sz_house = house.size();
		for (int i = 0; i < sz_house; i++) {
			findChickenDist(i, dist); //�� ���� ġŲ �Ÿ��� ���Ѵ�.
		}
		result = min(dist, result);
		return;
	}

	int upperBound = chicken.size() - togo;
	for (int i = start; i <= upperBound; i++) {
		closed[i] = true; //ġŲ���� �ݴ´�.
		closeChicken(i + 1, togo - 1); //���� ġŲ���� ������ ������.
		closed[i] = false; //�ٽ� ���󺹱ͽ�Ų��.
	}
}

void operate() {
	closeChicken(0, chicken.size() - close);
	cout << result << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}
