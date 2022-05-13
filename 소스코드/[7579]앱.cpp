#include <iostream>
#include <algorithm>
#define INF 1234567890
using namespace std;

int N, M;
int dp[2][10005] = { 0 };
int memory[102], cost[102];
int cur = 0, previous = 1, sum = 0;

//Row : Ž���� ��ģ ���� ����, Col : ���
//dp���� Row���� ���� Ž������ ��, Col�� ������� ���� �� �ִ� �޸��� �ִ��� ����,
//������ Row���� M���� ũ�ų� ���� ���� ������ Col ���� �����̴�.

void initialize() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> memory[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> cost[i];
		sum += cost[i];
	}

}

void operate() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= sum; j++) {
			if (j < cost[i]) {
				dp[cur][j] = dp[previous][j];
			}
			else {
				dp[cur][j] = max(dp[previous][j - cost[i]] + memory[i], dp[previous][j]);
			}
		}
		swap(cur, previous);
	}

	for (int i = 0; i <= sum; i++) {
		if (dp[previous][i] >= M) {
			cout << i << endl;
			break;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}