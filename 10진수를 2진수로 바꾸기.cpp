#include <iostream>
#include <bitset> //vector<bool>�� �����ϸ� �ȴ�.
#include <string>
#pragma warning (disable:4996)
using namespace std;

int main() {
	unsigned int num;
	cout << "10���� : ";
	cin >> num;

	auto rawdata = bitset<32>(num);

	string st = rawdata.to_string();
	st = st.substr(st.find('1'));

	cout << "2���� : ";
	cout << st << endl;
	cout << "1�� ���� : ";
	cout << rawdata.count() << endl;
	cout << "bitset ������ : ";
	cout << rawdata.size();
	return 0;
}