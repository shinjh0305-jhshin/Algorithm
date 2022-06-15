//LCA�� �� �ϳ��� �ٸ� �帣��.
#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <vector>
#define root 1
#define endl "\n"
using namespace std;

vector<int> tree[50003];
int depth[50003];
int parentInfo[17][50003] = { 0 }; //17 : ceil(log_2(50000))
bool visited[50003] = { false };
int nodes, height;

void initialize() {
	cin >> nodes;

	int innode, outnode;
	for (int i = 0; i < nodes - 1; i++) {
		cin >> innode >> outnode;
		tree[innode].push_back(outnode);
		tree[outnode].push_back(innode);
	}
}

void BFS() {
	queue<int> qu;
	qu.push(root);
	visited[root] = true;

	int curdepth = 0, cursize, curNode;
	while (!qu.empty()) {
		cursize = qu.size();
		while (cursize--) {
			curNode = qu.front(); qu.pop();
			depth[curNode] = curdepth;

			for (auto it : tree[curNode]) {
				if (!visited[it]) {
					visited[it] = true;
					parentInfo[0][it] = curNode;
					qu.push(it);
				}
			}
		}
		curdepth++;
	}

	height = curdepth - 1; //Ʈ���� ����
}

void getLCA() {
	int maxParent, temp = 2; //maxParent : ���������� �� 2^k�ܰ踦 �ö� �� �ִ°����� k ��
	maxParent = floor(log2(height)); //Ʈ���� ���̰� 5�� ���, ��� ����� ���̰� 2^3�̸��̱⿡ maxparent==2�� �ȴ�.
	
	for (int i = 1; i <= maxParent; i++) {
		for (int j = 1; j <= nodes; j++) {
			parentInfo[i][j] = parentInfo[i - 1][parentInfo[i - 1][j]];
		}
	}

	//������ ó���Ѵ�.
	int queries, nodeA, nodeB;
	cin >> queries;

	while (queries--) {
		cin >> nodeA >> nodeB;
		if (depth[nodeA] > depth[nodeB]) swap(nodeA, nodeB);
		
		for (int k = maxParent; k >= 0; k--) {
			if (pow(2, k) <= depth[nodeB] - depth[nodeA]) { //�ѹ��� nodeB�� 2^k ����� �ö� �Ǵ°�?
				nodeB = parentInfo[k][nodeB];
			}
		}
		/*
		31 ����� �ö�� ���� ������ ���´� ġ��.
		2^5 ����� ������ �θ� ��������, 2^4 ����� ������ �θ� �ٸ���.
		�׷� 2^4����� ������, 15����� ���� �ȴ�. (31-16=15)
		15=2^3+2^2+2^1+2^0�̱⿡, 2^3����� ���� �� �ִ������� Ž���ص� �����ϴ�.
		*/
		for (int k = maxParent; k >= 0 && nodeA != nodeB; k--) {
			if (parentInfo[k][nodeA] != parentInfo[k][nodeB]) {
				nodeA = parentInfo[k][nodeA];
				nodeB = parentInfo[k][nodeB];
			}
		}

		if (nodeA != nodeB) cout << parentInfo[0][nodeA] << endl;
		else cout << nodeA << endl;
	}
}

void operate() {
	BFS();
	getLCA();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}