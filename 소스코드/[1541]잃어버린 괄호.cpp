//������ ������ ���� �� �ڿ� �ִ� ���ڵ��� ��� ���� ������ ���� ���� �����ϴ�.

#include <iostream>
#include <string>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class lost {
private:
	string st;
	int temp, ans; //temp : ���� �۾����� ���� ����  ans : ���� �����
	bool status; //������ ���� ������ ��ȣ�� ����. true : +  false : -

public:
	void initialize() {
		getline(cin, st);
		status = true;
		temp = ans = 0; //ù ������ ����̸�, temp�� �ʱ�ȭ�Ѵ�.
	}

	void operate() {
		char ch;

		for (int i = 0; i < st.length(); i++) {
			ch = st[i];

			if (ch >= '0' && ch <= '9') { //����
				temp *= 10; temp += ch - '0';
			}
			else { //��ȣ
				if (ch == '+') {
					//1. ������ ���� ��ȣ�� -�� ���(status�� false) : ���� ���ڸ� ����.
					if (status == false) {
						ans -= temp;
					}
					//2. ������ ���� ��ȣ�� +�� ���(status�� true) : ���� ���ڸ� ���Ѵ�.
					else if (status == true) {
						ans += temp;
					}
				}
				else if (ch == '-') {
					//1. ������ ���� ��ȣ�� -�� ���(status�� false) : ���� ���ڸ� ����.
					if (status == false) {
						ans -= temp;
					}
					//2. ������ ���� ��ȣ�� +�� ���(status�� true) : ���� ���ڸ� ���ϰ�, flag�� �ٲ۴�.
					else if (status == true) {
						ans += temp;
						status = false;
					}
				}

				temp = 0;
			}
		}

		if (status == false) ans -= temp;
		else if (status == true) ans += temp;

		cout << ans << endl;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	lost op;
	op.initialize();
	op.operate();

	return 0;
}