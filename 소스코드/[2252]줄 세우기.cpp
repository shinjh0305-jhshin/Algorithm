#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#pragma warning (disable:4996)
#define endl "\n"
using namespace std;

class height {
private:
	vector<int>* rawdata;
	int* in_order;
	int ppl, rule;

public:
	void initialize() {
		cin >> ppl >> rule; cin.get();

		rawdata = new vector<int>[ppl + 1];
		in_order = new int[ppl + 1];
		memset(in_order, 0, sizeof(int)*(ppl + 1));

		int front, rear;
		for (int i = 0; i < rule; i++) {
			cin >> front >> rear; cin.get();
			rawdata[front].push_back(rear);
			in_order[rear]++;
		}
	}

	void operate() {
		//next : in_order�� 0�� ��带 ��� ť
		//order : Ű �� ����(���)�� ��� ť
		queue<int> order, next;

		int temp, mov;

		for (int i = 1; i <= ppl; i++) { //in_order�� 0�� ����� �ִ´�.
			if (in_order[i] == 0) next.push(i);
		}

		while (order.size() != ppl) { //��� ����� order�� �� �� ����
			temp = next.front(); next.pop(); //�ϳ��� ������
			order.push(temp);

			mov = 0;
			while (mov != rawdata[temp].size()) {
				if (--in_order[rawdata[temp][mov]] == 0) { //in_order�� �ϳ��� ���δ�
					next.push(rawdata[temp][mov]);
				}
				mov++;
			}
		}

		while (!order.empty()) { //���
			cout << order.front() << ' ';
			order.pop();
		}
		cout << endl;
	}
};

int main() {
	ios::sync_with_stdio(false);
	height op;
	op.initialize();
	op.operate();
	return 0;
}