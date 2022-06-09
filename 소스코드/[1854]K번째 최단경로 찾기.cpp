#include <iostream>
#include <queue>
#include <vector>
#define endl "\n"
#define INF 2134567890
using namespace std;

int leftVisit[1003], dist[1003];
int nodes, edges, order;
vector<pair<int, int>> map[1003];

void initialize() {
	cin >> nodes >> edges >> order;

	int to, from, cost;
	for (int i = 0; i < edges; i++) {
		cin >> from >> to >> cost;
		map[from].push_back({ cost, to });
	}

	for (int i = 1; i <= nodes; i++) {
		leftVisit[i] = order - 1;
		dist[i] = INF;
	}
}

void operate() {
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //{���� �Ÿ�, ���� ���}

	pq.push({ 0, 1 }); 

	int curNode, curDist, nextNode, nextDist, szMap;
	while (!pq.empty()) {
		curDist = pq.top().first; curNode = pq.top().second;
		pq.pop();

		if (leftVisit[curNode] < 0) continue;
		if (leftVisit[curNode] == 0) { //k��° �ִ� ��ο� �� �ִ�.
			dist[curNode] = curDist;
		}
		leftVisit[curNode]--; //�� �� �� ���;� �ϴ��� ������Ʈ�Ѵ�.

		for (const auto mov : map[curNode]) {
			nextDist = mov.first; nextNode = mov.second;
			if (leftVisit[nextNode] < 0) continue; //A��忡 k��° �ִ� ��ΰ� �������ٸ�, A���� �� �� �ִ� ��� ����� k��° �ִ� ��ε� �̹� ���� �ִ�.

			nextDist += curDist;
			pq.push({ nextDist, nextNode });
		}
	}

	for (int i = 1; i <= nodes; i++) {
		if (dist[i] == INF) cout << -1 << endl;
		else cout << dist[i] << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
5 10 3
1 2 2
1 3 7
1 4 5
1 5 6
2 4 2
2 3 4
3 4 6
3 5 8
5 2 4
5 4 1
*/