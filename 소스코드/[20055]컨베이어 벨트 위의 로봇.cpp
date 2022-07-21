/*
���μ���
1. �ø��� ��ġ, ������ ��ġ �� ĭ�� �����̸� ������Ʈ
2. �κ��� �� ĭ �̵��� �� �ִ��� ����
3. �ø��� ��ġ�� �ø� �� ������ �κ� �ø���
4. �������� 0�� ĭ�� K �� �̻��̸� ����
*/

#include <iostream>
#include <deque>
using namespace std;

int belts, target;
int capa[205]; //�� ĭ�� ������(����:1)
int goUp = 1, goDown; //�ø��� ������ ��ġ
deque<int> robots; //robot ��ġ
bool hasRobot[205] = { false };

void initialize() {
	cin >> belts >> target;
	goDown = belts;

	for (int i = 1; i <= 2 * belts; i++) {
		cin >> capa[i];
	}
}

void operate() {
	int nullCapa = 0; //�������� 0�� ĭ�� ����
	int op = 1;

	while (1) {
		//phase 1 : update goup godown
		goUp = goUp - 1 == 0 ? 2 * belts : goUp - 1;
		goDown = goDown - 1 == 0 ? 2 * belts : goDown - 1;

		//phase2 : move robot
		//�� �� �κ��� ������ ��ġ�� ������ Ȯ���Ѵ�
		if (!robots.empty() && robots[0] == goDown) {
			hasRobot[goDown] = false;
			robots.pop_front();
		}

		//ó�� �尣 �κ����� �� ĭ�� �����δ�
		int nextPos;
		for (auto& it : robots) {
			nextPos = it + 1 > 2 * belts ? 1 : it + 1;
			if (!hasRobot[nextPos] && capa[nextPos]) {
				hasRobot[it] = false;
				it = nextPos;
				hasRobot[nextPos] = true;
				capa[nextPos]--;

				if (capa[nextPos] == 0) nullCapa++;
			}
		}

		//�κ� �̵� �ĸ� �� �κ��� ������ ��ġ�� ������ Ȯ���Ѵ�.
		if (!robots.empty() && robots[0] == goDown) {
			hasRobot[goDown] = false;
			robots.pop_front();
		}

		//phase3 : new robot
		if (capa[goUp]) {
			robots.push_back(goUp);
			hasRobot[goUp] = true;
			capa[goUp]--;

			if (capa[goUp] == 0) nullCapa++;
		}

		if (nullCapa >= target) {
			cout << op << endl;
			return;
		}
		op++;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}