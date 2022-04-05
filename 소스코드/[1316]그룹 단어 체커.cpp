#include <iostream>
#include <cstring>
#include <string>
#define endl "\n"
using namespace std;

class checker {
private:
	int	words;
	int history[26]; //�̹� ���� �������� �����ϴ� ����
	string st;

public:
	void operate() {
		int len, temp, j, answer = 0;
		cin >> words; cin.get();

		for (int i = 0; i < words; i++) {
			memset(history, 0, sizeof(int) * 26);
			getline(cin, st);
			
			len = st.length();
			for (j = 0; j < len; j++) {
				temp = st[j] - 'a';
				if (history[temp] == 0) history[temp] = 1; //ó�� ��Ÿ���� ����
				else {
					if (temp == st[j - 1] - 'a') continue;
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