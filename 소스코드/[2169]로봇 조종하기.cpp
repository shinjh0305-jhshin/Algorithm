#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

int rawdata[1003][1003];
vector<int> from_right, from_left, prev_result;
int rows, cols;

void initialize() {
	cin >> rows >> cols;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> rawdata[i][j];
		}
	}

	from_right.resize(cols);
	from_left.resize(cols);
	prev_result.resize(cols);

	prev_result[0] = rawdata[0][0];
	for (int i = 1; i < cols; i++) {
		prev_result[i] = prev_result[i - 1] + rawdata[0][i];
	}
}

void get_left(int row) { //�� Ȥ�� ���ʿ��� ���� ��� �� ���� ���� �� ū ���� �����Ѵ�
	from_left[0] = rawdata[row][0] + prev_result[0]; //���� ���� ĭ�� �������ۿ� �� �´�

	for (int i = 1; i < cols; i++) {
		from_left[i] = max(prev_result[i], from_left[i - 1]) + rawdata[row][i];
	}
}

void get_right(int row) { //�� �Ǵ� �����ʿ��� ���� ��� �� ���� ���� �� ū ���� �����Ѵ�
	from_right[cols - 1] = rawdata[row][cols - 1] + prev_result[cols - 1]; //���� ������ ĭ�� �������ۿ� �� �´�

	for (int i = cols - 2; i >= 0; i--) {
		from_right[i] = max(prev_result[i], from_right[i + 1]) + rawdata[row][i];
	}
}

void get_max() {
	for (int i = 0; i < cols; i++) { //���� Ȥ�� ������ ��� �� �� ū ���� �����Ѵ�.
		prev_result[i] = max(from_left[i], from_right[i]);
	}
}

void operate() {
	for (int i = 1; i < rows; i++) {
		get_left(i);
		get_right(i);
		get_max();
	}

	cout << prev_result[cols - 1] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}