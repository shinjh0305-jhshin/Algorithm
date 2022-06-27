#include <iostream>
#include <string>
#include <stack>
#define leftPhar -1 //���� �Ұ�ȣ
#define leftSquare -2 //���� ���ȣ
using namespace std;

stack<int> st; //�� �����ϴ� ����
stack<char> testing; //��ȿ�� �Է����� Ȯ���ϴ� ����
string rawdata;

bool initialize() { //�׽�Ʈ���̽��� �Է¹ް� ��ȿ�� �Է����� Ȯ���Ѵ�.
	cin >> rawdata;
	int len_rawdata = rawdata.length();

	for (int i = 0; i < len_rawdata; i++) {
		if (rawdata[i] == '(' || rawdata[i] == '[') {
			testing.push(rawdata[i]);
		}
		else {
			if (rawdata[i] == ')') { //�ݴ� �Ұ�ȣ ���� ���
				if (testing.empty() || testing.top() != '(') return false;
				else testing.pop();
			}
			else { //�ݴ� ���ȣ ���� ���
				if (testing.empty() || testing.top() != '[') return false;
				else testing.pop();
			}
		}
	}

	if (testing.empty()) return true; //���ÿ��� dangling bracket ���� ���� �� ���� ���
	else return false; //���� ��ȣ�� �ִ� ���
}

int seekFor(int target) {
	int answer = 0;
	while (st.top() != target) {
		answer += st.top();
		st.pop();
	}
	st.pop(); //���� ��ȣ�� �����Ѵ�

	if (answer == 0) return 1; //���ڸ��� ���� ��쿡�� 1�� �����Ѵ�
	else return answer; //�ȿ� ��ȣ���� �ִ� ���, ��ȣ�ĵ��� ���� ���ؼ� �����Ѵ�
}

void operate() {
	int len = rawdata.length();
	for (int i = 0; i < len; i++) {
		if (rawdata[i] == '(') st.push(leftPhar);
		else if (rawdata[i] == '[') st.push(leftSquare);
		else if (rawdata[i] == ')') {
			st.push(2 * seekFor(leftPhar)); //�Ұ�ȣ�� ����ġ 2
		}
		else if (rawdata[i] == ']') {
			st.push(3 * seekFor(leftSquare)); //���ȣ�� ����ġ 3
		}
	}

	int ans = 0;
	while (!st.empty()) {
		ans += st.top();
		st.pop();
	}

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	if (initialize()) {
		operate();
	}
	else cout << 0 << endl;

	return 0;
}