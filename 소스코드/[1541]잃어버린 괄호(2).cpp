#include <iostream>
#include <string>
using namespace std;

string st;

void initialize() {
	cin >> st;
}

void operate() {
	int result = 0, st_len = st.length();
	bool flag = false; //'-'��ȣ�� ���Գ�?

	int start = 0;
	for (int i = 1; i < st_len; i++) {
		if (st[i] == '+' || st[i] == '-') { //������ ��ȣ�� ������ ���
			if (flag == true) result -= stoi(st.substr(start, i - start)); //������ - ��ȣ�� ���Ծ�����
			else { //������ - ��ȣ�� �� ���Ծ�����
				result += stoi(st.substr(start, i - start));
				if (st[i] == '-') flag = true; //���� ��ȣ�� -�� ���, ������ ��� ���ڸ� ����.
			}
			start = i + 1;
		}
	}
	if (flag == true) result -= stoi(st.substr(start, st_len - start));
	else result += stoi(st.substr(start, st_len - start));

	cout << result << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}