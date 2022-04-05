#include <iostream>
#include <algorithm>
#pragma warning (disable:4996)
#define endl "\n"
using namespace std;

class sticker {
private:
	//int** cost : sticker ������ cost
	//���� : 1��(row : 0), 2��(row : 1)
	//<<result�� index �ٸ� ����>>
	int cost[2][100005]; 
		
	//int** result : DP�� ����� ���� �迭
	//���� : ����X(col : 0), 1�� ����(col : 1), 2�� ����(col : 2)
	//<<cost�� index �ٸ� ����>>
	int result[2][3];
	int save_row, lookup_row, test_cases, rowofSticker;

public:
	sticker() {
		save_row = test_cases = rowofSticker = 0; lookup_row =  1;
	}

	void get_test_cases() {
		cin >> test_cases; cin.get();
	}

	void operate() {
		int i, j, k, answer;
		enum {up, down};
		for (i = 0; i < test_cases; i++) {
			//Initializing phase
			cin >> rowofSticker; cin.get();
			for (j = 0; j < 2; j++) {
				for (k = 0; k < rowofSticker; k++) {
					cin >> cost[j][k]; cin.get();
				}
			}

			result[save_row][0] = 0; result[save_row][1] = cost[down][0]; result[save_row][2] = cost[up][0];

			//Real operating phase
			for (j = 1; j < rowofSticker; j++) {
				swap(save_row, lookup_row);
				result[save_row][0] = max(result[lookup_row][0], result[lookup_row][1]);
				result[save_row][0] = max(result[save_row][0], result[lookup_row][2]);

				result[save_row][1] = max(result[lookup_row][0], result[lookup_row][2]) + cost[down][j];
				result[save_row][2] = max(result[lookup_row][0], result[lookup_row][1]) + cost[up][j];
			}
			answer = max(result[save_row][0], result[save_row][1]);
			answer = max(answer, result[save_row][2]);
			cout << answer << endl;
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	sticker op;
	op.get_test_cases();
	op.operate();
	return 0;
}