#include <iostream>
#include <algorithm>
#define endl "\n"
using namespace std;

int tite[500002] = { 0 }, mite[500002] = { 0 }; //index : ����
int num_rawdata, height;

void initialize() {
	cin >> num_rawdata >> height;

	int temp;
	for (int i = 0; i < num_rawdata; i++) {
		cin >> temp; //���̰� ���´�

		if (i % 2) tite[temp]++;
		else mite[temp]++;
	}
}

void operate() {
	int miteSum = 0, titeSum = 0; //�ν��� �ϴ� �� ������ ����
	int minSum = 1234567890, mins = 0;

	for (int i = 1; i < height; i++) miteSum += mite[i]; //���̴� height ���ٴ� �۴�
	titeSum = tite[height]; //1������ �����Ѵ�

	int tempSum;
	for (int i = 1; i <= height; i++) { //1������ height(�����) ������ Ž���Ѵ�
		tempSum = miteSum + titeSum;
		if (tempSum < minSum) { //���ο� min �߰�
			minSum = tempSum;
			mins = 1;
		}
		else if (tempSum == minSum) mins++; //���� min������ �߰�!

		miteSum -= mite[i];
		titeSum += tite[height - i];
	}

	cout << minSum << ' ' << mins << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}