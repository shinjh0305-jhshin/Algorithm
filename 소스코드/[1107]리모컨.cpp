#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class remoteControl {
private:
	int target = 0;
	int brokenButton = 0;
	int result = 0;
	vector<int> broken;

public:
	void initialize() {
		cin >> target; 
		cin >> brokenButton; 

		int temp;
		if (brokenButton) {
			for (int i = 0; i < brokenButton; i++) {
				cin >> temp; cin.get();
				broken.push_back(temp);
			}

			sort(broken.begin(), broken.end());
		}
	}

	void operate() {
		//step 1 : ���翡�� ���� �� ã��
		int current = abs(target - 100);
		if (brokenButton == 10) { result = current; return; }

		//step 2 : Max min ã��
		int maxmin = target, temp, maxmin_digit, maxmin_temp, msb_std; //maxmin : ���峭 ��ư�� ���� ��쿡 ����� �ʱ�ȭ �� ����
		maxmin_digit = digit(maxmin) - 1; //10�� n�¿��� n�� �ش��ϴ� ����
		maxmin_temp = maxmin;
		while (maxmin_digit >= 0) {
			if (maxmin > 5000000) break;

			msb_std = pow(10, maxmin_digit);
			temp = maxmin_temp / msb_std;

			if (isBroken(temp)) {
				maxmin = (maxmin / msb_std + 1)*msb_std;
				maxmin_digit = digit(maxmin) - 1;
				maxmin_temp = maxmin;
			}

			else {
				maxmin_temp = maxmin_temp % (int)pow(10, maxmin_digit);
				maxmin_digit--;
			}
		}

		maxmin = digit(maxmin) + (maxmin - target);

		//step 3 : min Max ã��
		int minmax = target, minmax_digit, minmax_temp, lsb_std; //msb_std : 10�� 4���̸� 10000
		minmax_digit = digit(minmax) - 1;
		minmax_temp = minmax;

		//�տ� �� ���� ���ϸ鼭
		//�տ� ���� ���峭 ���ڸ�, ���鼭 �ڿ� ���ڸ� 9999...�� �����
		while (minmax_digit >= 0) {
			if (minmax < 0) {
				minmax = -500005;
				break;
			} 
			lsb_std = pow(10, minmax_digit);
			temp = minmax_temp / lsb_std;

			if (isBroken(temp)) {
				minmax = (minmax / lsb_std - 1)*lsb_std + lsb_std - 1;
				minmax_digit = digit(minmax) - 1;
				minmax_temp = minmax;
			}

			else {
				minmax_temp = minmax_temp % lsb_std;
				minmax_digit--;
			}
			
		}
		minmax = digit(minmax) + (target - minmax);

		result = min(current, maxmin);
		result = min(result, minmax);
	}

	void print() {
		cout << result << endl;
	}
		

	int isBroken(int button) {
		for (int i = 0; i < broken.size(); i++) {
			if (button == broken[i]) return 1;
		}
		return 0;
	}

	int digit(int num) {
		int result = 0;
		do {
			result++;
			num /= 10;
		} while (num);
		return result;
	}
};

int main() {
	remoteControl op;
	op.initialize();
	op.operate();
	op.print();

	return 0;
}