#include <iostream>
#include <string>
using namespace std;

string a, b;
int len_a, len_b;

int main() {
	cin >> a >> b;
	len_a = a.length(); len_b = b.length();

	int upperBound = len_b - len_a;
	int diff = 9999, diff_temp;

	//b�� �������� a�� ���߰� a�� �� ĭ�� �ڷ� ���������鼭 ����. (���Ʈ����)
	for (int i = 0; i <= upperBound; i++) {
		diff_temp = 0;
		for (int j = 0; j < len_a; j++) { //a�� b�� ���ڸ� �ϳ��� ���Ѵ�.
			if (a[j] != b[i + j]) diff_temp++;
		}
		if (diff_temp < diff) diff = diff_temp;
	}
	cout << diff << endl;
	return 0;
}