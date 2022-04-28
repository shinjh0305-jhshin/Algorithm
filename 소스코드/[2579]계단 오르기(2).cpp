#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> rawdata;
int sz_rawdata;
int dp[3][301]; //0 : �̹� ����� �� ��´�  1 : �̹� ����� ������ 1�� �������� ��°Ŵ�  2 : ...2�� �������� ��°Ŵ�

void initialize() {
	cin >> sz_rawdata;
	rawdata.resize(sz_rawdata);

	for (int i = 0; i < sz_rawdata; i++) {
		cin >> rawdata[i];
	}

	dp[0][0] = 0; dp[1][0] = rawdata[0]; dp[2][0] = 0;
}

void operate() {
	for (int i = 1; i < sz_rawdata; i++) {
		//�̹� ����� �� ��� ���. 2��� �̻� �� �پ�ѱ⿡ dp[0][i-1]�� ��� ����� �ƴϴ�.
		dp[0][i] = max(dp[1][i - 1], dp[2][i - 1]);

		//�̹� ����� ������ 1��� �������� ��� ���
		dp[1][i] = dp[0][i - 1] + rawdata[i];

		//�̹� ����� ������ 2��� �������� ��� ���
		dp[2][i] = dp[1][i - 1] + rawdata[i];
	}

	cout << max(dp[1][sz_rawdata - 1], dp[2][sz_rawdata - 1]) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
6
123
14
3
2
13
4
ans : 143
*/