#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <Windows.h>
#pragma warning (disable:4996)
using namespace std;

string hello = u8"�ȳ��ϼ���. �������Դϴ�.";
u32string anthem = U"���ع��� ��λ��� ������ �⵵��";
u32string st = U"���ع���";
u16string school = u"�������б� ��ǻ�Ͱ��а� CSE_4011";

int main() {
	//UTF-32������ ��� �����ڵ� ���ڸ� 4����Ʈ ������ ����.
	cout << anthem.length() << endl; //17 (���� 17����)
	if (anthem.substr(0, 4) == st) { //���ع��� == ���ع���
		cout << "true" << endl;
	}
	if (anthem.find(U"��") != u32string::npos) {
		cout << "found" << endl;
	}

	//UTF-8
	size_t i = 0, len = 0;
	while (i < hello.length()) {
		int char_size = 0;
		if ((hello[i] & 0b11111000) == 0b11110000) {
			char_size = 4;
		}
		else if ((hello[i] & 0b11110000) == 0b11100000) {
			char_size = 3;
		}
		else if ((hello[i] & 0b11100000) == 0b11000000) {
			char_size = 2;
		}
		else {
			char_size = 1;
		}

		cout << hello.substr(i, char_size) << endl;
		i += char_size;
		len++;
	}
	cout << "total length : " << len << endl;

	//UTF-16
	cout << school.length() << endl;
	if (school.find(u"CSE") != u16string::npos) {
		cout << "find" << endl;
	}

	//wstring�� cout �� ��, �ѱ������� �˷��ִ� �뵵.
	locale::global(locale(""));
	wcout.imbue(locale());

	//����������
	string st = "���ع��� ��λ��� ������ �⵵�� �ϴ����� �����ϻ� �츮���� ����.";
	string rawdata[][10] = { 
		{ "��", "��", "��", " ", "��", "��", "��", "��", "��", "��" },
		{ "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" },
		{ "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" }
	};

	return 0;
}