#include <iostream>
#include <queue>
#include <algorithm>
#define INF 1234567890
using namespace std;

bool plugged[101] = { false };
int plugs, devices;
int rawdata[101];
priority_queue<pair<int, int>> pq;  //<������ ������ ��, �̸�> ������ ���´�.

void initialize() {
	cin >> plugs >> devices;

	for (int i = 0; i < devices; i++) {
		cin >> rawdata[i];
	}
}

int getNextTime(int curPos, int curDevice) { //������ ���� ����ϴ����� return �Ѵ�.
	int nextTime;
	for (nextTime = curPos + 1; nextTime < devices; nextTime++) {
		if (rawdata[nextTime] == curDevice) { //���Ŀ� �ٽ� ��� �� ����� ���
			return nextTime;
		}
	}
	return INF; //���Ŀ� �ٽ� ������� ���� ����� ���
}

void operate() {
	int opers = 0, nextTime, curTopDevice, curPlugged = 0;
	for (int i = 0; i < devices; i++) {
		int curDevice = rawdata[i];

		if (!plugged[curDevice] && curPlugged >= plugs) { //���� ���� ���� ����̸�, �ٸ� ��⸦ ���� �� ���
			curTopDevice = pq.top().second; pq.pop();
			plugged[curTopDevice] = false; //�ٸ� ��⸦ ����.
			opers++; //�� Ƚ�� ����
		}

		//���� ��⸦ �ȴ´�.
		//�̹� ���� ����� ���, ������ ���� ��ġ�� pq�� �����ϱ� ���� �� ������ �����Ѵ�.
		//���� �ڽ��� ��ġ ���� pq�� ���� ������, maxHeap�̱⿡ ��� ������, ������ �絵 ���⿡ �����ص� �ȴ�.

		if (!plugged[curDevice] && curPlugged < plugs) curPlugged++; //���� ���� ���� ����̸�, ���� �÷��װ� ���� ���
		nextTime = getNextTime(i, curDevice); //������ �� ��⸦ ����ϴ� ������ �����´�.
		pq.push({ nextTime, curDevice });
		plugged[curDevice] = true; //���� ���� �÷��׿� ���� ����
	}
	
	cout << opers << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
3 8
1 3 4 2 1 2 3 4
ans : 2

3 9
1 2 3 2 4 3 4 5 2
ans : 2

3 9
1 2 3 4 1 3 4 2 1
ans : 2

1 9
1 2 3 4 5 6 7 8 9
ans : 8

3 14
1 4 3 2 5 4 3 2 5 3 4 2 3 4
ans : 4
*/