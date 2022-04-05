#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class virus {
private:
	struct info {
		int row, col;
	};

	vector<info> blank; //��������
	vector<info> viruses; //���̷��� ����
	queue<info> qu;
	short oriMap[10][10]; //���� ����
	short modMap[10][10]; //����� ����

	int rows, cols, nulls = 0; //nulls : ���� ������ ����
	int drow[4] = { 1,0,-1,0 };
	int dcol[4] = { 0,-1,0,1 };

public:
	void reset(int* temp, int i, int j, int k) {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				modMap[row][col] = oriMap[row][col];
			}
		}

		modMap[blank[i].row][blank[i].col] = modMap[blank[j].row][blank[j].col] = modMap[blank[k].row][blank[k].col] = 1;
		
		int sz = viruses.size();
		for (int i = 0; i < sz; i++) {
			qu.push({ viruses[i].row, viruses[i].col });
		}

		*temp = nulls;
	}

	void initialize() {
		cin >> rows >> cols; cin.get();

		char ch;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				ch = cin.get(); cin.get();
				oriMap[i][j] = ch - '0';

				if (oriMap[i][j] == 0) {
					nulls++;
					blank.push_back({ i,j });
				}
				else if (oriMap[i][j] == 2)
					viruses.push_back({ i,j });
			
			}
		}		
	}

	void operate() {
		//maxtemp : �������� �ִ� �ĺ�, nulltemp : ���� ��쿡���� �������� ����
		int maxtemp = 0, nulltemp; 
		int currow, curcol, nrow, ncol;

		for (int i = 0; i < nulls - 2; i++) {
			for (int j = i + 1; j < nulls - 1; j++) {
				for (int k = j + 1; k < nulls; k++) {
					reset(&nulltemp, i, j, k); //������ �����ϰ� ���� �����.
					
					while (!qu.empty()) {
						currow = qu.front().row; curcol = qu.front().col; qu.pop();

						for (int x = 0; x < 4; x++) {
							nrow = currow + drow[x]; ncol = curcol + dcol[x];

							if (nrow < 0 || nrow >= rows || ncol < 0 || ncol >= cols || modMap[nrow][ncol]) continue;

							modMap[nrow][ncol] = 2; nulltemp--;
							qu.push({ nrow, ncol });
						}
					}

					maxtemp = max(maxtemp, nulltemp);
				}
			}
		}

		maxtemp -= 3; //�ʱ� �������� �� �� ���� ���� �����.
		cout << maxtemp << endl;
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	virus op;
	op.initialize();
	op.operate();
	return 0;
}