#include <iostream>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	//target : ���ʿ� ���� ����  target_mov : �����Ǵ� ����  target_cnt : ī����
	int target, target_mov, target_cnt = 0;
	cin >> target;

	//udigit : �����ڸ���  ldigit : �����ڸ���  newldigit : ���� �����Ǵ� �����ڸ���
	int udigit, ldigit, newldigit;
	target_mov = target;

	do {
		udigit = target_mov / 10;
		ldigit = target_mov % 10;
		newldigit = (udigit + ldigit) % 10;

		target_mov = 10 * ldigit + newldigit;
		target_cnt++;
	} while (target != target_mov);

	cout << target_cnt << endl;

	return 0;
}