#include <iostream>
#include <vector>
#define endl "\n"
using namespace std;

vector<int> rawdata, temp;
int sz_rawdata;
long long result = 0;

void initialize() {
	cin >> sz_rawdata;
	rawdata.resize(sz_rawdata);
	temp.resize(sz_rawdata);

	for (int i = 0; i < sz_rawdata; i++) {
		cin >> rawdata[i];
	}
}

void merge_sort(int start_idx, int end_idx) {
	int mid = (start_idx + end_idx) / 2;

	if (end_idx - start_idx > 1) {
		merge_sort(start_idx, mid);
		merge_sort(mid + 1, end_idx);
	}

	int i = start_idx, j = mid + 1, temp_idx = start_idx;
	long long cnt = 0;

	while (i <= mid && j <= end_idx) {
		//���ʰ� �������� ���ڰ� ���� ���� ���ʿ��� ������.
		if (rawdata[i] > rawdata[j]) { //������ �������� ���ڰ� �����´�.
			temp[temp_idx++] = rawdata[j++];
			cnt++;
		}
		else { //���� �������� ���ڰ� �����´�. �����ʿ��� ������ ���ڵ�� �������� �����.
			temp[temp_idx++] = rawdata[i++];
			result += cnt;
		}
	}

	if (i > mid) { //���ʿ��� ���ڰ� �� �����Դ�
		while (j <= end_idx) temp[temp_idx++] = rawdata[j++];
	}
	else {
		while (i <= mid) {
			temp[temp_idx++] = rawdata[i++];
			result += cnt;
		}
	}

	for (int i = start_idx; i <= end_idx; i++) {
		rawdata[i] = temp[i];
	}
}

void operate() {
	merge_sort(0, sz_rawdata - 1);
	cout << result << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
6
6 4 3 2 9 3
ans : 9

6
6 4 7 2 9 3
ans : 8

8
1 3 5 7 2 4 6 8
ans : 6


3
3 2 1
ans : 3

6
1 2 3 1 1 1
ans : 6

10
11 8 2 4 3 9 6 9 7 13
ans : 17
*/