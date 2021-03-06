//위상정렬(Activity on Vertex) 문제

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#pragma warning (disable:4996)
#define endl "\n"
using namespace std;

class prerequisite {
private:
	int subjects;
	int prereqs;
	int* in_node; //index의 선수과목 개수를 저장하는 배열
	vector<int>* out_node; //index의 후수과목 index를 저장하는 vector
	int* minSemester;

public:
	prerequisite() :subjects(0), prereqs(0), in_node(NULL), out_node(NULL), minSemester(NULL) {};
	void initialize() {
		cin >> subjects >> prereqs; cin.get();

		in_node = new int[subjects + 1];
		out_node = new vector<int>[subjects + 1];
		minSemester = new int[subjects + 1];
		memset(in_node, 0, sizeof(int)*(subjects + 1));

		int first, next;
		for (int i = 0; i < prereqs; i++) {
			cin >> first >> next; cin.get();

			in_node[next]++;
			out_node[first].push_back(next);
		}
	}

	void operate() {
		int semester = 1, seonsu, iter, num_husu, husu; //iter : 반복문 iter(현재 학기에 들을 수 있는 과목 개수)
		queue<int> qu;
		for (int i = 1; i <= subjects; i++) { //선수과목이 없는 과목들부터 먼저 전부 qu에 넣는다.
			if (in_node[i] == 0)
				qu.push(i);
		}
		iter = qu.size();

		while (iter) { 
			for (int i = 0; i < iter; i++) {
				seonsu = qu.front();
				minSemester[seonsu] = semester; //과목을 들을 수 있는 학기를 저장한다.
				
				num_husu = out_node[seonsu].size(); //이 과목을 선수과목으로 갖는 과목의 개수
				for (int j = 0; j < num_husu; j++) {
					husu = out_node[seonsu][j];
					in_node[husu]--; //후수과목을 이수하기 위해 필요한 선수과목 개수가 줄어든다
					if (in_node[husu] == 0) { //모든 선수 과목을 이수했을 때
						qu.push(husu);
					}
				}
				qu.pop();
			}
			iter = qu.size();
			semester++; //다음 학기로 넘어간다.
		}
	}

	void print_result() {
		for (int i = 1; i <= subjects; i++) {
			cout << minSemester[i] << ' ';
		}
		cout << endl;
	}
};

int main() {
	prerequisite op;
	op.initialize();
	op.operate();
	op.print_result();
	return 0;
}