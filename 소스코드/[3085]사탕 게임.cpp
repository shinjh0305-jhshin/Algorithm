#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class candy_game {
private:
	vector<char> rawdata[50];
	int board_size;

public:
	void initialize() {
		cin >> board_size; cin.get();
		for (int i = 0; i < board_size; i++) {
			for (int j = 0; j < board_size; j++) {
				rawdata[i].push_back(cin.get());
			}
			cin.get();
		}
	}

	void operate() {
		// **saved_max : global maximum,  **current_calc : local maximum
		int front, back, i, j, k, saved_max = 0, current_calc;
		for (i = 0; i < board_size; i++) { //���� ������ �̿��� �� ���� �ٲٴ� ����
			for (front = 0; front <= board_size - 2; front++) { 
				back = front + 1;
				swap(rawdata[i][front], rawdata[i][back]); //���� index�� ����

				current_calc = 1;
				for (j = 0; j <= board_size - 2; j++) { //���� ���⿡�� ���� �� ���� ���� ����
					if (rawdata[i][j] == rawdata[i][j + 1]) { //���� index�� ����
						current_calc++;
					}
					else {
						if (current_calc > saved_max) saved_max = current_calc;
						current_calc = 1;
					}
				}
				if (current_calc > saved_max) saved_max = current_calc; //������������ ���ӵ� ���� ������ ������ üũ

				for (k = front; k <= back; k++) { //���� ���⿡�� ���� �� ���� ���� ����, 2�� �ݺ��ؾߵ�
					current_calc = 1;
					for (j = 0; j <= board_size - 2; j++) {
						if (rawdata[j][k] == rawdata[j + 1][k]) { //���� index�� ����
							current_calc++;
						}
						else {
							if (current_calc > saved_max) saved_max = current_calc; 
							current_calc = 1;
						}
					}
				}
				if (current_calc > saved_max) saved_max = current_calc; //������������ ���ӵ� ���� ������ ������ üũ

				swap(rawdata[i][front], rawdata[i][back]); //���󺹱�
			}
		}

		for (i = 0; i < board_size; i++) { //���� ������ �̿��� �� ���� �ٲٴ� ����
			for (front = 0; front <= board_size - 2; front++) {
				back = front + 1;
				swap(rawdata[front][i], rawdata[back][i]); //���� index�� ����

				current_calc = 1;
				for (j = 0; j <= board_size - 2; j++) { //���� ���⿡�� ���� �� ���� ���� ����
					if (rawdata[j][i] == rawdata[j + 1][i]) { //���� index�� ����
						current_calc++;
					}
					else {
						if (current_calc > saved_max) saved_max = current_calc;
						current_calc = 1;
					}
				}
				if (current_calc > saved_max) saved_max = current_calc; //������������ ���ӵ� ���� ������ ������ üũ

				for (k = front; k <= back; k++) { //���� ���⿡�� ���� �� ���� ���� ����, 2�� �ݺ��ؾߵ�
					current_calc = 1;
					for (j = 0; j <= board_size - 2; j++) {
						if (rawdata[k][j] == rawdata[k][j + 1]) { //���� index�� ����
							current_calc++;
						}
						else {
							if (current_calc > saved_max) saved_max = current_calc;
							current_calc = 1;
						}
					}
				}
				if (current_calc > saved_max) saved_max = current_calc; //������������ ���ӵ� ���� ������ ������ üũ

				swap(rawdata[front][i], rawdata[back][i]);
			}
		}
		cout << saved_max << endl;
	}

};

int main() {
	ios::sync_with_stdio(false);
	candy_game op;
	op.initialize();
	op.operate();
	return 0;
}