/**************************************************************************************************/
//������ �־��� : DFS, DP, Bitmasking
//Key Point : �������� �־����� �ʾҴ���, �ϳ��� ���������� ����ص� �ȴ�.
//���� : 0123450�� �ּ�(1000��)��� �ϸ�, �� ��δ� 2345012(���� 1000��)�� ��Ȯ�� ��ġ�ϱ� ����.
/**************************************************************************************************/
#include <cstdio>
#include <algorithm>
#pragma warning (disable:4996)

class operate {
private:
	int city_no; //���� ��
	int cost[16][16]; //��� �迭
	int result[16][1 << 16]; //��� ���� �迭

public:
	operate() :city_no(0) {};

	void initialize() {
		scanf("%d", &city_no); getchar();

		for (int i = 0; i < city_no; i++) {
			for (int j = 0; j < city_no; j++) {
				scanf("%d", &cost[i][j]); getchar();
			}
		}
	}

	void traverse() {

	}
};