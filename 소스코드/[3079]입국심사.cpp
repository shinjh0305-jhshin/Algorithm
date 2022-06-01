#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

ll desks, ppls;
ll duration[100003];

void operate() {
	ll left = 0, right = 0, mid;

	cin >> desks >> ppls;
	for (int i = 0; i < desks; i++) {
		cin >> duration[i];
		right = max(right, duration[i]);
	}
	right *= ppls / desks + 1; //�ִ� : ��� ����� �ƹ� ��� ���� ��� ����ũ�� ���� �ѷ�����.

	ll pplCapa;
	while (left < right) {
		mid = (left + right) / 2; //���� : �ð�
		pplCapa = 0; //mid�� ���� ó���� �� �ִ� �� ����� ���

		for (int i = 0; i < desks; i++) {
			pplCapa += mid / duration[i];
		}

		if (pplCapa >= ppls) right = mid;
		else left = mid + 1;
	}

	cout << left << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}