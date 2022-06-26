//�޸������̼� Ǯ�� �̿ϼ�(�Ұ�)
//�޸������̼��� ���ؼ��� ��� ��Ȳ�� ���ؼ� �ش� ���� �����ϴ� ���� ����Ǿ�� �ϳ�.
//�׷����� Ž�� ���������� �� ��带 �湮���� ��, ���� �湮 ��忡 ���� ó���� �Ұ����ϱ⿡
//�޸������̼��� ���ؼ��� ���� �󿡼� Ư�� ������ �־����� �Ѵ�.

#include <iostream>
#include <vector>
#include <algorithm>
#define MIN -1
using namespace std;

vector<pair<int, int>> map[100005]; //{node, cost}
int maxWeight[100005]; //�� ��忡�� �� ���� �� �� �ִ� ������ �޸������̼�
int nodes, edges, startNode, endNode;

void initialize() {
	cin >> nodes >> edges;

	int nodeA, nodeB, cost;
	for (int i = 0; i < edges; i++) {
		cin >> nodeA >> nodeB >> cost;
		map[nodeA].push_back({ nodeB, cost });
		map[nodeB].push_back({ nodeA, cost });
	}

	for (int i = 1; i <= nodes; i++) {
		maxWeight[i] = MIN; //�ּ� ���Է� �����Ѵ�.
	}
	maxWeight[endNode] = 2134567890; //�������� max weight�� �༭, ������ lower_bound�� �޸������̼ǿ� ������ ������ �Ѵ�.
}

bool DFS(int node) {
	int sz_map = map[node].size(), nextNode;
	for (int i = 0; i < sz_map; i++) {
		nextNode = map[node][i].first;
		if (maxWeight[nextNode] != MIN) { //�湮�� �� �ִ�.
			maxWeight[node] = max(maxWeight[node], min(map[node][i].second, maxWeight[nextNode])); //�� �� �ִ� ���� �߿��� �ִ��� ã�´�.
		}
		else { //���� �湮�ؾ� �Ѵ�.
			if (DFS(nextNode)) { //���������� ���� �� �� �ִ� ��� ���� ��带 �湮�ߴ�.
				//�� �� �ִ� ���� �߿��� �ִ��� ã�´�. min() : ���� ��忡�� ���� ���� ���� �ٸ� ��� ���Կ�, ���� ��忡�� �� ���� ���� �ؼ� �������� �� �� �ִ� �ִ� ���� �� �ּڰ�
				maxWeight[node] = max(maxWeight[node], min(map[node][i].second, maxWeight[nextNode])); 
			}
		}
	}

	if (maxWeight[node] != MIN) return true; //���� ��带 ���� ������ �� �� �ִ� �ִ� ���԰� �����.
	else return false;
}