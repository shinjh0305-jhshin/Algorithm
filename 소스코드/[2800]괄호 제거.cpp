#include <iostream>
#include <string>
#define endl "\n"
using namespace std;

string original, working;
int strLen;
bool notRemovedAtAll = true;

void initialize() {
	cin >> original;
	strLen = original.length();
}

int makeWorkingString(bool prevRemoved, int idx) { //prevRemoved : ���� ��ȣ�� ���� �Ǿ��°�?
	int mov;
	for (mov = idx; mov < strLen; mov++) { 
		if (original[mov] == '(') {
			//1. ��ȣ�� ���� �ϴ� ����� ���� �����غ���
			working.push_back('(');
			makeWorkingString(false, mov + 1);
			working.pop_back(); //���� ��ȣ�� �����Ѵ�.

			//2. ��ȣ�� ���ִ� ����� ���� �����غ���
			notRemovedAtAll = false;
			mov = makeWorkingString(true, mov + 1);
		}
		else if (original[mov] == ')' && prevRemoved) continue; //�ݴ� ��ȣ�� ���԰�, ���� ���� ��ȣ�� ���� �� ���
		else working.push_back(original[mov]);
	}
	if (mov == strLen && !notRemovedAtAll) cout << working << endl; //working�� ����Ѵ�.
	while (working.length() != idx) working.pop_back(); //string�� pop �Ѵ�
}

void operate() {
	makeWorkingString(false, 0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}