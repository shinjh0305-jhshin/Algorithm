/*
�� ������ �ٽ��� A���� B�� ���ѷ����� ���� �� �� �ִ����� �Ǻ��ϴ� ���̴�.
�׷����� ���� �������� ���� ���ѷ����� �ִ����� �Ǵ��Ϸ��� N-1���� ���� Ž���� ��ģ �� (N : ��� ����)
1���� ���� Ž���� �߰��� �ϸ� ������,
�� ��쿡�� Ư�� ������ Ư�� ������ ���� ����ġ�� ���� ���ѷ����� ����� �� �ִ����� �Ǵ��ؾ� �ϴ� ����̹Ƿ�,
�ڳ�庸�� ����� ���� ������ ���� Ž���� �ؾ� �Ѵ�. (���ۿ��� �������� ���� ���� ���� ������ �����ϴ� ��� ó��)
�̸� ���� ���ѷ��� �߰��� �ִ� ��� ������ ���ѷ����� ���� �� ���� �ٲ�� �ȴ�.
*/

#include <iostream>
#include <algorithm>
#define endl "\n"
#define ll long long
#define INF 2134567890000
#define MIN -2134567890000
using namespace std;

struct info {
	int start, end, cost;
};

ll cityProfit[53], totalSum[53];
info edge[53];
int cities, edges, start, finish;

void initialize() {
	cin >> cities >> start >> finish >> edges;

	for (int i = 0; i < edges; i++) {
		cin >> edge[i].start >> edge[i].end >> edge[i].cost;
	}

	for (int i = 0; i < cities; i++) {
		cin >> cityProfit[i];
		totalSum[i] = MIN;
	}
	totalSum[start] = cityProfit[start]; //���� ������ �ʱ�ȭ
}

void operate() {
	int edgeStart, edgeEnd, edgeCost;

	for (int iter = 0; iter < cities + 50; iter++) { //�������� ���ѷ��� �߰� Ȥ�� �� ���Ŀ� ���� �� �ֱ⿡, 1�����ŭ ������ �߰��� ������.
		for (int k = 0; k < edges; k++) {
			edgeStart = edge[k].start; edgeEnd = edge[k].end; edgeCost = edge[k].cost;

			if (totalSum[edgeStart] == MIN) continue; //���� �湮���� ����.	

			if (totalSum[edgeStart] == INF) totalSum[edgeEnd] = INF; //���� ������ ���� �߰� Ȥ�� ���Ŀ� ���Դ�
			else if (totalSum[edgeStart] + cityProfit[edgeEnd] - edgeCost > totalSum[edgeEnd]) { //�� �̵��� �����
				if (iter >= cities) totalSum[edgeEnd] = INF;
				else {
					totalSum[edgeEnd] = totalSum[edgeStart] + cityProfit[edgeEnd] - edgeCost;
				}
			}
		}
	}

	if (totalSum[finish] == MIN) cout << "gg" << endl;
	else if (totalSum[finish] == INF) cout << "Gee" << endl;
	else cout << totalSum[finish] << endl;
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}