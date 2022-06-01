#include <iostream>
#include <deque>
using namespace std;

void operate() {
	int len, del, target;
	cin >> len >> del; cin.get();

	deque<int> dq;
	for (int i = 0; i < len; i++) {
		target = cin.get() - '0';

		while (del > 0 && !dq.empty() && dq.back() < target) { //������ �� �ִ� ������ ���Ұ�, �� ���ڰ� ������ ���� �� ���� pop
			dq.pop_back();
			del--;
		}
		dq.push_back(target);
	}

	for (int i = 0; i < dq.size() - del; i++) {
		cout << dq[i];
	}

	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}