/**************************************************************************************************/
//������ �־��� : DFS, DP, Bitmasking
//Key Point : �������� �־����� �ʾҴ���, �ϳ��� ���������� ����ص� �ȴ�.
//���� : 0123450�� �ּ�(1000��)��� �ϸ�, �� ��δ� 2345012(���� 1000��)�� ��Ȯ�� ��ġ�ϱ� ����.
/**************************************************************************************************/
#include <iostream>
#include <algorithm>
#define INF 2000000000
#define UNVISITED -1
using namespace std;

int city_no; //���� ��
int cost[16][16]; //��� �迭
int result[16][1 << 16]; //result[i][j] = ���� i�� node�� �ְ�, j�� �ִ� node�� �湮�� ������ ��, �����ϴµ� �ɸ��� �Ÿ�.

void initialize() {
	cin >> city_no;

	for (int i = 0; i < city_no; i++) {
		for (int j = 0; j < 1 << city_no; j++) {
			result[i][j] = UNVISITED;
		}
		for (int j = 0; j < city_no; j++) {
			cin >> cost[i][j];
		}
	}
}

int tsp(int currentNode, int visited) {	
	if (visited == (1 << city_no) - 1) { //��� ���� Ž������ ���
		if (cost[currentNode][0] == 0) return INF; //�ٽ� �������� �����ϴ� ��Ʈ�� ���� ���
		else return cost[currentNode][0];
	}

	//�ʱ�ȭ�� INF�� �ϸ� �� �Ǵ� ���� : �ʰ��� ������ �� ���� �߻� ����
	//��� ��带 �� ���Ƽ� �ٽ� ���� ���� �ͼ� �ٽ� �� ���Ƽ� �ٽ� ���� ���� �� ���
	//currentNode�� visited�� ���� ��Ȳ�� �߻��Ѵ�.
	//�� ��, result�� INF�̳� �ƴϳķ� ������, �翬�� result�� INF�̱⿡ �ٽ� ������ ����.
	//��, ���� Ž���� �����ߴٴ� ǥ�ô� INF�� ����, Ž���� ���������� �ʾҴٴ� UNVISITED�� �ؾ� �ȴ�.

	if (result[currentNode][visited] != UNVISITED) return result[currentNode][visited];

	int nextVisited;
	result[currentNode][visited] = INF;
	for (int nextNode = 0; nextNode < city_no; nextNode++) {
		//���� ��忡�� ���� ���� ���� ���� ���ų�, �̹� �湮�� ���� ����.
		if (cost[currentNode][nextNode] == 0 || (visited & (1 << nextNode)) != 0) continue;
		
		nextVisited = visited | (1 << nextNode);
		result[currentNode][visited] = min(result[currentNode][visited], cost[currentNode][nextNode] + tsp(nextNode, nextVisited));
	}

	return result[currentNode][visited];
}

void operate() {
	//0��° ��忡�� ����Ѵٰ� �����Ѵ�
	cout << tsp(0, 1) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}