#include <iostream>
#include <cmath>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class b664 {
private:
	short x1, x2, y1, y2;
	int cases;

public:
	void initialize() {
		cin >> cases; cin.get();
	}

	void operate() {
		short cx, cy, circles, result, temp;
		double r;
		
		for (int i = 0; i < cases; i++) {
			result = 0;

			cin >> x1 >> y1 >> x2 >> y2; cin.get();
			cin >> circles; cin.get();

			for (int j = 0; j < circles; j++) {
				temp = 0;

				cin >> cx >> cy >> r; cin.get();

				//�����~���� �߽��� ���������� ���� ��쿡�� �����Ѵ�.
				if (sqrt(pow(cx - x1, 2) + pow(cy - y1, 2)) < r) temp++;
				//������~���� �߽��� ���������� ���� ��쿡�� �����Ѵ�.
				if (sqrt(pow(cx - x2, 2) + pow(cy - y2, 2)) < r) temp++;

				//ū �� �ȿ� ��/�������� ��� �����ϴ� ���, �� ���� �������� ���� �ƴϴ�.
				if (temp == 1) result++;
			}

			cout << result << endl;
		}

	}
};

int main() {
	ios::sync_with_stdio(false);
	b664 op;
	op.initialize();
	op.operate();
	return 0;
}