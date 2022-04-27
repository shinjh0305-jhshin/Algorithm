#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

enum teamName { _start, _link };
int map[21][21];
vector<int> team[2];
int sz_map, result = 2134567890;

void initialize() {
	cin >> sz_map;
	for (int i = 0; i < sz_map; i++) {
		for (int j = 0; j < sz_map; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < 2; i++) {
		team[i].reserve(sz_map / 2 + 1);
	}
}

void make_score(int curNode) {
	if (curNode == sz_map) {
		int score[2] = { 0 }, sz_team;
		for (int i = 0; i < 2; i++) {
			sz_team = sz_map / 2;

			for (int j = 0; j < sz_team - 1; j++) {
				for (int k = j + 1; k < sz_team; k++) {
					score[i] += (map[team[i][j]][team[i][k]] + map[team[i][k]][team[i][j]]);
				}
			}
		}

		result = min(result, abs(score[_start] - score[_link]));
	}
	else {
		int start_size = team[_start].size(), link_size = team[_link].size();

		//1. curNode�� start ���� ���� ���
		/////////////////////////////////////
		team[_start].push_back(curNode);
		if (team[_start].size() == sz_map / 2) { //start ���� �� �� ���
			for (int i = curNode + 1; i < sz_map; i++) { //���� ���� ���� �� link���� �ִ´�
				team[_link].push_back(i);
			}
			make_score(sz_map); //���� ��� �ܰ�� �ٷ� ����
		}
		else make_score(curNode + 1);

		//���󺹱� ��Ų��.
		team[_start].pop_back();
		while (team[_link].size() != link_size) { //���� ���� ���� link�� �־��� ���, ���� ������.
			team[_link].pop_back();
		}

		//2. curNode�� link ���� ���� ���
		/////////////////////////////////////
		team[_link].push_back(curNode);
		if (team[_link].size() == sz_map / 2) { //link ���� �� �� ���
			for (int i = curNode + 1; i < sz_map; i++) { //���� ���� ���� �� start���� �ִ´�
				team[_start].push_back(i);
			}
			make_score(sz_map); //���� ��� �ܰ�� �ٷ� ����
		}
		else make_score(curNode + 1);

		//���󺹱� ��Ų��.
		team[_link].pop_back();
		while (team[_start].size() != start_size) { //���� ���� ���� start�� �־��� ���, ���� ������.
			team[_start].pop_back();
		}
	}
}

void operate() {
	make_score(0);
	cout << result << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}