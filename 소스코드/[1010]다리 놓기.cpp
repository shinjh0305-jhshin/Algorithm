#include <iostream>
#include <ctime>
#define endl "\n"
using namespace std;

int dp[32][32] = { 0 }; //ROW : ���� ������ ����, COL : ������ ������ ����

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int cases, rTarget, cTarget;

	cin >> cases; cin.get();

	//���� ������ 1���� ���� ������ ������ ������ŭ ����� ���� �����.
	for (int i = 1; i <= 29; i++) dp[1][i] = i; //�ʱ�ȭ

	for (int i = 2; i <= 29; i++) { //���� ������ �ִ� ������ŭ �̸� �۾��صд�.
		for (int j = i; j <= 29; j++) { //������ ������ ���� ������ �������� �ִ� �������� �þ��.
			//dp[i][j]�� dp[i-1][j-1]���� dp[i-1][1]���� ���� ���ε�,
			//dp[i-1][j-2]���� dp[i-1][1]���� ���� ���� dp[i][j-1]�� ����Ǿ� �ֱ⿡ �̸� ������ ����.
			dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
		}
	}

	for (int i = 0; i < cases; i++) {
		cin >> rTarget >> cTarget; cin.get();
		cout << dp[rTarget][cTarget] << endl;
	}

	return 0;

}