#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#define endl "\n"
#define INF 2134567890
using namespace std;

int nodes, edges, candidates, start, mustA, mustB, btwMust; //mustA, mustB : �ݵ�� ������ �ϴ� �� ���, btwMust : mustA-mustB ���� ����
vector<pair<int, int>> map[2002]; //��������, �Ÿ�
int totalCost[3][2002]; //0:����->���� 1:mustA->���� 2:mustB->����

void initialize() {
	cin >> nodes >> edges >> candidates >> start >> mustA >> mustB;
	for (int i = 1; i <= nodes; i++) map[i].clear(); //������ �����ִ� map ������ ���� �����.

	int from, to, cost;
	for (int i = 0; i < edges; i++) { //map �����
		cin >> from >> to >> cost;
		map[from].push_back({ to, cost });
		map[to].push_back({ from, cost });

		if ((from == mustA && to == mustB) || (from == mustB && to == mustA)) btwMust = cost;
	}

	for (int i = 0; i < 3; i++) { //dijkstra �迭 �ʱ�ȭ
		for (int j = 1; j <= nodes; j++) {
			totalCost[i][j] = INF;
		}
	}
}

void dijkstra(int curTarget, int startPoint) {//curTarget : ���� �������� totalCost�� row index, startPoint : start, mustA, mustB �� �� ��
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //�� �Ÿ�, ��������
	pq.push({ 0, startPoint });
	totalCost[curTarget][startPoint] = 0;

	int curSum, curStart, dest, tempSum;
	while (!pq.empty()) {
		curSum = pq.top().first; curStart = pq.top().second; pq.pop();

		if (curSum > totalCost[curTarget][curStart]) continue; //�̹� �� �ִܰ�ο��� �򰡵Ǿ���.

		for (const auto it : map[curStart]) {
			dest = it.first; tempSum = curSum + it.second;

			if (totalCost[curTarget][dest] <= tempSum) continue;

			totalCost[curTarget][dest] = tempSum;
			pq.push({ tempSum, dest });
		}
	}
}

void operate() { 
	dijkstra(0, start); //������������ ����ϴ� ���ͽ�Ʈ��
	dijkstra(1, mustA); //�ʼ����� �� �� �� ������ ����ϴ� ���ͽ�Ʈ��
	dijkstra(2, mustB); //�ʼ����� �� �ٸ� �� ������ ����ϴ� ���ͽ�Ʈ��

	vector<int> v;

	int candidate; //���� �ĺ���
	for (int i = 0; i < candidates; i++) {
		cin >> candidate;

		//min(start-A-B-End, start-B-A-End)
		if (min(totalCost[0][mustA] + totalCost[2][candidate], totalCost[0][mustB] + totalCost[1][candidate]) + btwMust == totalCost[0][candidate]) {
			v.push_back(candidate);
		}
	}
	sort(v.begin(), v.end());
//	cout << "				ANSWER : ";
	for (const auto it : v) cout << it << ' ';
	cout << endl;

}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int test_cases;
	cin >> test_cases;

	for (int i = 0; i < test_cases; i++) {
		initialize();
		operate();
	}

	return 0;
}