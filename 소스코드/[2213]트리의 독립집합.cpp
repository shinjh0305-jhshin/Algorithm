#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#pragma warning (disable:4996)
#define endl "\n"
using namespace std;

class MIND {
private:
	vector<vector<int>> tree;
	int nodes;
	int* cost;
	int** rawdata; /*�� ��庰�� ����/������ �� cost ����*/
	bool* visited;
	short* set; //0 : �Ǵ� ����, 1 :  ����, 2 : ������
	enum status { inc, exc };

public:
	MIND() :cost(NULL), rawdata(NULL), visited(NULL), set(NULL) {};

	void initialize() {
		cin >> nodes; cin.get();

		tree.resize(nodes + 1);
		cost = new int[nodes + 1];
		visited = new bool[nodes + 1];
		memset(visited, 0, nodes + 1);

		set = new short[nodes + 1];
		memset(set, 0, sizeof(short) * (nodes + 1));

		rawdata = new int*[nodes + 1];
		for (int i = 1; i <= nodes; i++) {
			rawdata[i] = new int[2];
		}

		for (int i = 1; i <= nodes; i++) {
			cin >> cost[i]; cin.get();
		}

		int node1, node2;
		for (int i = 1; i < nodes; i++) {
			cin >> node1 >> node2;
			tree[node1].push_back(node2);
			tree[node2].push_back(node1);
		}
	}

	void operate() {
		/*root�� �׻� 1�� ����*/
		dfs(1);
		print_result();
		if (rawdata[1][inc] > rawdata[1][exc]) {
			set[1] = inc + 1;
			backtracking(1, inc);
		}
		else {
			set[1] = exc + 1;
			backtracking(1, exc);
		}

		for (int i = 1; i <= nodes; i++) {
			if (set[i] == inc + 1) cout << i << ' ';
		}
		cout << endl;
	}

	void dfs(int num) {
		int mov;
		visited[num] = 1;
		rawdata[num][inc] = cost[num]; //���� ��带 ������ ��� ���� �� �ִ� �ִ�
		rawdata[num][exc] = 0; //���� ��带 �������� ��� ���� �� �ִ� �ִ�

		for (int i = 0; i < tree[num].size(); i++) {
			mov = tree[num][i];
			if (!visited[mov]) {
				dfs(mov);
				rawdata[num][inc] += rawdata[mov][exc];
				rawdata[num][exc] += max(rawdata[mov][inc], rawdata[mov][exc]);
			}
		}
	}

	void print_result() {
		cout << max(rawdata[1][inc], rawdata[1][exc]) << endl;
	}

	void backtracking(int parent, bool parent_flag) { //parent_flag�� enum status ����ȭ
		int mov;
		for (int i = 0; i < tree[parent].size(); i++) {
			mov = tree[parent][i];
			if (!set[mov]) {
				if (parent_flag == inc) { //�θ� node�� ���ԵǾ��� ��
					set[mov] = exc + 1;
					backtracking(mov, exc);
				}

				else { //�θ� node�� �����ԵǾ��� ��
					if (rawdata[mov][inc] < rawdata[mov][exc]) { //���� �ڽ� ��� �������� ����
						set[mov] = exc + 1;
						backtracking(mov, exc);
					}
					else { //���� �ڽ� ��� ������ ����
						set[mov] = inc + 1;
						backtracking(mov, inc);
					}
				}
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	MIND op;
	op.initialize();
	op.operate();
	return 0;
}