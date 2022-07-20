#include <iostream>
#include <algorithm>
#define endl "\n"
using namespace std;

/*
����
1. Ű ������ ������������ �����Ѵ�
2. ���� S�� �� �ں��� �����Ѵ�.
3-1. ����Ʈ���� ���� Ű ���� �������� ����� Ű�� ������
3-2. ���� S�� �� ���� ������ ���� �� �ִ� Ű�� ���� ã�´�.
3-3. �ش� Ű�� �����ϴ� ����Ʈ���� ������ ���� ���Ѵ�
*/

//����Ʈ���δ� �����ϱ� ���� �� ����
int sz_rawdata;
int heightData[100003], orderData[100003], result[100003], segTree[400012];

void update(int target, int left = 1, int right = sz_rawdata, int idx = 1) {
	if (left <= target && target <= right) segTree[idx]++;
	else return;

	if (left == right) return;

	int mid = (left + right) / 2;
	update(target, left, mid, idx * 2);
	update(target, mid + 1, right, idx * 2 + 1);
}

int getIdx(int targetOrder, int left = 1, int right = sz_rawdata, int idx = 1, int sum = 0) {
	if (left == right) return right;
	int used = segTree[idx]; //left���� right���� Ű �߿��� ����� Ű�� ����
	int avail = sum + (right - left + 1 - used); //���� �������� ����� �� �ִ� Ű�� ����

	int mid = (left + right) / 2;
	int leftAvail = mid - left + 1 - segTree[2 * idx];
	int newSum = sum + leftAvail; //���� ���ݿ��� ����� �� �ִ� ��

	if (newSum >= targetOrder) return getIdx(targetOrder, left, mid, idx * 2, sum); //���� ���� ������ �����Ѵ�.
	else return getIdx(targetOrder, mid + 1, right, idx * 2 + 1, newSum);
}

void initialize() {
	cin >> sz_rawdata;
	for (int i = 1; i <= sz_rawdata; i++) {
		cin >> heightData[i];
	}
	for (int i = 1; i <= sz_rawdata; i++) {
		cin >> orderData[i];
	}

	sort(heightData + 1, heightData + sz_rawdata + 1);
}

void operate() {
	int target;
	for (int i = sz_rawdata; i > 0; i--) {
		target = getIdx(orderData[i] + 1);
		result[i] = heightData[target];
		update(target);
	}

	for (int i = 1; i <= sz_rawdata; i++) {
		cout << result[i] << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}