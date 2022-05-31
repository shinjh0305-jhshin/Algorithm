#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> map[203];
bool visited[203]; //��� �ĺ����� �� �ô°�?(������ ������ �湮 ����)
int inRoom[203]; //index : ����� index, ���� : �ش� ��翡 �ִ� ���� index
int cows, rooms;

void initialize() {
	cin >> cows >> rooms;

	int iter, target;
	for (int i = 1; i <= cows; i++) {
		cin >> iter;
		for (int j = 0; j < iter; j++) {
			cin >> target;
			map[i].push_back(target);
		}
	}

	memset(inRoom, 0, sizeof(inRoom));
}

bool DFS(int cowNum) {
	for (const auto nextRoom : map[cowNum]) {
		/*
		A��� �Ұ� 3�� ���� ����; �о�⸦ ������ ��� 3-1-8-4-7�� Ž���� ����ƴٰ� ����.
		visited�� �� ���� ������ ���� ����Ѵ�.

		1. ���ѷ��� ����
		8�� �ִ� �Ұ� 4�� �з����� 4�� �ִ� �Ұ� 8�� �з��� �� �ִ� ��Ȳ�̸�, visited�� ������ ���� ������ �߻��� ���̴�.
		��, �� �ڸ��� �ִ� �Ұ� �з��������� ǥ���ϱ� ���ؼ� ����Ѵ�.

		2. ���ʿ��� ���� ����
		���� ���� ���� Ž�� ��� ��� ������ �����ؼ� A�� 8�� ������ �ٽ� ���ϴ� ��Ȳ�̶� ��������.
		������ 8-4-7�� ���� �� �̻� ���ٸ� ����� ����� ���� �̹� ���߱⿡, �� �̻� �� �� �ʿ䰡 ����.
		*/
		if (visited[nextRoom]) continue; //�� �� ���� ��
		visited[nextRoom] = true;

		if (inRoom[nextRoom] == 0 || DFS(inRoom[nextRoom])) { //���� ĭ �ȿ� �Ұ� ���ų�, �Ҹ� �о �� �ִ� ��Ȳ�̶��.
			inRoom[nextRoom] = cowNum;
			return true;
		}
	}

	return false;
}

void operate() {
	int ans = 0; //��翡 �� �� �ִ� ���� ����
	for (int i = 1; i <= cows; i++) {
		memset(visited, false, sizeof(visited));

		if (DFS(i)) ans++;
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