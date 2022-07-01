#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

enum a {U, F, L, B, R, D}; //�� �� �� �� �� ��
char color[6] = { 'w', 'r', 'g', 'o', 'b', 'y' };
char cube[6][3][3];

void initialize() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cube[i][j][k] = color[i];
			}
		}
	}
}

void rotateUpDown(char side, char dir) {
	int idxOne = 0;
	if (side == 'D') idxOne = 2;

	char temp[3];
	for (int i = 0; i < 3; i++) temp[i] = cube[R][idxOne][i]; //������ �� Ű��!
	

	if ((side == 'U' && dir == '+') || (side == 'D' && dir == '-')) { //�ð����
		for (int i = 0; i < 3; i++) cube[R][idxOne][i] = cube[B][idxOne][i]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[B][idxOne][i] = cube[L][idxOne][i]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[L][idxOne][i] = cube[F][idxOne][i]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[F][idxOne][i] = temp[i]; //�� -> ��
	}
	else if ((side == 'U' && dir == '-') || (side == 'D' && dir == '+')) { //�ݽð���� 
		for (int i = 0; i < 3; i++) cube[R][idxOne][i] = cube[F][idxOne][i]; //�� <- ��
		for (int i = 0; i < 3; i++) cube[F][idxOne][i] = cube[L][idxOne][i]; //�� <- ��
		for (int i = 0; i < 3; i++) cube[L][idxOne][i] = cube[B][idxOne][i]; //�� <- ��
		for (int i = 0; i < 3; i++) cube[B][idxOne][i] = temp[i]; //�� <- ��
	}
}

void rotateRightLeft(char side, char dir) {
	int idxOne = 2, idxTwo = 0;
	if (side == 'L') swap(idxOne, idxTwo);

	char temp[3];
	for (int i = 0; i < 3; i++) temp[i] = cube[F][i][idxOne]; //�� �� Ű��!

	if ((side == 'R' && dir == '+') || (side == 'L' && dir == '-')) { //�ð����
		for (int i = 0; i < 3; i++) cube[F][i][idxOne] = cube[D][2 - i][idxTwo]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[D][i][idxTwo] = cube[B][i][idxTwo]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[B][i][idxTwo] = cube[U][2 - i][idxOne]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[U][i][idxOne] = temp[i]; //�� -> ��
	}
	else if ((side == 'R' && dir == '-') || (side == 'L' && dir == '+')) { //�ݽð����
		for (int i = 0; i < 3; i++) cube[F][i][idxOne] = cube[U][i][idxOne]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[U][i][idxOne] = cube[B][2 - i][idxTwo]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[B][i][idxTwo] = cube[D][i][idxTwo];//�� -> ��
		for (int i = 0; i < 3; i++) cube[D][i][idxTwo] = temp[2 - i]; //�� -> ��
	}
}

void rotateFrontBack(char side, char dir) {
	int idxOne = 2, idxTwo = 0;
	if (side == 'B') swap(idxOne, idxTwo);

	char temp[3];
	for (int i = 0; i < 3; i++) temp[i] = cube[U][idxOne][i]; //�� �� Ű��!

	if ((side == 'F' && dir == '+') || (side == 'B' && dir == '-')) { //�ð����
		for (int i = 0; i < 3; i++) cube[U][idxOne][i] = cube[L][2 - i][idxOne]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[L][i][idxOne] = cube[D][idxOne][2 - i]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[D][idxOne][i] = cube[R][idxTwo][i]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[R][i][idxTwo] = temp[i]; //�� -> ��
	}
	else if ((side == 'F' && dir == '-') || (side == 'B' && dir == '+')) { //�ݽð����
		for (int i = 0; i < 3; i++) cube[U][idxOne][i] = cube[R][i][idxTwo]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[R][i][idxTwo] = cube[D][idxOne][i]; //�� -> ��
		for (int i = 0; i < 3; i++) cube[D][idxOne][i] = cube[L][2 - i][idxOne];//�� -> ��
		for (int i = 0; i < 3; i++) cube[L][i][idxOne] = temp[2 - i];//�� -> ��
	}

}
void operate() {
	int op;
	string opers;

	cin >> op; cin.get();
	getline(cin, opers); 

	char curop, curdir;
	for (int i = 0; i < opers.length(); i += 3) {
		curop = opers[i];
		curdir = opers[i + 1];

		if (curop == 'U' || curop == 'D') {
			rotateUpDown(curop, curdir);
		}
		else if (curop == 'R' || curop == 'L') {
			rotateRightLeft(curop, curdir);
		}
		else {
			rotateFrontBack(curop, curdir);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << cube[U][i][j];
		}
		cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int cases;
	cin >> cases; cin.get();
	
	while (cases--) {
		initialize();
		operate();
	}

	return 0;
}