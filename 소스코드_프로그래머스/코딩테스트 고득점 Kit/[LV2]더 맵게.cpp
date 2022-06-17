#include <string>
#include <queue>
#include <vector>
#define ll long long

using namespace std;

priority_queue<ll, vector<ll>, greater<ll>> pq;

int solution(vector<int> scoville, int K) {
	int answer = 0;
	for (const auto it : scoville) {
		pq.push(it);
	}

	ll food1, food2;
	while (1) {
		//��� ������ K �̻��� ��
		if (pq.top() >= K) return answer;
		//���� ������ ���� ��
		else if (pq.size() == 1) return -1;

		food1 = pq.top(); pq.pop();
		food2 = pq.top(); pq.pop();
		pq.push(food1 + food2 * 2);

		answer++;
	}


	return answer;
}