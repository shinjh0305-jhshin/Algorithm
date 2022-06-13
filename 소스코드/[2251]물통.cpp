#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"
using namespace std;

int sz[3];
bool visited[202][202][202] = { false };
vector<int> result;

void initialize() {
	cin >> sz[0] >> sz[1] >> sz[2];
}

void makeChange(int curWater[3]) {
	if (visited[curWater[0]][curWater[1]][curWater[2]]) return;
	visited[curWater[0]][curWater[1]][curWater[2]] = true;

	if (curWater[0] == 0) result.push_back(curWater[2]);

	int tempWater[3];
	for (int i = 0; i < 3; i++) {
		if (curWater[i]) { //i�� ��ũ�� �ű��.
			for (int j = 0; j < 3; j++) { //j�� ��ũ�� ���� �ű��.
				if (i == j || curWater[j] == sz[j]) continue; //���� ��ũ�ų�, �ű� ��ũ�� �� á���� pass

				for (int k = 0; k < 3; k++) tempWater[k] = curWater[k]; //�Ѱ��� �� �뷮��

				if (sz[j] - curWater[j] >= curWater[i]) { //i�� �� ���θ� j���� �� �� �ִٸ�
					tempWater[i] = 0; tempWater[j] = curWater[i] + curWater[j];
					makeChange(tempWater);
				}
				else { //i�� �� �Ϻθ� j���� �� �� �ִٸ�. �� j�� �� ����.
					tempWater[i] = curWater[i] - (sz[j] - curWater[j]);
					tempWater[j] = sz[j];
					makeChange(tempWater);
				}
			}
		}
	}
}

void operate() {
	int initial[] = { 0,0,sz[2] };
	makeChange(initial);

	sort(result.begin(), result.end());

	for (const auto it : result) {
		cout << it << ' ';
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}