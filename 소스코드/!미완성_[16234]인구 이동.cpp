#include <iostream>
#include <vector>
using namespace std;

int map[52][52];
bool visited[52][52] = { false };
int sz_map, lowerBound, upperBound;

void initialize() {
	cin >> sz_map >> lowerBound >> upperBound;

	for (int i = 0; i < sz_map; i++) {
		for (int j = 0; j < sz_map; j++) {
			cin >> map[i][j];
		}
	}
}
 /*
 1. visited�� ��ȸ�ϸ鼭 ���� �ܰ迡�� �α� �̵��� �Ͼ ������ Ȯ���Ѵ�.
 2. �α� �̵��� �Ͼ ���̶��, ���� BFS�� �ϸ鼭 �α� �̵��� �Ͼ ���� ���� vector�� �ִ´�. (��ǥ���� ������ �ȴ�)
 3. BFS Ž���� �ϸ鼭 �α����� ���� sum���� �����Ѵ�. ��, 
 3. vector�� �ִ� ��ǥ�� �α��� ��źȭ ��Ų��.

 */


int operate() {
	int days = -1;
	bool moved = true;

	while (moved) {
		moved = false;
		days++;

		for (int i = 0; i < sz_map; i++) {
			for (int j = 0; j < sz_map; j++) {

			}
		}
	}
}
