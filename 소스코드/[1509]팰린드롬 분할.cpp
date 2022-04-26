#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool dp[2505][2505] = { false };
int result[2505];
string st;
int sz_string;

void initialize() {
	cin >> st;
	sz_string = st.size();
	st.insert(0, "."); //string index�� ���� dummy character
	
	//�κ� ���ڿ��� �Ӹ������ �Ǵ����� �Ǻ��ϴ� �����̴�.
	//���ڿ��� ���� ������ �Ӹ���� ���θ� �����Ѵ�.
	for (int i = 1; i <= sz_string; i++) {
		dp[i][i] = true; //���̰� 1�� ���ڿ��� �Ӹ�����̴�.
		if (i <= sz_string - 1 && st[i] == st[i + 1]) { //���̰� 2�� ���ڿ��� �Ӹ���� ���� �Ǻ�.
			dp[i][i + 1] = true;
		}
	}

	int end_of_start, end;
	for (int sz = 3; sz <= sz_string; sz++) { //���̰� 3 �̻��� ���ڿ��� �Ӹ���� ���� �Ǻ�.
		end_of_start = sz_string - (sz - 1); //end_of_start : ���ڿ��� ���� ������ ���Ѽ�

		for (int start = 1; start <= end_of_start; start++) { //start : ���ڿ��� ���� ����
			end = start + sz - 1; //end : ���ڿ��� ���� ����

			if (st[start] == st[end] && dp[start + 1][end - 1] == 1) { //�� ������ ����, �߰��� �Ӹ�����̸� �Ӹ����!
				dp[start][end] = true;
				continue;
			}
		}
	}
}

void operate() {
	result[0] = 0; //���ڿ��� ó������ ������ �Ӹ�������� �Ǻ��ϴ� ��츦 ����� dummy data.

	//���ڿ��� ���� ������ �������� �Ǻ��Ѵ�.
	for (int back = 1; back <= sz_string; back++) {
		result[back] = 1234567890;
		//ó��(start)���� ���� ����(back)���� �� ĭ�� �ڷΰ��� �� ������ �ɰ��� Ȯ���ϴµ�,
		//�ɰ��� �κк��� �������� �Ӹ�����̶��
		//(ó������ �ɰ��� �κб��� �Ӹ������ �ּ� ���� + 1) ��ŭ�� �Ӹ������ �����.

		for (int start = 1; start <= back; start++) { 
			if (dp[start][back]) {
				result[back] = min(result[back], result[start - 1] + 1);
			}
		}
	}

	cout << result[sz_string] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}