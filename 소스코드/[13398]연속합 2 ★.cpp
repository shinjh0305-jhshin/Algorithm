#include <iostream>
#include <algorithm>
using namespace std;

int dp[2][100005]; //���� �� �� ��, ���� 1�� �� ��
int rawdata[100005];
int sz_rawdata;

void initialize() {
	cin >> sz_rawdata;
	for (int i = 0; i < sz_rawdata; i++) {
		cin >> rawdata[i];
	}

	dp[0][0] = dp[1][0] = rawdata[0];
}

void operate() {
	int maxNum = rawdata[0];

	for (int i = 1; i < sz_rawdata; i++) {
		//dp[0] : �տ� �ִ� �����տ� �� ���̴°� ������, ���� ���ο� �������� �����ϴ°� ������
		dp[0][i] = max(dp[0][i - 1] + rawdata[i], rawdata[i]);
		//dp[1] : �տ� �ִ� �������� �ּ��ΰŴ� �˰ڴ�. ���࿡ ���� ����...?? ���߿� �� ��������...?? 
		dp[1][i] = max(dp[0][i - 1], dp[1][i - 1] + rawdata[i]); //���� �� �Ͱ�, �̹� ���� ���� ���翡 �� �߰���Ű�� �� �� �ִ�
		maxNum = max(maxNum, max(dp[0][i], dp[1][i]));
	}

	cout << maxNum << endl;
}	

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}