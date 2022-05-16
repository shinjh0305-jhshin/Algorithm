#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define endl "\n"
#define INF 12345678
using namespace std;

struct info {
	int key, root;
};
info rawdata[103];
int ppl;
int dist[103][103];
vector<int> head;

bool compare(const info& a, const info& b) {
	if (a.root < b.root) return true;
	return false;
}

int getRoot(int num) {
	if (rawdata[num].root < 0) return num;
	else return rawdata[num].root = getRoot(rawdata[num].root);
}

void mergeRoot(int num1, int num2) {
	int root1 = getRoot(num1);
	int root2 = getRoot(num2);

	if (root1 == root2) return;

	if (rawdata[root2].root < rawdata[root1].root) swap(root1, root2);

	rawdata[root1].root += rawdata[root2].root;
	rawdata[root2].root = root1;
}

void get_dist() {
	for (int k = 1; k <= ppl; k++) {
		for (int i = 1; i <= ppl; i++) {
			if (dist[i][k] == INF) continue;
			for (int j = i + 1; j <= ppl; j++) {
				dist[i][j] = dist[j][i] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

void initialize() {
	int relations;
	cin >> ppl >> relations;

	for (int i = 1; i <= ppl; i++) { 
		rawdata[i].key = i;
		rawdata[i].root = -1;
	}

	for (int i = 1; i <= ppl; i++) { //dist �ʱ�ȭ
		for (int j = i + 1; j <= ppl; j++) {
			dist[i][j] = dist[j][i] = INF;
		}
		dist[i][i] = 0;
	}

	int num1, num2;
	for (int i = 0; i < relations; i++) {
		cin >> num1 >> num2;
		mergeRoot(num1, num2);
		dist[num1][num2] = dist[num2][num1] = 1;
	}

	for (int i = 1; i <= ppl; i++) getRoot(i); //���� ��Ʈ�� �Ÿ��� 1�� �����

	sort(rawdata + 1, rawdata + ppl + 1, compare); //��Ʈ�� ������ ������� �� ������ ������.
	get_dist();
}

void find_head(int start, int finish) {
	int minValue = 1234567890, minHead, tempMax, begin, end;
	int root = rawdata[start].root;

	for (int i = start; i <= finish; i++) { //������ �ĺ��� index
		tempMax = 0;
		begin = rawdata[i].key; //������ �ĺ���

		for (int j = start; j <= finish; j++) {
			end = rawdata[j].key; //������
			tempMax = max(tempMax, dist[begin][end]);
		}
		tempMax = max(tempMax, dist[begin][root]);

		if (tempMax < minValue) {
			minValue = tempMax;
			minHead = begin;
		}
	}

	tempMax = 0; //��Ʈ���� �����ϴ� ��츦 ����Ѵ�.
	begin = root;
	for (int j = start; j <= finish; j++) {
		end = rawdata[j].key;
		tempMax = max(tempMax, dist[begin][end]);
	}

	if (tempMax < minValue) minHead = begin;
	
	head.push_back(minHead);
}

void get_head() {
	int groups = 0, mov = 1, anchor;
	int rootInfo[103];

	for (int i = 1; i <= ppl; i++) rootInfo[i] = rawdata[i].root; //��Ʈ�� ������ �����´�.

	for (mov = 1; mov <= ppl; mov++) {
		if (rootInfo[mov] > 0) break;
		if (rootInfo[mov] <= -1) groups++;
		if (rootInfo[mov] == -1) head.push_back(rawdata[mov].key); //��Ȧ�� ����ȸ
	}

	for (; mov <= ppl; mov++) {
		anchor = mov;
		while (mov <= ppl && rootInfo[mov] == rootInfo[anchor]) mov++;

		find_head(anchor, mov - 1);
	}

	cout << groups << endl;
	sort(head.begin(), head.end());
	for (auto it : head) {
		cout << it << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	get_head();
	
	return 0;
}