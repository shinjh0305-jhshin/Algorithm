#include <iostream>
#include <queue>	
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

void operate() {
	int rawdata[11][10]; //�� : �ڸ���, �� : MSD
	int target, totalSum = 0, digits;
	queue<int> st;

	cin >> target;

	if (target == 0) { cout << 0 << endl; return; }

	rawdata[1][0] = 1;
	for (int i = 1; i < 10; i++) {
		rawdata[1][i] = 1; 
		totalSum++;

		if (totalSum == target) {
			cout << i << endl;
			return;
		}
	}

	for (int i = 2; i <= 10; i++) {
		rawdata[i][0] = 0;
		for (int j = 1; j < 10; j++) {
			rawdata[i][j] = rawdata[i - 1][j - 1] + rawdata[i][j - 1]; //���� �ڸ���(i)�� MSD�� j�� �� ���� �� �ִ� ������ ����

			if (totalSum + rawdata[i][j] < target) totalSum += rawdata[i][j]; //���� �۾����� MSD�� target�� �������� ���ϸ� ��� �����Ѵ�.
			else {// ���� �۾����� MSD�� ���� ���ڰ� �츮�� ã�� �����̴�. 
				st.push(j); //MSD�� push �Ѵ�.
				digits = i; //�ڸ����� keep �س��´�.
				goto backtrack;
			} 
		}
	}

	if (st.empty()) { //target ��° �����ϴ� ���ڴ� �������� �ʴ´�.
		cout << -1 << endl;
		return;
	}

backtrack:;
	for (int curdigit = digits - 1; curdigit >= 1; curdigit--) { //MSD���� LSD�� ���鼭 ���ʴ�� ���캻��.
		for (int temp = 0; temp < 10; temp++) {
			if (totalSum + rawdata[curdigit][temp] < target) totalSum += rawdata[curdigit][temp];
			else {
				st.push(temp);
				break;
			}
		}
	}

	while (!st.empty()) {
		cout << st.front();
		st.pop();
	}
	cout << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	operate();
	return 0;
}