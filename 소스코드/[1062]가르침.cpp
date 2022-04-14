//bitset�� �̿��ؼ� �ð� �ٿ�����

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string>
using namespace std;

int words, numLearn, ans = 777;
vector<int> rawdata; //������ �ܾ���� ���� �κ��� bitmasking �� �� ����. (antic����)
vector<int> rawdataNum; //���� �κп��� �� ���̶� ���� ������ bitmask index ����. (antic����)

void initialize() {
	cin >> words >> numLearn;
	
	numLearn -= 5; //antic�� ������ �����ľ��ϱ⿡, �̸� ������ ������ ���ĺ��� ����ģ��.
	rawdata.resize(words);
	
	string temp;
	int num, sz_temp, sumRawdata = 0; //sumRawdata : ���� �κ��� ���� or ������ ��
	for (int i = 0; i < words; i++) {
		cin >> temp;

		num = 0;
		sz_temp = temp.size() - 4;

		for (int j = 4; j < sz_temp; j++) {
			if (temp[j] == 'a' || temp[j] == 'n' || temp[j] == 't' || temp[j] == 'i' || temp[j] == 'c') continue;
			num |= (1 << (temp[j] - 'a'));
		}
		rawdata[i] = num; //rawdata���� antic�� ������ ����� �� ���ĺ����� ���´�.
		sumRawdata |= num;
	}

	if (numLearn < 0) {
		ans = 0;
		return;
	}

	for (int i = 0; i < 26; i++) {
		if ((sumRawdata >> i) & 1) {
			rawdataNum.push_back(i);
		}
	}

	if (numLearn >= rawdataNum.size()) ans = words; //�����ľ� �ϴ� ���ڰ� �ܾ� �ȿ� �ִ� ���ں��� ����.
}

void DFS(int rawdata_idx, int depth, int& tempNum) { //depth : ���ݱ��� ��� ������ ����
	if (depth != numLearn) { 
		int upperBound = rawdataNum.size() - (numLearn - depth); //����� �Ǵ� ���ں��� ���� ���ڰ� �������� ��� ����
		for (int i = rawdata_idx; i <= upperBound; i++) {
			tempNum |= (1 << (rawdataNum[i]));
			DFS(i + 1, depth + 1, tempNum);
			tempNum &= ~(1 << rawdataNum[i]);
		}
	}
	else {
		int ans_temp = 0;
		for (int k = 0; k < words; k++) {
			for (int i = 0; i < 26; i++) {
				if ((rawdata[k] >> i) & 1) {
					if ((tempNum >> i) & 1) continue;
					else {
						ans_temp--;
						break;
					}
				}
			}
			ans_temp++;
		}

		ans = max(ans, ans_temp);
	}
}

void operate() {
	if (ans != 777) {
		cout << ans << endl;
		return;
	}

	ans = 0;
	int tempNum = 0;
	//���λ� anta ���̻� tica���� antic�� ������ ����ģ��
	tempNum |= (1 << ('a' - 'a'));
	tempNum |= (1 << ('n' - 'a'));
	tempNum |= (1 << ('t' - 'a'));
	tempNum |= (1 << ('i' - 'a'));
	tempNum |= (1 << ('c' - 'a'));

	DFS(0, 0, tempNum);
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	initialize();
	operate();

	return 0;
}

/*
3 8
antacbetica
antachemtica
antatica
ans : 2

1 5
antatica

ans : 1

3 7
antawxtica
antaytica
antaztica
ans : 2
*/