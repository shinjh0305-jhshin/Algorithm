#include <iostream>
#include <vector>
using namespace std;

//��� ����� �������� ���� ����, ���� ���� ����̴�
int blueArea[4][6] = { 0 }, greenArea[6][4] = { 0 }; //��� index ����!!

void moveTypeOne(vector<int>& info) {													//��
	//info�� ��,���� �����ϸ�, �Ķ� �ʷ� ������� ���� ��� ���� �ٴ����� �����Ѵ�.
	int currow = info[0], curcol = info[1];

	int nextcol; //�Ķ��� �������� �� ���� ���� ������
	for (nextcol = 0; nextcol < 5; nextcol++) {
		if (blueArea[currow][nextcol + 1] != 0) break;
	}

	int nextrow; //�ʷϻ� �������� �� �࿡ ���� ������
	for (nextrow = 0; nextrow < 5; nextrow++) {
		if (greenArea[nextrow + 1][curcol] != 0) break;
	}

	blueArea[currow][nextcol] = 1;
	greenArea[nextrow][curcol] = 1;
}

void moveTypeTwo(vector<int>& info) {													 //���
	//info�� ��,���� �����ϸ�, �Ķ� �ʷ� ������� ���� ��� ���� �ٴ����� �����Ѵ�.
	int currow = info[0], curcol = info[1];

	int nextcol; //�Ķ��� �������� �� ���� ���� ������
	for (nextcol = 1; nextcol < 5; nextcol++) { //������ �簢���� ������ �ƴ�
		if (blueArea[currow][nextcol + 1] != 0) break;
	}

	int nextrow; //�ʷϻ� �������� �� �࿡ ���� ������
	for (nextrow = 0; nextrow < 5; nextrow++) {
		if (greenArea[nextrow + 1][curcol] != 0 || greenArea[nextrow + 1][curcol + 1] != 0)  break;
	}

	blueArea[currow][nextcol - 1] = blueArea[currow][nextcol] = 1;
	greenArea[nextrow][curcol] = greenArea[nextrow][curcol + 1] = 1;
}

void moveTypeThree(vector<int>& info) {													 //��
	//info�� ��,���� �����ϸ�, �Ķ� �ʷ� ������� ���� ��� ���� �ٴ����� �����Ѵ�.             ��
	int currow = info[0], curcol = info[1];

	int nextcol; //�Ķ��� �������� �� ���� ���� ������
	for (nextcol = 0; nextcol < 5; nextcol++) {
		if (blueArea[currow][nextcol + 1] != 0 || blueArea[currow + 1][nextcol + 1] != 0) break;
	}

	int nextrow; //�ʷϻ� �������� �� �࿡ ���� ������
	for (nextrow = 1; nextrow < 5; nextrow++) {
		if (greenArea[nextrow + 1][curcol] != 0) break;
	}
	blueArea[currow][nextcol] = blueArea[currow + 1][nextcol] = 1;
	greenArea[nextrow - 1][curcol] = greenArea[nextrow][curcol] = 1;
}

int eraseRowCol() {
	//�Ķ��� ������ �� ������ ����
	int erasedCol = 0;

	bool fullCol;
	for (int colMov = 5; colMov >= 0; colMov--) {
		fullCol = true;
		for (int rowMov = 0; rowMov < 4; rowMov++) {
			if (blueArea[rowMov][colMov] == 0) { //�� ĭ�� ���� ���
				fullCol = false;
				break;
			}
		}

		if (fullCol) { //�� ĭ�� ���� ���
			for (int rowMov = 0; rowMov < 4; rowMov++) {
				blueArea[rowMov][colMov] = 0; //���� ��ĭ���� �����.
			}
			erasedCol++; //������ �� ���� ����
		}
		else if (erasedCol) { //���� ���� �� ĭ�� �ְ�, ������ ������ ���� �־��� ���, ������ ���� ������ŭ ������.
			for (int rowMov = 0; rowMov < 4; rowMov++) {
				blueArea[rowMov][colMov + erasedCol] = blueArea[rowMov][colMov]; //�ռ� ��ϵ��� ������.
				blueArea[rowMov][colMov] = 0; //���� ��� ��ġ�� 0���� �����.
			}
		}
	}
	
	//�ʷϻ� ������ �� ������ ����
	int erasedRow = 0;
	bool fullRow;
	for (int rowMov = 5; rowMov >= 0; rowMov--) {
		fullRow = true;
		for (int colMov = 0; colMov < 4; colMov++) {
			if (greenArea[rowMov][colMov] == 0) { //�� ĭ�� ���� ���
				fullRow = false;
				break;
			}
		}

		if (fullRow) { //�� ĭ�� ���� ���
			for (int colMov = 0; colMov < 4; colMov++) {
				greenArea[rowMov][colMov] = 0; //���� ��ĭ���� �����.
			}
			erasedRow++; //������ �� ���� ����
		}
		else if (erasedRow) { //���� �࿡ �� ĭ�� �ְ�, ������ ������ ���� �־��� ���, ������ ���� ������ŭ ������.
			for (int colMov = 0; colMov < 4; colMov++) {
				greenArea[rowMov + erasedRow][colMov] = greenArea[rowMov][colMov]; //�ռ� ��ϵ��� ������.
				greenArea[rowMov][colMov] = 0; //���� ��� ��ġ�� 0���� �����.
			}
		}
	}

	return erasedCol + erasedRow;
}

void eraseBuffer() { //���� �� ���� �����ϰ� �����Ѵ�.
	//�Ķ���
	int eraseCols = 0;
	for (int col = 0; col < 2; col++) {
		for (int row = 0; row < 4; row++) {
			if (blueArea[row][col] != 0) {
				eraseCols++;
				break;
			}
		}
	}

	if (eraseCols) {
		for (int col = 5 - eraseCols; col >= 0; col--) {
			for (int row = 0; row < 4; row++) {
				blueArea[row][col + eraseCols] = blueArea[row][col];
				blueArea[row][col] = 0;
			}
		}
	}

	//�ʷϻ�
	int eraseRows = 0;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 4; col++) {
			if (greenArea[row][col] != 0) {
				eraseRows++;
				break;
			}
		}
	}

	if (eraseRows) {
		for (int row = 5 - eraseRows; row >= 0; row--) {
			for (int col = 0; col < 4; col++) {
				greenArea[row + eraseRows][col] = greenArea[row][col];
				greenArea[row][col] = 0;
			}
		}
	}
}

void operate() {
	int blocks, type, startrow, startcol;
	cin >> blocks;
	
	vector<int> info(4);

	int answer = 0;
	while (blocks--) {
		cin >> type >> startrow >> startcol;
		info[0] = startrow;
		info[1] = startcol;

		if (type == 1) moveTypeOne(info);
		else if (type == 2) moveTypeTwo(info);
		else moveTypeThree(info);

		answer += eraseRowCol();
		eraseBuffer();
	}

	int leftBlocks = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (blueArea[j][i]) leftBlocks++;
			if (greenArea[i][j]) leftBlocks++;
		}
	}

	cout << answer << endl;
	cout << leftBlocks << endl;

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}