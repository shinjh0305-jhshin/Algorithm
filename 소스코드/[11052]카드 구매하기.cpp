#include <iostream>
#include <algorithm>
using namespace std;

int rawdata[1002], result[1002];
int sz_rawdata;

void initialize() {
	cin >> sz_rawdata;

	for (int i = 1; i <= sz_rawdata; i++) {
		cin >> rawdata[i];
	}
}

void operate() {
	for (int i = 1; i <= sz_rawdata; i++) {
		result[i] = rawdata[i];
		//ī�带 5�� �� ���
		//5+0 4+1 3+2�� Ž���ϸ�, �Ʒ��� j�� ���ϱ� �� ����(0,1,2)�� �ǹ��Ѵ�.
		for (int j = 1; j <= i / 2; j++) { 
			result[i] = max(result[i], result[j] + result[i - j]);
		}
	}

	cout << result[sz_rawdata] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}