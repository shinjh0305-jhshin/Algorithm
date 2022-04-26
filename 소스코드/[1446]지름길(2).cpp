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

	sort(rawdata.begin(), rawdata.end(), compare); //�������� ���� ��ġ ������ �����Ѵ�.
}

void operate() {
	dp[0] = 0;
	int roadIdx = 0; //���� �� ������� ������ INDEX
	int curFront, curBack, curDist; //���� roadIdx�� ����Ű�� �ִ� �����濡 ���� ����
	int curIdx = 1; //���� ������ ����

	curFront = rawdata[roadIdx].front; curBack = rawdata[roadIdx].back; curDist = rawdata[roadIdx].dist;
	for (curIdx = 1; curIdx <= distHighway; curIdx++) {
		if (curIdx < curBack) { //�� ������� �������� ���� �������� �� ���� ���
			dp[curIdx] = dp[curIdx - 1] + 1;
		}
		else { //�� ������� �������� ���� ������ �� ���
			dp[curIdx] = dp[curIdx - 1] + 1; //�ϴ� ���� �������� ���� ��츦 ������ ���´�. ����, �������� �̿��ϴ� ��츦 �����Ѵ�.
			while (curBack == curIdx) { //���� ���� ������ ���� �������� ���� �� ���� �� �ִ�.
				dp[curIdx] = min(dp[curIdx], dp[curFront] + curDist);

				roadIdx++; //���� ������� �Ѿ��.
				if (roadIdx == numRoad) { //���� �� �ִ� �������� �� �̻� ����.
					curIdx++; //�� ���� �������ʹ� finale���� å������.
					goto finale;
				}
				curFront = rawdata[roadIdx].front; curBack = rawdata[roadIdx].back; curDist = rawdata[roadIdx].dist;
			}

		}
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