#include <iostream>
#include <vector>
using namespace std;

int nodes, root, target;
vector<int> tree[52];

void initialize() {
	cin >> nodes;

	int temp;
	for (int i = 0; i < nodes; i++) {
		cin >> temp;
		if (temp == -1) {
			root = i;
			continue;
		}
		tree[temp].push_back(i);
	}

	cin >> target; //node to erase
}

int DFS(int node) {
	bool status = false; //���� ��忡�� �Ʒ� �������� DFS Ž���� �̷�� ���°�?
	int ret = 0;

	for (const auto& it : tree[node]) {
		if (it == target) continue;
		status = true;
		ret += DFS(it);
	}

	if (status == false) return 1; //�� �� �ִ� �ڽ� ��尡 ���� ���, ���� ����̴�
	else return ret; //�ڽ� ����� ���� ������ ���� ���Ѵ�
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	
	if (target == root) cout << 0 << endl;
	else cout << DFS(root) << endl;

	return 0;
}