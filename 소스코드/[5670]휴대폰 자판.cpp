#include <iostream>
#include <string>
#include <vector>
#define endl "\n"
using namespace std;

struct TRIE {
	int cnt = 0;
	bool finish = false;
	TRIE* charExist[26] = { NULL };
};

TRIE* root = NULL;
vector<string> st;
int sz_st;

void initialize() {
	st.resize(sz_st);
	for (int i = 0; i < sz_st; i++) {
		cin >> st[i];
	}
	root = new TRIE;
}

void eraseTRIE(TRIE* node) {
	for (int i = 0; i < 26; i++) {
		if (node->charExist[i]) eraseTRIE(node->charExist[i]);
	}
	delete node;
}

void makeTRIE() {
	TRIE* curTRIE = NULL;

	int st_len, curChar;
	for (int i = 0; i < sz_st; i++) {
		st_len = st[i].length();
		curTRIE = root;

		for (int mov = 0; mov < st_len; mov++) {
			curChar = st[i][mov] - 'a';
			if (!curTRIE->charExist[curChar]) {
				curTRIE->cnt++;
				curTRIE->charExist[curChar] = new TRIE;
			}
			curTRIE = curTRIE->charExist[curChar];
			if (mov == st_len - 1) curTRIE->finish = true;
		}
	}
}

void checkString() {
	int st_len, curChar;
	double totalcnt = 0, cnt = 0;
	TRIE* curTRIE;

	for (int i = 0; i < sz_st; i++) {
		st_len = st[i].length();
		curTRIE = root;

		cnt = 1; //ù ���ڴ� �Է��Ѵ�.
		for (int mov = 0; mov < st_len - 1; mov++) {
			curChar = st[i][mov] - 'a';
			curTRIE = curTRIE->charExist[curChar];
			if (curTRIE->cnt > 1 || curTRIE->finish) cnt++; //���� �� �ִ� ���ڰ� 2�� �̻��̰ų� ���⼭ ���� �� ���ڰ� �ִ�.
		}
		totalcnt += cnt;
	}

	cout << totalcnt / sz_st << endl;
}

void operate() {
	makeTRIE();
	checkString();
	eraseTRIE(root);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cout << fixed;
	cout.precision(2);

	while (cin >> sz_st) {
		initialize();
		operate();
	}

	return 0;
}