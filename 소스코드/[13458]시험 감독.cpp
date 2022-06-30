#include <iostream>
#define ll long long
using namespace std;

int classes;
ll students[1000005];
ll head, sub; //head procter, sub procter�� �δ� ���� ���� �ο� ��

void initialize() {
	cin >> classes;
	for (int i = 0; i < classes; i++) {
		cin >> students[i];
	}
	cin >> head >> sub;
}

void operate() {
	ll answer = 0;
	ll subProcters = 0;

	for (int i = 0; i < classes; i++) {
		ll leftstudent = students[i];
		leftstudent -= head; answer++; //�Ѱ����� ����

		if (leftstudent > 0) { //���� �л��� ���� ���
			subProcters = leftstudent / sub; //�ΰ����� ����
			if (leftstudent - subProcters * sub > 0) subProcters++; //������ �� ���� �л��� ����������, �ΰ����� �߰� ����
			answer += subProcters;
		}
	}

	cout << answer;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}
