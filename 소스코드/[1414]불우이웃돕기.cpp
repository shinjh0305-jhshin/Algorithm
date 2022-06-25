#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define endl "\n"
using namespace std;

struct info {
	int cost, row, col;
};

vector<info> rawdata;
int sz_rawdata, totalLength = 0;
int root[2500];

bool compare(const info& a, const info& b) {
	return a.cost < b.cost;
}

void initialize() {
	cin >> sz_rawdata;

	string st;
	for (int i = 0; i < sz_rawdata; i++) {
		cin >> st;
		for (int j = 0; j < sz_rawdata; j++) {
			if (st[j] == '0') continue;
			else if ('a' <= st[j] && st[j] <= 'z') { //���ڷ� ���� ��ȯ�ؼ� rawdata�� �ִ´�.
				if (i != j) rawdata.push_back({ st[j] - 'a' + 1, i, j });
				totalLength += st[j] - 'a' + 1;
			}
			else {
				if (i != j) rawdata.push_back({ st[j] - 'A' + 27, i, j });
				totalLength += st[j] - 'A' + 27;
			}
		}
	}

	for (int i = 0; i < sz_rawdata; i++) {
		root[i] = -1;
	}

	sort(rawdata.begin(), rawdata.end(), compare);
}

int getRoot(int num) {
	if (root[num] < 0) return num;
	return root[num] = getRoot(root[num]);
}

void mergeRoot(int num1, int num2, int cost) {
	int root1 = getRoot(num1);
	int root2 = getRoot(num2);

	if (root1 == root2) return; //�̹� ���� ����Ǿ� �ֱ⿡, ������ ������ �ʿ� ����

	if (root[root1] > root[root2]) swap(root1, root2); //���� ������� �ʾҴ�. ������ �� ������ �����Ѵ�.

	root[root1] += root[root2];
	root[root2] = root1;

	totalLength -= cost; //��ü ���� ���̿��� ������ ���� ���̸� ����
}

void operate() {
	int root1, root2;
	for (const auto curLan : rawdata) {
		mergeRoot(curLan.row, curLan.col, curLan.cost);
	}

	root1 = getRoot(0);
	for (int i = 1; i < sz_rawdata; i++) {
		root2 = getRoot(i);
		if (root1 != root2) {
			cout << -1 << endl;
			return;
		}
	}

	cout << totalLength << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}