#include <iostream>
#include <algorithm>
using namespace std;

//toLeft : �����ʿ��� �����ϴ� LIS�� ���� ����
//toRight : ���ʿ��� �����ϴ� LIS�� ���� ����
//workspace : LIS�� ���ϸ鼭 ����� �۾� ����
int rawdata[1003], toLeft[1003], toRight[1003], workspace[1003];
int sz_rawdata;

void initialize() {
	cin >> sz_rawdata;
	for (int i = 0; i < sz_rawdata; i++) {
		cin >> rawdata[i];
	}
}

void make_forward() { //LIS�� ���������� ���� �������� ���Ѵ�.
	int idx = 0;
	workspace[0] = rawdata[0];
	toRight[0] = 1;

	for (int i = 1; i < sz_rawdata; i++) {
		if (rawdata[i] > workspace[idx]) {
			workspace[++idx] = rawdata[i];
			toRight[i] = idx + 1;
		}
		else {
			auto it = lower_bound(workspace, workspace + idx, rawdata[i]);
			*it = rawdata[i];
			toRight[i] = it - workspace + 1;
		}
	}
}

void make_backward() { //LIS�� �������� ���� �������� ���Ѵ�.
	int idx = 0;
	workspace[0] = rawdata[sz_rawdata - 1];
	toLeft[sz_rawdata - 1] = 1;

	for (int i = sz_rawdata - 2; i >= 0; i--) {
		if (rawdata[i] > workspace[idx]) {
			workspace[++idx] = rawdata[i];
			toLeft[i] = idx + 1;
		}
		else {
			auto it = lower_bound(workspace, workspace + idx, rawdata[i]);
			*it = rawdata[i];
			toLeft[i] = it - workspace + 1;
		}
	}
}
void operate() {
	//������, ������ ������ ���� LIS�� ���ϰ� �� ���� ���� ū ������ ����.
	make_forward();
	make_backward();

	int result = -1;
	for (int i = 0; i < sz_rawdata; i++) {
		result = max(result, toRight[i] + toLeft[i]);
	}
	cout << result - 1 << endl; //��� ���ڰ� �� �� ���� �� �� ���ش�.
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}