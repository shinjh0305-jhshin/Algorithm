#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> duration, answer, previous; 
vector<int> previousHouse[502], afterHouse[502]; //previous : �� ���� ���� ������ ����� �� ��, after : �� ���� ���� ���� ���� �� �ִ� ��
queue<int> qu; //������ ����� �� ���� �� �������� ���� ���� �� �ִ� ��
int sz_house; //�� ����

void initialize() {
	cin >> sz_house;
	duration.resize(sz_house + 1); //�� �� �� ä�� ���� �� �ɸ��� �ð�
	answer.resize(sz_house + 1, 0); //�� ��ä�� ���� �� �ɸ��� ���� �ð�
	previous.resize(sz_house + 1, 0); //�� ���� ���� ������ ����� �� ���� ����

	int temp;
	for (int i = 1; i <= sz_house; i++) {
		cin >> duration[i];

		while (1) {
			cin >> temp;
			if (temp == -1) break;

			previous[i]++;
			previousHouse[i].push_back(temp);
			afterHouse[temp].push_back(i);
		}
	}

	for (int i = 1; i <= sz_house; i++) {
		if (previous[i] == 0) {
			qu.push(i);
			answer[i] = duration[i];
		}
	}
}

void operate() {
	int curHouse, nextHouses, nextHouse, temp, previousSize;

	while (!qu.empty()) {
		curHouse = qu.front(); qu.pop(); //���� ���� �� �ִ� ��(���� ��)

		nextHouses = afterHouse[curHouse].size(); //���� ���� ���� ������ ���� ����

		for (int i = 0; i < nextHouses; i++) {
			nextHouse = afterHouse[curHouse][i]; //���� ���� ���� ������ ��

			if (--previous[nextHouse] == 0) { //���� ������ ������ �� �������� ���
				qu.push(nextHouse);

				temp = 0;
				previousSize = previousHouse[nextHouse].size(); //���� ������ ������ ����
				for (int iter = 0; iter < previousSize; iter++) {
					temp = max(temp, answer[previousHouse[nextHouse][iter]]); //���� ������ ���� �� �ִ� �ҿ�ð��� ���Ѵ�
				}
				answer[nextHouse] = temp + duration[nextHouse];
			}
		}
	}

	for (int i = 1; i <= sz_house; i++) {
		cout << answer[i] << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
8
4 -1
2 1 -1
5 2 8 -1
8 3 -1
3 2 -1
1 3 5 -1
4 4 6 -1
28 -1

answer :
4
6
33
41
9
34
45
28
*/