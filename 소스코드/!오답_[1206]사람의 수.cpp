#include <iostream>
#include <cmath>
#include <vector>
#define err 0.001
using namespace std;

double rawdata[52];
int sz_rawdata;

void initialize() {
	cin >> sz_rawdata;

	for (int i = 0; i < sz_rawdata; i++) {
		cin >> rawdata[i];
	}
}

void operate() {
	bool status;
	for (int i = 1; i < 1000; i++) { //��� ��
		status = true;
		for (int j = 0; j < sz_rawdata; j++) { //��հ�
			double temp = rawdata[j] * i; //�̹� ��� �� ���� ���� ��
			double nextTemp = rawdata[j] * (i + 1); //���� ��� �� ���� ���� ��

			if (temp - (int)temp < 0.00000001) continue; //������ ���
			else {
				if ((int)nextTemp - (int)temp >= 1) { //�̹� ��� �� �ȿ��� ���ڰ� �ٲ� ���. ��, ���� ��� �� ���� ���� ���� ���� �κ��� ����.
					if ((double)((int)temp + 1) / i - rawdata[j] < err) continue; //�Ҽ��� ��° �ڸ� ���Ͽ��� �ٲ� ���
				}
				status = false;
				break;
			}
		}

		if (status == true) {
			cout << i << endl;
			return;
		}
	}

	cout << 1000 << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}