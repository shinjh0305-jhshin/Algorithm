#include <iostream>
#include <cmath>
#include <algorithm>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class turret {
private:
	int x1, x2, y1, y2, cases;
	double r1, r2;
	double thr = 1e-5;


public:
	void initialize() {
		cin >> cases; cin.get();
	}

	void operate() {
		double dist; //�߽� ������ �Ÿ�, d�� ǥ��
		for (int i = 0; i < cases; i++) {
			cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2; cin.get();
			dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			
			if (dist > r1 + r2) //���� �ۿ� �����鼭 ������ ���� �� �� (d > r1 + r2)
				cout << 0 << endl;
			else if (abs(dist - (r1 + r2)) < thr) //�����ϴ� �� �� (d == r1 + r2)
				cout << 1 << endl;
			else if (dist < r1 + r2) { // d < r1 + r2
				if (dist < thr) { //d==0
					if (r1 == r2) //������ �� ��
						cout << -1 << endl;
					else if (r1 != r2) // ���ɿ�
						cout << 0 << endl;
				}
				else if (abs(dist - abs(r1 - r2)) < thr) //������
					cout << 1 << endl;
				else if(dist+min(r1, r2)<max(r1, r2)) //�� ���� �ٸ� ���� �����ϸ鼭 ������ ����
					cout << 0 << endl;
				else
					cout << 2 << endl;
			}
			else {
				cout << "Program error" << endl;
				cout << "d : " << dist << "  r1 + r2 : " << r1 + r2 << endl;
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	turret op;
	op.initialize();
	op.operate();
	return 0;
}