#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#define endl "\n"
#define STATUS vector<bool>
using namespace std;

int sz_cities;
int ppls[11];
vector<int> map[11];

void initialize() {
	cin >> sz_cities;

	for (int i = 1; i <= sz_cities; i++) {
		cin >> ppls[i];
	}

	int iter, target;
	for (int i = 1; i <= sz_cities; i++) {
		cin >> iter;
		for (int j = 0; j < iter; j++) {
			cin >> target;
			map[i].push_back(target);
		}
	}
}

bool check_connection(STATUS visited) {
	int target;
	queue<int> qu;

	target = find(visited.begin() + 1, visited.begin() + sz_cities, false) - visited.begin();
	visited[target] = true;
	qu.push(target);

	while (!qu.empty()) {
		target = qu.front(); qu.pop();
		for (int i = 0; i < map[target].size(); i++) {
			if (visited[map[target][i]] == false) {
				qu.push(map[target][i]);
				visited[map[target][i]] = true;
			}
		}
	}

	if (find(visited.begin() + 1, visited.begin() + sz_cities, false) != visited.begin() + sz_cities) return false;
	return true;
}

void operate() {
	queue<STATUS> qu;
	STATUS visited(11, false), original, temp;
	int target, withOne, withoutOne, answer = 123456790;
	visited[1] = true; //1�� �������� �����Ѵ�
	qu.push(visited);

	while (!qu.empty()) {
		original = temp = qu.front(); qu.pop(); //original : �ʱ⿡ �޾ƿ� �������, temp : ���� ��� ��湮 �����ϴ� ��ŷ�޸�

		if (check_connection(original)) { //���� �� ���� ������ �����Ѵٸ�
			withOne = withoutOne = 0;
			for (int i = 1; i <= sz_cities; i++) {
				if (original[i] == true)  withOne += ppls[i];
				else withoutOne += ppls[i];
			}
			answer = min(answer, abs(withOne - withoutOne));
		}
		
		for (int i = 1; i <= sz_cities; i++) {
			if (original[i] == true) { //1�� ���� �׷쿡 �ִ� ����
				for (int j = 0; j < map[i].size(); j++) {
					target = map[i][j];

					if (temp[target] == false) { //���õ� �� ����
						temp[target] = true; //�湮 �̷� ǥ��

						original[target] = true;
						qu.push(original);
						original[target] = false;
					}
				}
			}
		}
	}
	if (answer == 123456790) cout << -1 << endl;
	else cout << answer << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	initialize();
	operate();

	return 0;
}