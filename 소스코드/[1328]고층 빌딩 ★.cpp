/*
���� ���� ������ ���̴� ���� �����غ���. (N = 5, L = 3, R = 2�� ����)
��� 1 : N = 4, L = 2, R = 2�� ��Ȳ���� �� ���ʿ� ������ �ٴ� ���
��� 2 : N = 4, L = 3, R = 1�� ��Ȳ���� �� �����ʿ� ������ �ٴ� ���
��� 3 : N = 4, L = 3, R = 2�� ��Ȳ���� ���̻��̿� ������ ���� ��� N - 1���� ��ġ ����.

���� ���� ������ ���� ���̻��̿� �������� ������ ���� ������ �ʰ� �ǹǷ�,
��� 3�� �����ϱⰡ ��������.
*/

#include <iostream>
#define MOD 1000000007
using namespace std;

long long dp[102][102][102] = { 0 }; //dp[N�� �ǹ�][���ʿ��� ���̴� �ǹ� ����][�����ʿ��� ���̴� �ǹ� ����]
int L, R, N;

void operate() {
	cin >> N >> L >> R;
	dp[1][1][1] = 1; 

	for (int num = 2; num <= N; num++) {
		for (int left = 1; left <= L; left++) {
			for (int right = 1; right <= R; right++) {
				dp[num][left][right] = 
					(dp[num - 1][left - 1][right] + dp[num - 1][left][right - 1] + dp[num - 1][left][right] * (num - 2)) % MOD;
			}
		}
	}

	cout << dp[N][L][R] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}