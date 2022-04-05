#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

struct info {
	int front;
	int back;
	int dist;
};

vector<info> rawdata;
int numRoad, distHighway;
int dp[10005];

bool compare(const info &a, const info &b) {
	if (a.back < b.back) return true;
	return false;
}

void initialize() {
	cin >> numRoad >> distHighway;

	rawdata.resize(numRoad);
	for (int i = 0; i < numRoad; i++) {
		cin >> rawdata[i].front >> rawdata[i].back >> rawdata[i].dist;
	}

	for (int i = 0; i <= distHighway; i++) dp[i] = -1;
	sort(rawdata.begin(), rawdata.end(), compare);
}

void operate() {
	dp[0] = 0;
	int roadIdx;
	int curFront, curBack, curDist; //���� roadIdx�� ����Ű�� �ִ� �����濡 ���� ����
	int curIdx = 1; //���� ������ ����

	for (roadIdx = 0; roadIdx < numRoad; roadIdx++) {
		curFront = rawdata[roadIdx].front; curBack = rawdata[roadIdx].back; curDist = rawdata[roadIdx].dist;

		while (curIdx <= curBack) {
			if (curIdx > distHighway) goto finale;
			dp[curIdx] = dp[curIdx - 1] + 1; curIdx++;
		}

		curIdx--; //���� �� ������ �κ� �ٽ� ���ҽ�Ŵ

		if (dp[curIdx] > dp[curFront] + curDist) {
			dp[curIdx] = dp[curFront] + curDist;
		}

		curIdx++; //�ٽ� �������
	}

finale:;
	for (; curIdx <= distHighway; curIdx++) dp[curIdx] = dp[curIdx - 1] + 1; //�������� �� �� �� �κ� ����
	
	cout << dp[distHighway] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	initialize();
	operate();

	return 0;
}