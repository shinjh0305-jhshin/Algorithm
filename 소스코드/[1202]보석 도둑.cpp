#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define endl "\n"
using namespace std;

struct info {
	int weight;
	int value;
};
vector<info> gems;
vector<int> sacks;
int sz_gems, sz_sacks;

struct cmp {
	bool operator() (const info& a, const info& b) {
		if (a.value < b.value) return true;
		return false;
	}
};

bool compare(const info& a, const info& b) {
	if (a.weight < b.weight) return true;
	return false;
}

void initialize() {
	cin >> sz_gems >> sz_sacks;

	gems.resize(sz_gems);
	sacks.resize(sz_sacks);

	for (int i = 0; i < sz_gems; i++) {
		cin >> gems[i].weight >> gems[i].value;
	}

	for (int i = 0; i < sz_sacks; i++) {
		cin >> sacks[i];
	}

	sort(gems.begin(), gems.end(), compare); //���� ������ ���԰� Ŀ���� ������ ���ĵǾ��ִ�.
	sort(sacks.begin(), sacks.end(), less<int>()); //���� ������ �뷮�� Ŀ���� ������ ���ĵǾ� �ִ�.
}

void operate() {
	priority_queue<info, vector<info>, cmp> pq; //������ ��ġ�� ū ���� top�� �´�.

	int gemsIdx = 0, curSackWeight;
	long long sum = 0;
	for (int i = 0; i < sz_sacks; i++) {
		curSackWeight = sacks[i];
		for (; gemsIdx < sz_gems; gemsIdx++) {
			if (gems[gemsIdx].weight <= curSackWeight) { //���� ���濡 �� �� �ִ� �����̴�.
				pq.push(gems[gemsIdx]);
			}
			else break;
		}
		if (!pq.empty()) {
			sum += pq.top().value;
			pq.pop();
		}
	}

	cout << sum << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*
5 4
2 30
6 10
3 100
5 110
4 70
4
4
2
6
ans: 310

5 5
7 30
9 10
10 100
14 110
8 70
1
2
3
4
9
ans: 70
*/