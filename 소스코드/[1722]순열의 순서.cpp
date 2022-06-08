#include <iostream>
#include <cmath>
#define ll long long
using namespace std;

int num; //�ּ������� ũ�Ⱑ 4�� ������ ���� ����
bool used[21] = { false };

int getNum(int target) { //target��° �̿� ������ ���ڸ� �����ش�
	for (int i = 1; i <= num; i++) {
		if (!used[i]) {
			target--;
			if (target == 0) {
				used[i] = true;
				return i;
			} 
		} 

	}
}

ll numBefore(int target) { //target ������ ������ �� ���� �̿� ������ ���ڰ� �ִ���
	ll ret = 0;
	for (int i = 1; i < target; i++) {
		if (!used[i]) {
			ret++;
		}
	}
	used[target] = true;
	return ret;
}

ll fact(int num) {
	if (num <= 1) return 1;
	return num * fact(num - 1);
}

void operate() {
	int typeOp, numtoGet;
	ll target, div;
	cin >> num >> typeOp;

	div = fact(num); //4!�� ���Ѵ�

	if (typeOp == 1) { //������ ������
		cin >> target; //�� ��°?

		for (int i = num; i > 0; i--) {
			div /= i; //4�� ���ڷ� ����� ������ 4 * 3!�̹Ƿ� 3!���� �����Ѵ�

			numtoGet = target / div; //3!�� �� �� �� �� �ִ°�
			if(target % div) numtoGet++; //�������� ���� ���

			cout << getNum(numtoGet) << ' ';

			target -= div * (numtoGet - 1);
		}
		cout << endl;
	}

	else {
		ll ans = 0;
		for (int i = num; i > 0; i--) {
			cin >> target;
			div /= i;

			ans += numBefore(target)*div;
		}
		cout << ans + 1 << endl;
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}

/*
4
2 2 3 4 1

10
1 124578
1 5 2 9 3 4 8 10 7 6
*/