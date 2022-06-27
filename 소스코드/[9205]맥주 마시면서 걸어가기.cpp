#include <iostream>
#include <cstring>
#include <vector>
#define endl "\n"
#define isPossible(a, b, c, d) ((double)(abs((a) - (c)) + abs((b) - (d))) / 50 <= 20)
using namespace std;

int cvs; //������ ����
pair<int, int> house, festival;
pair<int, int> store[102];
bool visited[102];

void initialize() {
	memset(visited, false, sizeof(visited));
	cin >> cvs;

	cin >> house.first >> house.second;
	for (int i = 0; i < cvs; i++) {
		cin >> store[i].first >> store[i].second;
	}
	cin >> festival.first >> festival.second;
}

bool traverse(int row, int col) {
	if (isPossible(row, col, festival.first, festival.second)) { //�� ��ġ���� �ٷ� ��Ÿ��Ʈ�� �� �� �ִ�.
		return true;
	}

	int nextrow, nextcol;
	for (int i = 0; i < cvs; i++) {
		nextrow = store[i].first; nextcol = store[i].second;
		if (!visited[i] && isPossible(row, col, nextrow, nextcol)) { //�湮���� ���� �������̰�, �� �� �ִ� �������̴�.
			visited[i] = true;
			if (traverse(nextrow, nextcol)) return true;
		}
	}

	return false;
}

void operate() {
	if (traverse(house.first, house.second)) cout << "happy" << endl;
	else cout << "sad" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int cases;
	cin >> cases;

	while (cases--) {
		initialize();
		operate();
	}

	return 0;
}