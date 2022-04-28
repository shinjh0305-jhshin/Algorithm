#include <iostream>
#include <vector>
using namespace std;

vector<int> segTree(800016), rawdata(200004), index(100002), result(100002);
int test_cases, movies, queries, sz_rawdata;

/*
1. segTree�� (������)+(��ȭ��)�� �̷������.
2. �����δ� ���� 0���� ��ȭ�δ� ���� 1�� ä���ִ´�.
3. ��ȭ�� ���� �����ϸ� �ش� ��ȭ�� �������� �� ������ ������ �׾Ƴ����� �����Ѵ�. �� �� ��ȭ�� �ٲ� index�� index ���Ϳ��� �����Ѵ�.
4. ��ȭ ���� �ִ� ��ȭ�� ������, ��ȭ index�� �ٲ�� ������ index - 1 ������ �������̴�.
*/

int makeSegTree(int left, int right, int idx) {
	if (left == right) return segTree[idx] = rawdata[left];
	
	int mid = (left + right) / 2;
	return segTree[idx] = makeSegTree(left, mid, idx * 2) + makeSegTree(mid + 1, right, idx * 2 + 1);
}

int getQuery(int left, int right, int queryLeft, int queryRight, int idx) {
	if (queryRight < left || right < queryLeft) return 0;
	if (queryLeft <= left && right <= queryRight) return segTree[idx];
	
	int mid = (left + right) / 2;
	return getQuery(left, mid, queryLeft, queryRight, idx * 2) + getQuery(mid + 1, right, queryLeft, queryRight, idx * 2 + 1);
}

void changeSegTree(int left, int right, int dataIdx, int diff, int treeIdx) {
	if (left <= dataIdx && dataIdx <= right) {
		segTree[treeIdx] += diff;
		
		if (left == right) return;

		int mid = (left + right) / 2;
		changeSegTree(left, mid, dataIdx, diff, treeIdx * 2);
		changeSegTree(mid + 1, right, dataIdx, diff, treeIdx * 2 + 1);
	}
}

void initialize() {
	cin >> movies >> queries;

	sz_rawdata = movies + queries;

	for (int i = 1; i <= queries; i++) {
		rawdata[i] = 0; //rawdata : ���� �κ��� ���� 0���� ä���ְ�, ��ȭ �κи� 1�� ä���ִ´�,
	}

	for (int i = 1; i <= movies; i++) {
		index[i] = queries + i; //index : rawdata �󿡼� �Ϸù�ȣ�� i�� ��ȭ�� index
		rawdata[queries + i] = 1;
	}

	makeSegTree(1, sz_rawdata, 1);
}

void operate() {
	int targetMovie;
	for (int i = 0; i < queries; i++) {
		cin >> targetMovie;
		result[i] = getQuery(1, sz_rawdata, 1, index[targetMovie] - 1, 1); //��ȭ �տ� �ִ� ��ȭ�� ������ ���ؿ´�.

		//��ȭ�� ��ġ�� �� ���� �÷����´�.
		rawdata[index[targetMovie]] = 0; //������ �ִ� ��ġ�� 0���� �����.
		changeSegTree(1, sz_rawdata, index[targetMovie], -1, 1);

		index[targetMovie] = queries - i;
		rawdata[index[targetMovie]] = 1; //���ο� ��ġ�� 1�� �����.
		changeSegTree(1, sz_rawdata, index[targetMovie], 1, 1);
	}

	for (int i = 0; i < queries; i++) {
		cout << result[i] << ' ';
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> test_cases;
	for (int i = 0; i < test_cases; i++) {
		initialize();
		operate();
	}
	return 0;
}
/*
1
5 3
4 4 5
ans : 3 0 4


*/