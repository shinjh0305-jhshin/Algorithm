#include <iostream>
#include <vector>
#include <algorithm>
#include <set>	
#define endl "\n"
using namespace std;

struct info {
	int from, cost;
};
vector<info> inRawdata[10003]; //inNode list�� �����
vector<int> outRawdata[10003]; //outNode list�� �����
bool visited[10003] = { false };
int duration[10003];
int leftNodesToCome[10003] = { 0 }; //�� ���;� �� node����
int runFast = 0; //���� �ʰ� �޷��;� �ϴ� ���� ����
int nodes, edges, start, finish;


void initialize() {
	cin >> nodes >> edges;

	int from, to, cost;

	for (int i = 0; i < edges; i++) {
		cin >> from >> to >> cost;
		inRawdata[to].push_back({ from, cost });
		outRawdata[from].push_back({ to });
		leftNodesToCome[to]++;
	}

	cin >> start >> finish;
}

void getminDuration(int node) {
	int numMax = 0;
	for (const auto prevNode : inRawdata[node]) {
		numMax = max(numMax, duration[prevNode.from] + prevNode.cost);
	}
	duration[node] = numMax;

	for (const auto nextNode : outRawdata[node]) {
		if (--leftNodesToCome[nextNode] == 0) {
			getminDuration(nextNode);
		}
	}
}

void roadsToGo(int startNode, int targetDist) {
	if (visited[startNode]) return;

	visited[startNode] = true;
	for (const auto prevNode : inRawdata[startNode]) {
		if (duration[prevNode.from] == targetDist - prevNode.cost) {
			runFast++;
			roadsToGo(prevNode.from, targetDist - prevNode.cost);
		}
	}
}

void operate() {
	//1.�� �ɸ��� ���� �ð� ���ϱ�
	getminDuration(start);
	int maxDuration = duration[finish];

	//2. ���� �ʰ� �޷��� �ϴ� ���� ���� ���ϱ�
	roadsToGo(finish, maxDuration);

	cout << maxDuration << endl;
	cout << runFast << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
5
7
1 2 1
1 3 3
2 3 2
2 4 1
2 5 3
3 5 1
4 5 1
1 5
ans : 4 5

7
9
1 2 4
1 3 2
1 4 3
2 6 3
2 7 5
3 5 1
4 6 4
5 6 2
6 7 5
1 7
ans : 12 5


5
7
1 2 1
1 3 3
2 3 2
2 4 1
4 5 1
3 5 1
2 5 3
1 5
ans : 4 5
*/