#include <iostream>
#include <vector>	
#include <algorithm>
#define endl "\n"
using namespace std;

//dp[0] : �̹� ���� �ִ� ��ƼĿ�� ���� �ʴ´�.
//dp[1] : ���� �ִ� ��ƼĿ�� ����.
//dp[2] : �Ʒ��� �ִ� ��ƼĿ�� ����.
int dp[3][100003], rawdata[2][100003];
int sz_rawdata;

void initialize() {
	cin >> sz_rawdata;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < sz_rawdata; j++) {
			cin >> rawdata[i][j];
		}
	}
	dp[0][0] = 0; dp[1][0] = rawdata[0][0]; dp[2][0] = rawdata[1][0];
}

void operate() {
	for (int i = 1; i < sz_rawdata; i++) {
		dp[0][i] = max(dp[0][i - 1], max(dp[1][i - 1], dp[2][i - 1])); //���� �ܰ��� �ƹ��ų� �� max ����´�
		dp[1][i] = max(dp[0][i - 1], dp[2][i - 1]) + rawdata[0][i]; //���� �ܰ迡�� �� �� ���, �Ʒ� ��ƼĿ �� ��� �� max�� ����´�
		dp[2][i] = max(dp[0][i - 1], dp[1][i - 1]) + rawdata[1][i]; //���� �ܰ迡�� �� �� ���, �� ��ƼĿ �� ��� �� max�� ����´�
	}
	cout << max(dp[0][sz_rawdata - 1], max(dp[1][sz_rawdata - 1], dp[2][sz_rawdata - 1])) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int cases;
	cin >> cases;
	
	for (int i = 0; i < cases; i++) {
		initialize();
		operate();
	}

	return 0;
}