#include <iostream>
#define endl "\n"
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int cases, a, b;
	cin >> cases; cin.get(); //CRLF ����

	for (int i = 0; i < cases; i++) {
		a = cin.get() - '0';
		cin.get(); //, ����
		b = cin.get() - '0';
		cout << a + b << endl;
		cin.get(); //CRLF ����
	}

	return 0;
}