#include <iostream>
#include <queue>
#include <iostream>
#include <deque>
using namespace std;

deque<pair<int, int>> dq; //index, num

int nums, len; // len�� 3�̰�, index�� 3�̸� �̴� index 5���� ��ȿ�� ����.

void initialize() {
	cin >> nums >> len;
}

void operate() {
	int inCome;

	for (int i = 0; i < nums; i++) {
		cin >> inCome;
		while (!dq.empty() && dq.back().second > inCome) dq.pop_back();
		dq.push_back({ i, inCome });

		while (dq.front().first + len <= i) dq.pop_front();

		cout << dq.front().second << ' ';
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}