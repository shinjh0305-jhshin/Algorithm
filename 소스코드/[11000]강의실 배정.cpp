#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<pair<int, int>> rawdata; //���� ���۽ð�, ����ð��� ���� ����
priority_queue<int, vector<int>, greater<int>> classList; //�� ���ǽ��� ���� �ð� ����
int lectures;

void initialize() {
	cin >> lectures;
	rawdata.resize(lectures);

	for (int i = 0; i < lectures; i++) {
		cin >> rawdata[i].first >> rawdata[i].second;
	}

	sort(rawdata.begin(), rawdata.end());
}

void operate() {
	int timeEnd, timeStart; //�� ���� �� ���� �� ���� �ð�

	classList.push(rawdata[0].second); //ù ������ �ְ� �����Ѵ�.
	for (int i = 1; i < lectures; i++) {
		timeStart = rawdata[i].first; timeEnd = rawdata[i].second;

		if (classList.top() <= timeStart) classList.pop(); //���� ���� ����
		classList.push(timeEnd); //���ο� ���� �ִ´�
	}
	cout << classList.size() << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
11
1 3
3 5
5 6
6 7
7 11
2 4
4 5
6 8
11 13
3 6
6 12
*/