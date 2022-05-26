#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int rawdata[100003];
int videos, disks;
vector<pair<int, int>> result;

void initialize() {
	cin >> videos >> disks;

	int sum = 0;
	for (int i = 0; i < videos; i++) {
		cin >> rawdata[i];
		sum += rawdata[i];
	}

	int dividedSum = sum / disks; //�� 1/n�� ��. �� �� ���Ϸ� ��� �켱 �߶���´�.

	sum = 0;
	for (int i = 0; i < videos; i++) {
		sum += rawdata[i];
		if (sum + rawdata[i + 1] > dividedSum) { //���� ���Ǳ��� ���� �Ұ���������.
			result.push_back({ i, sum });
			sum = 0;

			if (result.size() == disks - 1) { //���� ��ũ�� ������ ��ũ�� ������ ���� ����ִ´�.
				for (int j = i + 1; j < videos; j++) sum += rawdata[j]; 
				result.push_back({ videos - 1, sum });
				break;
			}
		}
	}
}

void operate() {
	int ans = -1;
	bool changed = true;

	while (changed) {
		changed = false;

		for (int i = 0; i < result.size() - 1; i++) {
			if (result[i].second + rawdata[result[i].first + 1] < result[i + 1].second) {
				result[i].first++;
				result[i].second += rawdata[result[i].first];
				result[i + 1].second -= rawdata[result[i].first];
				changed = true;
			}
		}
	}

	for (int i = 0; i < result.size(); i++) {
		ans = max(ans, result[i].second);
	}

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
9 3
7 3 2 4 8 1 6 4 5
*/