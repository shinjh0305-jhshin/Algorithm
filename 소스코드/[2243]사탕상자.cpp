#include <iostream>
#define endl "\n"
using namespace std;

int rawdata[1000004] = { 0 }; //index : ������ ��
int segTree[4000008] = { 0 }; //�� : �ش� ������ ���ԵǴ� ���� ���� ������ ����

void insertCandy(int left, int right, int idx, int target, int size) {
	if (right < target || target < left) return;
	segTree[idx] += size;
	if (left == right) return;

	int mid = (left + right) / 2;
	insertCandy(left, mid, idx * 2, target, size);
	insertCandy(mid + 1, right, idx * 2 + 1, target, size);
}

int withdrawCandy(int left, int right, int idx, int target, int sum) { //sum : ���� ��, target : �� ���� ������ ����
	segTree[idx]--; //���� ������ Ÿ�� ������ ��� �ִ�.
	if (left == right) return left; 

	int mid = (left + right) / 2;
	if (sum + segTree[idx * 2] >= target) { //index�� ���� �� �������� �̵��Ѵ�.
		return withdrawCandy(left, mid, idx * 2, target, sum);
	}
	else {
		sum += segTree[idx * 2];
		return withdrawCandy(mid + 1, right, idx * 2 + 1, target, sum);
	}
}

void operate() {
	int queries;
	cin >> queries;

	int op, target, size;
	for (int i = 0; i < queries; i++) {
		cin >> op;
		if (op == 1) { //���� ����
			cin >> target;
			cout << withdrawCandy(1, 1000000, 1, target, 0) << endl;
		}
		else { //���� �߰�(Ȥ�� ����)
			cin >> target >> size;
			insertCandy(1, 1000000, 1, target, size);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}

/*
100
2 5 3
2 2 4
2 3 4
2 2 -2
1 8
1 6
1 6
1 2
1 2
1 2


*/