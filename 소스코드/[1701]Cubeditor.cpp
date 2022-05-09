#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string st;
int sz_string;
vector<int> len;

void initialize() {
	cin >> st;
	sz_string = st.length();
	len.resize(sz_string);
}

void failure() {
	int left, ans = 0;

	for (int left_bound = 0; left_bound < sz_string - 1; left_bound++) { //LEFT�� �� �����̸� �� ó������ �����ϴ� ����� ���� �ȴ�!!!!
		left = left_bound; //������ ���ڿ��� ó������ ������ ��� ���� �ȴ�.
		len[left] = - 1;

		for (int right = left_bound + 1; right < sz_string; right++) { //������ʹ� �Ϲ����� KMP�� �����ϴ�.
			while (1) { 
				if (st[left] == st[right]) {
					len[right] = left - left_bound; //KMP�� index ����̱⿡, ���� ������ �и� ��ŭ �̸� ��������� ���ش�.
					left++;
					break;
				}
				if (left == left_bound) { //left �����Ͱ� �������� ���ƿ��� ���.
					len[right] = - 1;
					break;
				}

				left = len[left - 1] + left_bound + 1; //���� �и� ������ŭ ���� �����Ѵ�.
			}
			ans = max(ans, len[right] + 1); // �� �ܰ辿 ���� �� ������ �ִ��� �����Ѵ�.
		}
	}
	

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	failure();

	return 0;
}

/*
asexexssexessex
ans : 4
*/