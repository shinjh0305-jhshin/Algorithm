#include <iostream>
#include <string>
#define endl "\n"
#define PLUS '+'
#define MINUS '-'
using namespace std;

int target;
string st;

void calculate(int depth) { //depth�� 2�� ��� 1 __ 2 ���̿� ��� �� �����ڸ� ���Ѵ�.
	
	if (depth == target) {
		int ans = 0, temp = 1;
		char currentOp = PLUS;
		for (int i = 0; i < depth - 1; i++) {
			if (st[i] == ' ') {
				temp = temp * 10 + i + 2;
			}
			else if (currentOp == PLUS) {
				ans += temp;
				temp = i + 2;
				if (st[i] == MINUS) currentOp = MINUS;
			}
			else {
				ans -= temp;
				temp = i + 2;
				if (st[i] == PLUS) currentOp = PLUS;
			}
		}
		//������ ���ڸ� ó���Ѵ�.
		if (currentOp == PLUS) ans += temp;
		else ans -= temp;

		if (ans == 0) {
			for (int i = 1; i < target; i++) {
				cout << i << st[i - 1];
			}
			cout << target << endl;
		}
		return;
	}

	//1. ' '(���� ����) ó��
	st.push_back(' ');
	calculate(depth + 1);
	st.pop_back();

	//2. + ó��
	st.push_back('+');
	calculate(depth + 1);
	st.pop_back();

	//3. - ó��
	st.push_back('-');
	calculate(depth + 1);
	st.pop_back();
}

void operate() {
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++) {
		cin >> target;
		calculate(1);
		cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}