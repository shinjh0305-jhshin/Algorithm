#include <iostream>
#include <algorithm>
using namespace std;

int rawdata[2][303][303];
int rows, cols, rotas; //rows, cols �� ���� �������� 1�� ����

void initialize() {
	cin >> rows >> cols >> rotas;

	rows--; cols--; //indexing �� ���ؼ� ���� �ٲ۴�

	for (int i = 0; i <= rows; i++) {
		for (int j = 0; j <= cols; j++) {
			cin >> rawdata[0][i][j];
		}
	}
}

void doRotate(int idx) {
	int mrow = idx, Mrow = rows - idx; //m : ����, M : ����
	int mcol = idx, Mcol = cols - idx; 

	int sizeSquare = (Mrow - mrow + 1) * (Mcol - mcol + 1);
	int Rotas = rotas % sizeSquare; //������ n ������ �����Ѵ�.

	int currow, curcol, leftRotas;
	for (int row = mrow; row <= Mrow; row++) {
		for (int col = mcol; col <= Mcol;) {
			currow = row; curcol = col; leftRotas = Rotas;

			while (1) {
				if ((currow == Mrow && curcol != Mcol) || curcol == mcol) { //�º�, �Ʒ����� ���� ���
					if ((Mrow - currow) + (Mcol - curcol) < leftRotas) { //��󺯱��� �� �� �ִ�
						leftRotas -= (Mrow - currow) + (Mcol - curcol);
						currow = Mrow; curcol = Mcol;
					}
					else { //���ϴܱ��� �� ����	
						if ((Mrow - currow) <= leftRotas) { //�Ʒ��������� �� �� �ִ�
							leftRotas -= Mrow - currow;
							currow = Mrow;
							curcol += leftRotas;
						}
						else {
							currow += leftRotas;
						}
						break;
					}
				}
				else { //�캯, ������ ���� ���
					if ((currow - mrow) + (curcol - mcol) < leftRotas) { //�»�ܱ��� �� �� �ִ�
						leftRotas -= (currow - mrow) + (curcol - mcol);
						currow = mrow; curcol = mcol;
					}
					else { //�»�ܱ��� �� ����
						if (currow - mrow <= leftRotas) { //���������� �� �� �ִ�
							leftRotas -= currow - mrow;
							currow = mrow;
							curcol -= leftRotas;
						}
						else {
							currow -= leftRotas;
						}
						break;
					}
				}
			}

			rawdata[1][currow][curcol] = rawdata[0][row][col];

			if (row == mrow || row == Mrow) col++;
			else col += Mcol - mcol;
		}
	}
}


void operate() {
	int iter = min(rows, cols) / 2;

	for (int i = 0; i <= iter; i++) {
		doRotate(i);
	}

	for (int i = 0; i <= rows; i++) {
		for (int j = 0; j <= cols; j++) {
			cout << rawdata[1][i][j] << ' ';
		}
		cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}