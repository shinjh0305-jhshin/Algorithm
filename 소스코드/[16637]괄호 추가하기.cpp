#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string st;
int stLen, ans = -(1 << 31);

void initialize() {
	cin >> stLen >> st;
}

int calc(int num1, int num2, char op) {
	if (op == '+') return num1 + num2;
	else if (op == '-') return num1 - num2;
	else if (op == '*') return num1 * num2;
	else {
		cout << "INDEX ERROR" << endl; //for debugging
		return 0;
	}
}

void makeChoice(int resultBefore, int idx) {
	char currentOp = idx == 0 ? '+' : st[idx - 1];

	if (idx >= stLen) { //index�� ���� ������ ���� ���
		ans = max(ans, resultBefore);
		return;
	}

	//��ȣ�� index(index�� �׻� ���ڿ� ��Ī��)�� �������� �� ���ڿ� ���´�
	//1. ��ȣ�� ������ ���� ��
	int Y = calc(resultBefore, st[idx] - '0', currentOp); //���� ���ڶ� �� ���ڶ� ����Ѵ�
	makeChoice(Y, idx + 2); //�ٷ� ���� ���ڷ� �Ѿ��

	//2. ��ȣ�� ���� ��
	if (idx != stLen - 1) { //�� ������ ���ڴ� ��ȣ�� ���� ���� ���ڰ� ����
		Y = calc(st[idx] - '0', st[idx + 2] - '0', st[idx + 1]); //��ȣ ���� ���ڸ� ����Ѵ�
		int Z = calc(resultBefore, Y, currentOp); //���� ���ڶ� ��ȣ ���� ��� ����� ����Ѵ�
		makeChoice(Z, idx + 4); //���� ���� ���ڷ� �Ѿ��.
	}

}

void operate() {
	makeChoice(0, 0);
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}