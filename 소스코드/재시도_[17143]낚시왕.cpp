#include <iostream>
#include <cstring>
#include <deque>
#include <algorithm>
#define pp pair<int, int>
using namespace std;

struct info {
	int speed;
	int direction;
	int size;
};

int rows, cols, sharks;
int sharkRow, sharkCol; //��ΰ� ���� ����� ��ġ
deque<pp> location; //row, col
info sharkDetail[2][102][102]; // ��� �ӵ�, ��� ����, ��� ũ��
int curShark = 0, beforeShark = 1;

bool compare(const pp& a, const pp& b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

void initialize() {
	cin >> rows >> cols >> sharks;

	int row, col, speed, direction, size;
	for (int i = 0; i < sharks; i++) {
		cin >> row >> col >> speed >> direction >> size;
		location.push_back({ row, col });
		sharkDetail[curShark][row][col] = { speed, direction, size };
	}
}

void catchShark(int col) { //col : ���� ��ΰ� �ִ� column
	int row = 999999;
	for (const auto& it : location) {
		if (it.second == col) {
			row = row < it.first ? row : it.first;
		}
	}

	sharkRow = row; 
	sharkCol = col;
}


void changeSharkLocation(int row, int col) {
	//1_up 2_down 3_right 4_left
	int curSpeed = sharkDetail[beforeShark][row][col].speed;
	int curdirection = sharkDetail[beforeShark][row][col].direction;
	int blockSize;

	int nextrow, nextcol, nextdirection;
	if (curdirection == 1) {
		nextcol = col;
		if (row - curSpeed >= 1) {
			nextrow = row - curSpeed;
			nextdirection = 1; 
		}
		else {
			nextdirection = (curSpeed - (row - 1)) / (rows - 1);
			if (nextdirection % 2 == 1) nextdirection = 1;
			else nextdirection = 2;

			nextrow = (curSpeed - (row - 1)) % (rows - 1);
			if (nextrow == 0) nextrow = 3;
			nextrow++;
		}
	}
	else if (curdirection == 2) {

	}

	if (curdirection == 1 || curdirection == 2) {
		blockSize = rows - 1;
		int nextdir = (curSpeed -))
	}
	else blockSize = cols - 1;

	
}

void moveShark() {
	int sz_shark = location.size();
	swap(curShark, beforeShark); //������, ������� ���� ��ġ ����
	memset(sharkDetail[curShark], 0, sizeof(sharkDetail[curShark]));

	int currow, curcol, curspeed, curdir, cursz;
	while (sz_shark--) {
		currow = location.front().first; curcol = location.front().second;
		location.pop_front();

		if (currow == sharkRow && curcol == sharkCol) continue;

		changeSharkLocation(currow, curcol);

	}
}

void operate() {
	for (int i = 1; i <= cols; i++) { //����� ��ġ �̵�

	}
}
