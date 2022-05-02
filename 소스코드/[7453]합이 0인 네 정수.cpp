#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> a, b, c, d, frontHalf, backHalf;
int sz_vector;

void initialize() {
	cin >> sz_vector;
	a.resize(sz_vector); b.resize(sz_vector); c.resize(sz_vector); d.resize(sz_vector);
	frontHalf.resize(sz_vector*sz_vector); backHalf.resize(sz_vector * sz_vector);

	for (int i = 0; i < sz_vector; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	}

	int idx = 0;
	for (int i = 0; i < sz_vector; i++) {
		for (int j = 0; j < sz_vector; j++) {
			frontHalf[idx] = a[i] + b[j]; //a�� b�� ������ ���� ���� ��� ���� 
			backHalf[idx++] = c[i] + d[j]; //c�� d�� ������ ���� ���� ��� ����
		}
	}

	sort(backHalf.begin(), backHalf.end());
}

void operate() {
	long long ans = 0, upper, lower, sum_temp = 0;

	//��� 1
	int iter = sz_vector * sz_vector;
	for (int i = 0; i < iter; i++) {
		ans += upper_bound(backHalf.begin(), backHalf.end(), -frontHalf[i]) - lower_bound(backHalf.begin(), backHalf.end(), -frontHalf[i]);
	}

	//���2
	//for (int i = 0; i < sz_vector; i++) {
	//	for (int j = 0; j < sz_vector; j++) {
	//		sum_temp = a[i] + b[j];

	//		upper = upper_bound(backHalf.begin(), backHalf.end(), -sum_temp) - backHalf.begin();
	//		lower = lower_bound(backHalf.begin(), backHalf.end(), -sum_temp) - backHalf.begin();

	//		ans += (upper - lower);
	//	}
	//}

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}