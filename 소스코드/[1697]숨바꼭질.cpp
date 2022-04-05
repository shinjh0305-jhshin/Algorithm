#include <iostream>
#include <queue>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

bool visited[100005] = { false };
queue<int> qu;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int mPos, fPos; //mPos : �����̴�(moving) ��ġ(������), fPos : ������(fixed) ��ġ(����)
	
	cin >> mPos >> fPos;
	
	qu.push(mPos); visited[mPos] = true;

	int time = 0, size, current, candidate;

	while (1) {
		size = qu.size();
		for (int i = 0; i < size; i++) {
			current = qu.front(); qu.pop();
			if (current == fPos) goto end; //���� �߰�!!

			for (int j = 0; j < 3; j++) {
				if (j == 0) candidate = current - 1;
				else if (j == 1) candidate = current + 1;
				else candidate = current * 2;

				if (candidate < 0 || candidate > 100000 || visited[candidate]) continue; //�� �� ���ų� �� �ʿ䰡 ���� ��

				visited[candidate] = true;
				qu.push(candidate);				
			}			
		}
		time++;
	}

end:;
	cout << time << endl;
	return 0;
}