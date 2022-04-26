#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class AcmCraft {
private:
	vector<int>* graph; //�� �ǹ� �� ���� ����� �� �ǹ��� INDEX
	int* duration, *in_order, *acc; //duration : �� �ǹ��� ���� �� �ʿ��� �ð�, in_order : �������, acc : �ش� �ǹ��� ���� ������ �� �ִ� �ð�
	int cases, bldgs, order, target;

public:
	void initialize() {
		cin >> cases; cin.get();
	}

	void get_cases() {
		cin >> bldgs >> order; cin.get();

		//RAWDATA �迭�� �޸� �Ҵ� �� �ʱ�ȭ
		graph = new vector<int>[bldgs + 1]; 
		duration = new int[bldgs + 1];
		acc = new int[bldgs + 1];
		memset(acc, 0, sizeof(int)*(bldgs + 1)); 
		in_order = new int[bldgs + 1];
		memset(in_order, 0, sizeof(int)*(bldgs + 1));

		//�� �ǹ��� ���� �� �ʿ��� �ð��� �޴´�
		for (int j = 1; j <= bldgs; j++) {
			cin >> duration[j]; cin.get(); 
		}

		int first, second;
		for (int j = 0; j < order; j++) {
			cin >> first >> second; cin.get();
			in_order[second]++; //�ǹ��� ���� ������ ����� �� �ǹ��� ���� �����Ѵ�
			graph[first].push_back(second); //�ǹ��� ���� ������ ����� �� �ǹ��� INDEX�� �����Ѵ�
		}

		cin >> target; cin.get();
	}

	void free_cases() { //���� TEST CASE�� ���� �޸� ����
		delete[] graph; 
		delete[] in_order;
		delete[] duration;
		delete[] acc;
	}

	void operate() {
		for (int i = 0; i < cases; i++) {
			get_cases();

			queue<int> next; //���� ���� �� �ִ� �ǹ��� �����ϴ� ť
			for (int j = 1; j <= bldgs; j++) { //���� ó���� ���� ����� �� �ǹ��� ���� �ǹ����� ã�´�.
				if (in_order[j] == 0) next.push(j);
			}

			int next_house, mov, temp;
			while (!next.empty()) {
				temp = next.front(); //TEMP == ��
				next.pop();

				mov = 0;
				while (mov != graph[temp].size()) {
					next_house = graph[temp][mov]; //���� ���� �ǹ��� ���� �ִ� �ǹ�
					acc[next_house] = max(acc[next_house], duration[temp] + acc[temp]); //�� �ǹ��� ���� ���� �ð��� ������Ʈ�����ش�.

					if (--in_order[next_house] == 0) { //���� �� �ǹ��� ���� �� �ִ°�?
						if (next_house == target) goto print;
						next.push(next_house);
					}
					mov++;
				}
			}
		print:;
			acc[target] += duration[target]; //TARGET ��ü �Ǽ� �ҿ� �ð� + ���� �ǹ� �Ǽ� �ҿ� �ð�
			cout << acc[target] << endl;
			free_cases();
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	AcmCraft op;
	op.initialize();
	op.operate();
	return 0;
}