#include <iostream>
#include <cstring>
#include <string>
#define endl "\n"
using namespace std;

class checker {
private:
	int	words;
	bool history[26];  //�̹� ���� �������� �����ϴ� ����
	string st;

public:
	void operate() {
		int len, temp, j, answer = 0;
		cin >> words; 

		for (int i = 0; i < words; i++) {
			memset(history, false, sizeof(history)); //�� �׽�Ʈ���̽����� �ʱ�ȭ�Ѵ�.
			cin >> st;
			len = st.length();

			for (j = 0; j < len; j++) {
				temp = st[j] - 'a'; //�ε��� 0 ���� �����ϵ��� �ٲ۴�.
				if (history[temp] == 0) history[temp] = true; //ó�� ��Ÿ���� ����
				else {
					if (st[j] == st[j - 1]) continue;
					else break;
				}
			}

			if (j == len) answer++;
		}

		cout << answer << endl;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	checker op;
	op.operate();

	return 0;
}