#include <iostream>
#include <algorithm>
using namespace std;

int horse[4] = { 0,0,0,0 }; //score�� index�� �����Ѵ�. score �� �����ϴ°� �ƴϴ�.
int dice[10];
int score[35], nextidx[35];
bool horseExist[36] = { false };

void initialize() {
	for (int i = 0; i <= 20; i++) { //�ܰ� �� �׸���
		score[i] = i * 2;
	}

	score[21] = 13; score[22] = 16; score[23] = 19; //10�б�
	score[24] = 22; score[25] = 24;	//20�б�
	score[26] = 28;	score[27] = 27; score[28] = 26;	//30�б�
	score[29] = 25; score[30] = 30;	score[31] = 35; score[32] = 40; //25���� 40

	for (int i = 0; i < 35; i++) nextidx[i] = i + 1;

	nextidx[5] = 21; nextidx[10] = 24; nextidx[15] = 26; //10, 20, 30ó��
	nextidx[19] = 32; //38ó��
	nextidx[23] = nextidx[25] = 29; //25ó��

	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}
} 

int DFS(int idx) { //idx : dice index
	int curDice = dice[idx];
	int maxScore = 0, curScore;

	int curLoc, nextLoc;

	for (int i = 0; i < 4; i++) {
		curLoc = horse[i];

		if (curLoc == -1) continue;
		
		curScore = 0;

		if (curLoc <= 20 && curLoc != 5 && curLoc != 10 && curLoc != 15) { //�ܰ��� �޸��� ��
			nextLoc = curLoc + curDice;

			if (nextLoc > 20) { //���� ����
				horse[i] = -1;
				horseExist[curLoc] = false;
				nextLoc = 0; //backtracking�� ���� ���� �� ����
			}
			else {
				if (nextLoc == 20) nextLoc = 32; //40���� ����

				if (horseExist[nextLoc]) continue; //������ ���� ���� �ִ�.
				else { //���� �� �� �ִ� ���̴�.
					curScore = score[nextLoc];
					horse[i] = nextLoc;
					horseExist[curLoc] = false;
					horseExist[nextLoc] = true;
				}
			}
		}
		else {
			nextLoc = curLoc;
			for (int j = 0; j < curDice; j++) {
				nextLoc = nextidx[nextLoc];

				if (nextLoc == 33) break; //���� ����.
			}

			if (nextLoc == 33) { //���� ����
				horse[i] = -1;
				horseExist[curLoc] = false; //���� ��ġ���� ���� �����Ѵ�
			}
			else if (horseExist[nextLoc]) continue; //������ ��ġ�� ���� �ִ�.
			else {
				curScore = score[nextLoc];
				horse[i] = nextLoc; //���� ��ġ�� ���� �д�.
				horseExist[nextLoc] = true;
				horseExist[curLoc] = false; //���� ��ġ���� ���� �����Ѵ�
			}
		}

		if (idx < 9) curScore += DFS(idx + 1);
		maxScore = max(maxScore, curScore);

		horse[i] = curLoc; //backtracking
		horseExist[nextLoc] = false;
		horseExist[curLoc] = true;

	}

	return maxScore;
}


void operate() {
	cout << DFS(0) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}