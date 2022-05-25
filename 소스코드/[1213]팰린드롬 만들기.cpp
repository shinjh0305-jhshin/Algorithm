#include <iostream>	
#include <string>
#include <algorithm>
using namespace std;

int check[26] = { 0 };
string st;
int len_st;

void initialize() {
	cin >> st;
	
	len_st = st.length();
	for (int i = 0; i < len_st; i++) {
		check[st[i] - 'A']++;
	}
}

int operate() {
	bool isOdd = false;
	string newString = "";

	if (len_st % 2) { //���̰� Ȧ���� ���
		for (int i = 0; i < 26; i++) { //Ȧ���� �� 1���� �־�� �Ѵ�.
			if (check[i] % 2 && isOdd) return 1;
			else if (check[i] % 2) isOdd = true;
		}


	}
	else { //���̰� ¦���� ���
		for (int i = 0; i < 26; i++) {
			if (check[i] % 2) return 1;
		}
	}
	

	int oddChar;
	for (int i = 0; i < 26; i++) {
		if (check[i]) {
			for (int iter = 0; iter < check[i] / 2; iter++) {
				newString += i + 'A';
			}
			
			if (check[i] % 2) oddChar = i; //Ȧ�� ������ ����
		}
	}

	string copyString = newString;
	reverse(copyString.begin(), copyString.end()); //�� �κ� �Ӹ������ �����.

	if (len_st % 2) newString += oddChar + 'A'; //Ȧ������ ���ڴ� ��� �ϳ��� �� ����ִ´�
	newString += copyString;


	for (auto it : newString) {
		cout << it;
	}
	cout << endl;
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();

	if (operate()) {
		cout << "I'm Sorry Hansoo" << endl;
	}

	return 0;
}