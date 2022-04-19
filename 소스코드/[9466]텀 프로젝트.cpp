#include <iostream>
#include <bitset>
#include <stack>
#define endl "\n"
using namespace std;

int rawdata[100003];
int test_cases, sz_rawdata, sz_impossible;
enum status { group = -1, impossible };
bitset<100003> visited(0);

void initialize() {
	cin >> sz_rawdata;
	for (int i = 1; i <= sz_rawdata; i++) {
		cin >> rawdata[i];
	}
}

void scan(int num) {
	stack<int> st;
	visited.reset();

	int curnum = num, nextnum, temp;
	while (1) {
		st.push(curnum);
		visited[curnum] = true;
		nextnum = rawdata[curnum];

		if (nextnum > 0) { //Ž���� �� �� ����� �� �ִ� ���
			if (visited[nextnum]) { //group ������. ��, loop �߰ߵ�.
				//stack�� �ִ� ����� ���� group���� �����
				while (1) {
					temp = st.top();
					rawdata[temp] = group;
					st.pop();
					if (temp == nextnum) { //group�� ���������� ���ƿԴ�.
						break;
					}
				}
				while (!st.empty()) { //�����ص� �ڽŰ��� ���� ���� �׷��� ������. �׷� ���� �Ұ�.
					rawdata[st.top()] = impossible; 
					sz_impossible++;
					st.pop();
				}
				break;
			}
			else { //���� group�� �������� ����.
				curnum = nextnum;
			} 
		}

		else { //Ž��������, group�� ���� �� �ϴ� ������� �Ǻ���.
			st.pop(); //st.top�� �̹� impossible�� ī��Ʈ �� ����̴�.
			//stack�� �ִ� ����� ���� impossible�� ��ũ�Ѵ�
			while (!st.empty()) {
				rawdata[st.top()] = impossible;
				sz_impossible++;
				st.pop();
			}
			break;
		}

	}
}

void operate() {
	sz_impossible = 0;
	for (int i = 1; i <= sz_rawdata; i++) {
		if (rawdata[i] > 0) scan(i);
	}
	cout << sz_impossible << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> test_cases;
	for (int i = 0; i < test_cases; i++) {
		initialize();
		operate();
	}

	return 0;	
}

/*
1
8
1 2 3 4 5 6 7 8
ans : 0

1
7
3 1 3 7 3 4 6
ans : 3

1
4
2 4 2 3
ans : 1

1
7
2 3 4 2 6 7 5
ans : 1

1
5
3 3 1 2 1
ans : 3

1
5
2 3 4 5 4
ans : 3
*/