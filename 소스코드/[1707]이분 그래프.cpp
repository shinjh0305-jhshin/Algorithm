//�׷����� DFS Ž���� �ϸ鼭
//���� ����� node�� ������ ���� ���� ��Ȳ�ۿ� �߻��� �� ������
//�̺� �׷����� �� ����� ���̴�.

#include <iostream>
#include <vector>
#include <cstring>
#define type1 1 //��ĥ�� ����
#define type2 2
using namespace std;

vector<int> map[20003];
int visited[20003];
int nodes, edges;

void initialize() {
	int from, to;
	
	cin >> nodes >> edges;
	for (int i = 1; i <= nodes; i++) map[i].clear();

	for (int i = 0; i < edges; i++) {
		cin >> from >> to;
		map[from].push_back(to);
		map[to].push_back(from);
	}

	memset(visited, 0, sizeof(visited));
}

bool DFS(int num, int previousType) {
	int currentType = visited[num] = previousType == type1 ? type2 : type1; //���� Ÿ�԰� �ݴ�Ǵ� ������ ����

	for (auto nextNode : map[num]) {
		if (visited[nextNode] && visited[nextNode] == currentType) { //�湮�� �� �ִ� ����, ���� ���� ������ �Ȱ���.
			return false;
		}
		else if (!visited[nextNode]) {
			if (DFS(nextNode, currentType) == false) { //����...
				return false;
			}
		}
	}
	
	return true;
}

void operate() {
	for (int i = 1; i <= nodes; i++) {
		if (!visited[i]) {
			if (!DFS(i, type2)) { //ù ������ type1�� �Ѵ�.
				cout << "NO" << endl;
				return;
			}
		}
	}

	cout << "YES" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int cases;
	cin >> cases;
	
	while (cases--) {
		initialize();
		operate();
	}


	return 0;
}