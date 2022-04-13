/*
��ǥ : ���� ������ �������� ������
���ѻ���:
1. �Ķ������� ���ۿ� ���� �� �� ��. ���� ����
2. �����¿츸 �̵� ����
3. ���� ���ÿ� �̵�
4. �������� �Ķ������� ���ÿ� �̵��ϸ�, �� ĭ�� ��� ����
5. ����̴� ������ �׸��ϴ� ���� ������ �� ������ �� ����(������ �δ�)
*/

/*�����ڵ�
0. ť�� ũ�⸦ �޴� ������ ũ�⸦ �ش�.
1. ť���� ���� R, B, ������ �Դ� ������ ��ġ�� ������.
2. R, B�� �����̵�, ������ �Դ� ����� �� �ݴ� �������δ� ���� �ʴ´�.
3. �����̴� �������� R�� ���뿡 ������(index�� ���� �������� �Ǵ�) flag ������Ʈ�ϰ� break
4. �����̴� �������� B�� ���뿡 ������ �� break
5. �ƹ� �ҵ浵 ������ 0���� ���ư���, ���� 10��° �����ӿ� �����ߴٸ� �� -1����ϰ� ��.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>	
using namespace std;

struct pos {
	short row, col;

	bool operator !=(const pos temp) {
		if (this->row != temp.row || this->col != temp.col) return true;
		return false;
	}
};
struct info {
	pos red, blue;
};
short drow[4] = { 1,0,-1,0 };
short dcol[4] = { 0,-1,0,1 };
char map[11][11];
int rows, cols;
pos hole;
queue<info> qu;

void initialize() {
	cin >> rows >> cols; cin.get();

	info first;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = (char)cin.get();

			if (map[i][j] == '.' || map[i][j] == '#') continue;
			if (map[i][j] == 'O') {
				hole.row = i; hole.col = j;
			}
			else if (map[i][j] == 'R') {
				first.red.row = i; first.red.col = j;
				map[i][j] = '.';
			}
			else {
				first.blue.row = i; first.blue.col = j;
				map[i][j] = '.';
			}

		}
		cin.get();
	}
	qu.push(first);
}

info getToMove(pos red, pos blue, short dir) { //dir �������� ������ �� �� �� �ִ� ��
	short currow, curcol, nrow, ncol;
	bool swapped = false;
	info result;

	result.red = red; result.blue = blue;

	if ((dir == 0 && blue.row > red.row) || (dir == 1 && blue.col < red.col) ||
		(dir == 2 && blue.row < red.row) || (dir == 3 && blue.col > red.col)) {
		swap(red, blue);
		swapped = true;
	} //�� ���, �׻� red�� blue ���� ������ ���⿡�� �ռ� �ְ� �ȴ�.

	currow = red.row; curcol = red.col;

	while (1) { //�ռ� �ִ� �������� �����δ�
		nrow = currow + drow[dir];
		ncol = curcol + dcol[dir];
		if (map[nrow][ncol] == '.') { //�� �� �� �ִ� ��
			map[currow][curcol] = '.';
			currow = nrow;
			curcol = ncol;
			continue;
		}
		if (map[nrow][ncol] == '#') { //���� ��Ҵ�
			result.red.row = currow;
			result.red.col = curcol;
			break;
		}
		if (map[nrow][ncol] == 'O') { //���� �� ������ ���뿡 ������. swapped�� ���� �������� �˾ƺ���.
			result.red.row = result.red.col = 777; 
			if (swapped) goto finale; //���뿡 ���� ������ �Ķ����̴�. �� ���� �ƴϴ�.
			else break; //���� ������ ���뿡 ������.
		}
	}

	currow = blue.row; curcol = blue.col;
	while (1) { //�ڿ� �ִ� ���� �����̱� �����Ѵ�.
		nrow = currow + drow[dir];
		ncol = curcol + dcol[dir];

		if (map[nrow][ncol] == '#' || (nrow == result.red.row&&ncol == result.red.col)) { //�տ� �ٸ� ������ ���� �־ �� �̻� �� ���ų� ���� ������.
			result.blue.row = currow;
			result.blue.col = curcol;
			break;
		}
		if (map[nrow][ncol] == '.') { //�� �� �� �ִ� ��
			map[currow][curcol] = '.';
			currow = nrow;
			curcol = ncol;
			continue;
		}
		if (map[nrow][ncol] == 'O') {
			result.blue.row = result.blue.col = 777; //���� �� ������ ���뿡 ������. swapped�� ���� �������� �˾ƺ���.
			break;
		}
	}

finale: if (swapped) swap(result.red, result.blue);
	return result;
}

void operate() {
	int mov = 1, sz_queue;
	info result;

	while (mov <= 10) {
		sz_queue = qu.size();
		for (int iter = 0; iter < sz_queue; iter++) {
			for (short i = 0; i < 4; i++) {
				result = getToMove(qu.front().red, qu.front().blue, i);

				if (result.blue.row == 777) { //������ ���
					continue;
				}
				else if (result.red.row == 777) { //���� ã�Ҵ�
					cout << mov << endl;
					return;
				}

				if (result.red != qu.front().red || result.blue != qu.front().blue) {
					qu.push({ result.red, result.blue});
				}
			}
			qu.pop();
		}
		mov++;
	}

	cout << -1 << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}

/*�׽�Ʈ���̽�
5 7
#######
#....R#
#B.####
##O####
#######

3 6
######
#.ORB#
######
ans : -1

8 8
########
#.####.#
#...#B##
#.##.R.#
######.#
##.##O.#
###.##.#
########
ans : 7

4 6
######
#R####
#B..O#
######
ans : -1

4 6
######
#R#O##
#B...#
######
ans : 4

9 9
#########
###.....#
#..#..#O#
##..R.#B#
####....#
#.....#.#
#.#.....#
##.###..#
#########
*/