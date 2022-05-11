#include <iostream>
#include <string>
#define endl "\n"
using namespace std;

string st = "";
int len;

bool isGoodString(int stLen) {
	string a, b;
	for (int i = 1; i <= stLen / 2; i++) {
		a = st.substr(stLen - i, i);
		b = st.substr(stLen - i * 2, i);
		if (a == b) return false;
	}
	return true;
}

bool make_st(int stLen) {
	if (stLen == len) return true;
	for (int i = 1; i <= 3; i++) {
		st += i + '0';
		if (isGoodString(stLen + 1)) {
			if (make_st(stLen + 1)) return true;
		}
		st.pop_back();
	}
	return false;
}

void operate() {
	cin >> len;
	make_st(0);
	cout << st << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	operate();

	return 0;
}


//bool make_ans(int depth) {
//	int temp;
//	bool status;
//
//	for (temp = 1; temp <= 3; temp++) {
//		if (answer.empty()) { //depth == 1�� ���, �� ù ��° ���ڸ� ���ϴ� ����.
//			answer.push_back(temp);
//			status = true;
//		}
//		else if (temp == answer.back()) continue; //�� ���ڶ� ������ �ٷ� ���� ���ڷ� �Ѿ��
//		else {
//			auto pos = find(answer.rbegin(), answer.rend(), temp);
//			if (pos == answer.rend()) { //ó�� ������ ���ڴ�
//				answer.push_back(temp);
//				status = true;
//			}
//			else {
//				auto right = answer.rbegin();
//				auto left = pos + 1;
//				status = false;
//				while (right != pos) {
//					if (left == answer.rend() || *left != *right) { //���������̴�
//						answer.push_back(temp);
//						status = true;
//						break;
//					}
//					else { //���� �����̴�
//						right++;
//						left++;
//					}
//				}
//			}
//		}
//		if (status == true) { //���� ������ �ϼ��Ǿ���.
//			if (depth == len) return true; //�־��� ������ ���� ������ �ϼ��ߴ�
//
//			if (make_ans(depth + 1)) return true;
//			else answer.pop_back();
//		}
//	}
//
//	if (temp > 3) { //���� �ܰ��� ���� �߸��Ǿ���.
//		return false;
//	}
//}
//
//void operate() {
//	cin >> len;
//
//	make_ans(1);
//
//	for (auto it : answer) {
//		cout << it;
//	}
//	cout << endl;
//}

