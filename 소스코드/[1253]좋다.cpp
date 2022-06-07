#include <iostream>
#include <unordered_set>
using namespace std;

int nums, maxNum = -2134567890, minNum = 2134567890;
unordered_multiset<int> rawdata;
unordered_multiset<int> resultNum;

void initialize() {
	cin >> nums;
	
	int temp;
	for (int i = 0; i < nums; i++) {
		cin >> temp;
		rawdata.insert(temp);

		maxNum = maxNum > temp ? maxNum : temp;
		minNum = minNum < temp ? minNum : temp;
	}
}

void operate() {
	int add2, result = 0;

	for (const auto target : rawdata) {
		for (const auto add1 : rawdata) {
			if (&target == &add1) continue; //add1 target�� ���� �ٸ� ���� ������ �� ������ �����

			add2 = target - add1;
			if (add1 == add2 && rawdata.count(add1) < 2) continue; //add1 add2�� ���� �ٸ� ���� ������ �� ������ �����

			if (rawdata.find(add2) != rawdata.end()) { //add2�� �����Ѵ�
				if (add1 == 0 && add2 == 0) {
					if (rawdata.count(0) >= 3) { //add1 == add2 == target == 0�� Ư����Ȳ
						result++; break;
					}
				}
				else if (add1 == 0 || add2 == 0) {
					if (rawdata.count(target) >= 2) { //add1, add2�� target�� ���� �ٸ� ���� �����ϴ� ���� �����
						result++; break;
					}
				}
				else { //�ߺ� ��Ȳ�� �߻����� �ʴ´�.
					result++; break;
				}
			}

		}
	}

	cout << result << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}