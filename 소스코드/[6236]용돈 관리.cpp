#include <iostream>
#include <algorithm>
using namespace std;

int spendings[100003];
int days, withdraws;

void operate() {
	cin >> days >> withdraws;

	int left = -1234567890, right = 0, mid;
	for (int i = 0; i < days; i++) {
		cin >> spendings[i];

		right += spendings[i];
		left = max(left, spendings[i]);
	}

	while (left < right) {
		mid = (left + right) / 2;

		int cnt = 1, balance = mid;
		for (int i = 0; i < days; i++) {
			if (balance < spendings[i]) {
				balance = mid;
				cnt++;
			} 
			balance -= spendings[i];
		}

		if (cnt <= withdraws) right = mid; //���� Ƚ���� ��ǥ���� ���⿡, �� ���ݾ� �����ؼ� �� ���� �����ؾ� �Ѵ�.
		else left = mid + 1; //���� Ƚ���� ��ǥ���� ���⿡, �� ���� �����ؼ� �� ���ϰ� �����ؾ� �Ѵ�.
	}

	cout << left << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}