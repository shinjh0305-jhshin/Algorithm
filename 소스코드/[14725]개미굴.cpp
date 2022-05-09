#include <iostream>
#include <map>
#include <string>
using namespace std;

struct TRIE {
	map<string, TRIE*> child;
};

TRIE rootNode;

void print_result(TRIE* currentNode, int depth) {
	for (auto it : currentNode->child) {
		for (int i = 0; i < depth * 2; i++) {
			cout << '-';
		}
		cout << it.first << endl;
		print_result(it.second, depth + 1);
	}
}

void operate() {
	int opers, depth;
	string target;
	TRIE* currentNode, *newTRIE;
	cin >> opers;

	for (int i = 0; i < opers; i++) {
		currentNode = &rootNode;

		cin >> depth; //�̵��� ���̸� �޴´�
		for (int j = 0; j < depth; j++) {
			cin >> target; //���� �̸�

			auto it = currentNode->child.find(target);
			if (it == currentNode->child.end()) { //Ž���� �� ���� �����
				newTRIE = new TRIE(); //���ο� �ڽ� ���
				currentNode->child.insert({ target, newTRIE });
				currentNode = newTRIE; //���� �ڽ� ���� ����
			}
			else { //Ž���� �� �ִ� �����
				currentNode = (*it).second; //�� ���� ����.
			}
		}
	}
	print_result(&rootNode, 0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}

//4ms ���--�������� �̰� ����!!
//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<set>
//using namespace std;
//
//set<string> s;
//
//int main() {
//
//	int N, K, t;
//	cin >> N;
//
//	for (int i = 0; i < N; i++) {
//		cin >> K;
//		string tmp = "";
//		string str = "";
//		for (int j = 0; j < K; j++)
//		{
//			cin >> tmp;
//			str += "*" + tmp;
//			s.insert(str);
//		}
//	}
//
//	for (auto value : s) {
//		int cnt = count(value.begin(), value.end(), '*');
//		int pos = value.find_last_of("*");
//		string tmp = value.substr(pos + 1);
//		for (int i = 0; i < cnt - 1; i++) cout << "--";
//		cout << tmp << '\n';
//	}
//}