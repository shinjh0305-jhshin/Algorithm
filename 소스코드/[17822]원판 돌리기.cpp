#include <iostream>
#include <cstring>
#include <stack>
#define UND 1234568790
using namespace std;

int plates, nums, rotates; //plates : ����, nums : ���� �� ����, rotate : ȸ�� Ƚ��
int rawdata[52][52];

void initialize() {
	cin >> plates >> nums >> rotates;

	for (int i = 1; i <= plates; i++) {
		for (int j = 1; j <= nums; j++) {
			cin >> rawdata[i][j];
		}
	}
}

void doRotate() { //ȸ���� ��Ų��
	//a, b, c
	//a�� ����� ������ b�������� cĭ ȸ����Ų��.

	int a, b, c;
	cin >> a >> b >> c;

	int num[52] = { 0 };

	int targetPlate, numBefore, numCurrent, idx, nextIdx;
	for (int i = 1;; i++) {
		targetPlate = i * a;
		if (targetPlate > plates) return;

		memset(num, 0, sizeof(num));

		for (int idx = 1; idx <= nums; idx++) {
			if (b == 0) { //�ð����
				nextIdx = idx + c; //���� index ����
				if (nextIdx > nums) nextIdx %= nums; //���� �ε����� ������ �Ѿ�� ���
			}
			else if (b == 1) { //�ݽð����
				nextIdx = idx - c;
				if (nextIdx <= 0) nextIdx += nums; //���� �ε����� �� �ڷ� ���� ���
			}

			num[nextIdx] = rawdata[targetPlate][idx];

		}
		for (int i = 1; i <= nums; i++) rawdata[targetPlate][i] = num[i];
	}
}

void getAdjacent() {
	int idxBefore, idxAfter, idxUp, idxDown;

	stack<pair<int, int>> st;

	for (int i = 1; i <= plates; i++) { //������ ���� �� ���� ����
		for (int j = 1; j <= nums; j++) {
			if (rawdata[i][j] == UND) continue; //������ ��
			
			idxBefore = j - 1 > 0 ? j - 1 : nums;
			idxAfter = j + 1 <= nums ? j + 1 : 1;

			if ((rawdata[i][idxBefore] == rawdata[i][j]) || (rawdata[i][idxAfter] == rawdata[i][j]) || 
				(i < plates && (rawdata[i + 1][j] == rawdata[i][j])) || (i > 1 && (rawdata[i - 1][j] == rawdata[i][j]))) {
				st.push({ i, j });
			}
		}
	}

	bool isDeleted = !st.empty();

	while (!st.empty()) {
		rawdata[st.top().first][st.top().second] = UND;
		st.pop();
	}

	if (isDeleted) return;

	// ���� �������� ���ؼ�, ������ ����� ���ؾ� �Ѵ�.
	double sum = 0, totalnums = 0;
	for (int i = 1; i <= plates; i++) {
		for (int j = 1; j <= nums; j++) {
			if (rawdata[i][j] != UND) {
				sum += rawdata[i][j];
				totalnums++;
			} 
		}
	}

	if (totalnums == 0) return;

	double average = sum / totalnums;
	for (int i = 1; i <= plates; i++) {
		for (int j = 1; j <= nums; j++) {
			if (rawdata[i][j] != UND) {
				if (rawdata[i][j] - average > 0.00000001) rawdata[i][j]--;
				else if (average - rawdata[i][j] > 0.00000001) rawdata[i][j]++;
			}
		}
	}
}

void getSum() {
	int ans = 0;
	for (int i = 1; i <= plates; i++) {
		for (int j = 1; j <= nums; j++) {
			if (rawdata[i][j] != UND) ans += rawdata[i][j];
		}
	}

	cout << ans << endl;
}

void operate() {
	for (int i = 0; i < rotates; i++) {
		doRotate();
		getAdjacent(); 
	}

	getSum();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}