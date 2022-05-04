#include <iostream>
#include <algorithm>
#define endl "\n"
#pragma warning(disable:4996)
using namespace std;

struct info {
	int duration, price;
};

info rawdata[17];
int dp[17] = { 0 };
int days;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> days; cin.get();
	for (int i = 1; i <= days; i++) {
		cin >> rawdata[i].duration >> rawdata[i].price; cin.get();
	}
	
	int nextStart, temp, temp1, temp2;
	for (int i = days; i >= 1; i--) { //���� ������ ��Ȯ�ϰ�, ���� ������ �Ѵ� ���� ������ ������ �� ���⿡ ���������� Ž���Ѵ�.
		nextStart = i + rawdata[i].duration; //���� ����� ������ �� �ִ� ��

		temp1 = temp2 = 0;

		//i�Ͽ� �����ϴ� ������ ���� ���� ���� ����Ѵ�.(temp1)
		if (nextStart <= days + 1) { //i�Ͽ� �����ϴ� ������ ���� �� �ִ��� Ȯ��
			temp1 = rawdata[i].price; temp = 0;
			for (int j = nextStart; j <= days; j++) {
				temp = max(temp, dp[j]);
			}
			temp1 += temp;
		}

		//i�Ͽ� �����ϴ� ������ ���� ���� ���� ����Ѵ�.(temp2)
		for (int j = i + 1; j <= days; j++) {
			temp2 = max(temp2, dp[j]);
		}

		dp[i] = max(temp1, temp2);
	}

	cout << dp[1] << endl;

	return 0;
}