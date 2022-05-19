#include <iostream>
#include <vector>
#include <algorithm>
#define INF 1234567890
using namespace std;

vector<int> rawdata;
int dp[10003];
int types, target;

void initialize() {
	cin >> types >> target;
	rawdata.resize(types);

	for (int i = 0; i < types; i++) {
		cin >> rawdata[i];
	}

	sort(rawdata.begin(), rawdata.end());
	rawdata.erase(unique(rawdata.begin(), rawdata.end()), rawdata.end());
	types = rawdata.size();
}

void operate() {
	int val;
	
	dp[0] = 0;
	for (int i = 1; i <= target; i++) {
		dp[i] = INF;
		for (int j = 0; j < types; j++) {
			val = rawdata[j];
			if (val > i) break; //���� ������ ��ġ�� ���� Ÿ�� �ݾ׺��� �� Ŭ ��
			if (dp[i - val] == INF) continue; //���� �ܰ� �ݾ��� ���� �� ���� �ݾ��� ��

			dp[i] = min(dp[i], dp[i - val] + 1);
		}
	}

	if (dp[target] == INF) cout << -1 << endl;
	else cout << dp[target] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
4 15
1
5
12
5
*/