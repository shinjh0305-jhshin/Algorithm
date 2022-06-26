#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#define endl "\n"
using namespace std;

struct info {
	int dest, cost;
};

vector<info> map[100003];
int nodes, edges;
int start, finish;

void initialize(int& cost_max) { //cost_max : �ٸ� �� �ִ� ��� ����
	cin >> nodes >> edges;

	int from, to, cost_temp;

	for (int i = 0; i < edges; i++) {
		cin >> from >> to >> cost_temp;
		map[from].push_back({ to, cost_temp });
		map[to].push_back({ from, cost_temp });
		cost_max = max(cost_max, cost_temp);
	}

	cin >> start >> finish;
}

bool BFS(int target) {
	bitset<100003> visited(0);
	queue<int> qu;
	int sz_edges, startPoint, nextPoint;

	qu.push(start); 
	visited.set(start, true);

	while (!qu.empty()) {
		startPoint = qu.front(); qu.pop();
		sz_edges = map[startPoint].size();

		for (int iter = 0; iter < sz_edges; iter++) {
			nextPoint = map[startPoint][iter].dest;

			if (!visited[nextPoint] && map[startPoint][iter].cost >= target) { //�湮���� ���� ����, target ���԰� ���� �� �ִ� �ٸ���.

				if (nextPoint == finish) return true;

				qu.push(nextPoint);
				visited.set(nextPoint, true);
			}
		}
	}
	
	return false;
}

void operate() {
	int cost_max = -1;
	initialize(cost_max);

	int front = 1, back = cost_max, mid, temp;
	
	while (front <= back) { //�ִ� ��� ���Ը� �� ������ �ؼ� �̺�Ž���� �ǽ��Ѵ�.
		mid = (front + back) / 2;

		if (BFS(mid)) { //mid�� ���Ը� ���� ��ǰ�� �ű� �� �ִ��� Ȯ���Ѵ�.
			temp = mid;
			front = mid + 1;
		}
		else
			back = mid - 1;
	}

	cout << temp << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}

/*
4 4
4 2 3
4 3 1
2 3 3
3 1 3
4 1
ans : 3

7 10
1 2 6
1 3 4
2 3 3
2 5 6
3 4 8
3 5 5
2 4 7
6 4 5
4 7 4
6 7 3
1 6
ans : 5

*/