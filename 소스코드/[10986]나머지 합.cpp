#include <iostream>
#define ll long long
using namespace std;

ll mod[1003] = { 0 }; //���� ������ �տ� �ش�Ǵ� index�� ����
ll rawdata[1000003];
ll nums, target;

void initialize() {
	cin >> nums >> target;

	ll prevMod = 0; //���������� ���� ������ ��
	for (int i = 1; i <= nums; i++) {
		cin >> rawdata[i];
		prevMod = (prevMod + rawdata[i]) % target;
		mod[prevMod]++;
	}
}

void operate() {
	ll ans = 0;

	ans += mod[0];
	for (int i = 0; i < target; i++) {
		if (mod[i]) {
			ans += (mod[i] * (mod[i] - 1)) / 2;
		}
	}

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}