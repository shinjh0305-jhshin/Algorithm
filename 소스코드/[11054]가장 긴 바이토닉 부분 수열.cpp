#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class bitonic {
private:
	vector<int> rawdata;
	int** seq_result = NULL;
	int sz_rawdata;
public:
	void initialize() {
		cin >> sz_rawdata;
		rawdata.reserve(sz_rawdata);
		
		seq_result = new int*[2];
		for (int i = 0; i < 2; i++)
			seq_result[i] = new int[sz_rawdata];

		int newnum;
		for (int i = 0; i < sz_rawdata; i++) {
			cin >> newnum;
			rawdata.push_back(newnum);
		}
	}

	void operate() {
		make_order(0, rawdata.size() - 1, 1, 0); //������ �˻�
		make_order(rawdata.size() - 1, 0, -1, 1); //������ �˻�
		
		int bitonic_max = 0;
		for (int i = 0; i < sz_rawdata; i++) {
			bitonic_max = max(bitonic_max, seq_result[0][i] + seq_result[1][i]);
		}
		bitonic_max--;

		cout << bitonic_max << endl;
	}

	// ** start_index, end_index : �ڱ��ڽ� �����Ұ�
	// ** direction : 1(������), -1(������)
	// ** save_row : seq_result�� ��� row�� ��������
	void make_order(int start_index, int end_index, int direction, int save_row) {

		//end_mov : ���� �ǵ����� ������ index, start_mov : �տ������� �ɾ���� index
		//seq_max : ���� end_mov���� ���� �� ������ ����, current_seq : start_mov�� ������ ����
		int seq_max, i, j, end_mov = start_index, start_mov, current_seq;

		for (i = 0; i < sz_rawdata; i++) {
			seq_max = 0;
			start_mov = start_index;

			for (j = 0; j < i; j++) {
				current_seq = seq_result[save_row][start_mov];
				if (rawdata[start_mov] < rawdata[end_mov] && current_seq > seq_max) {
					seq_max = current_seq;
				}
				start_mov += direction;
			}

			seq_result[save_row][end_mov] = seq_max + 1;
			end_mov += direction;
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	bitonic op;
	op.initialize();
	op.operate();
	return 0;
}