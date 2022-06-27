#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, int> inOrder;
int outOrder[1003];
int cars;

void operate() {
	cin >> cars;

	string temp;
	for (int i = 0; i < cars; i++) {
		cin >> temp;
		inOrder[temp] = i;
	}

	for (int i = 0; i < cars; i++) {
		cin >> temp;
		outOrder[i] = inOrder[temp];
	}

	int ans = 0;
	for (int i = 0; i < cars - 1; i++) {
		for (int j = i + 1; j < cars; j++) {
			if (outOrder[i] > outOrder[j]) { //��(i) ���Ŀ� ���� �� �߿��� ������ ���� �� ���� �ִ��� Ȯ��!
				ans++;
				break;
			}
		}
	}

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}