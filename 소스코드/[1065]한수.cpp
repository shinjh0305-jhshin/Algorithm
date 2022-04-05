#include <iostream>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

int operate(int target) {
	int result = 99;
	int d100; //100�� �ڸ���

	d100 = target / 100; 

	for (int i = 1; i <= d100; i++) { //100�� �ڸ��� target�� ���� �ڸ����� ���� �� ���� ����
		for (int j = 0;; j++) { //������ ���� Ȯ��

			if (i + j >= 10 || i + j + j >= 10) break; //10�� �ڸ� 1�� �ڸ� �� �ϳ��� ���� ������

			if (i < d100) result++;
			else if (d100 * 100 + (i + j) * 10 + (i + j + j) <= target) result++;
		}

		for (int j = -1;; j--) {//������ ���� Ȯ��
			if (i + j < 0 || i + j + j < 0) break; //10�� �ڸ� 1�� �ڸ� �� �ϳ��� ���� ������

			if (i < d100) result++;
			else if (d100 * 100 + (i + j) * 10 + (i + j + j) <= target) result++; 
		}
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int num;
	cin >> num;

	if (num < 100) cout << num << endl;
	else cout << operate(num) << endl;

	return 0;
}