#include <iostream>
#include <vector>
#pragma warning (disable:4996)
#define endl "\n"
using namespace std;

class dec_order {
private:
	vector<int> rawdata;
	int* seq_size = NULL;
	int sz_rawdata;

public:
	void initialize() {
		cin >> sz_rawdata;
		rawdata.reserve(sz_rawdata);
		seq_size = new int[sz_rawdata];

		int num_in;
		for (int i = 0; i < sz_rawdata; i++) {
			cin >> num_in;
			rawdata.push_back(num_in);
		}
	}

	void operate() {
		//global_max : ��ü �� �ִ�, local_max : �� finish �������� �ִ�
		//front_mov : ������ ���� ���, finish : ������ ���ڰ� �� �ڸ�
		int global_max = 0, local_max, front_mov, finish;
		
		for (finish = 0; finish < sz_rawdata; finish++) {
			local_max = 0;
			for (front_mov = 0; front_mov <= finish; front_mov++) {
				if (front_mov == finish) {
					seq_size[finish] = ++local_max;
					if (local_max > global_max) {
						global_max = local_max;
					}
				}
				else if (rawdata[front_mov] > rawdata[finish]) {
					if (seq_size[front_mov] > local_max) {
						local_max = seq_size[front_mov];
					}
				}
			}
		}
		cout << global_max << endl;
	}
};

int main() {
	ios::sync_with_stdio(false);
	dec_order op;
	op.initialize();
	op.operate();
	return 0;
}