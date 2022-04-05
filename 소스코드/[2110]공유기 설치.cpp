#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"
#pragma warning (disable:4996)
using namespace std;

class router {
private:
	int houses, routers;
	vector<int> location;

public:
	void initialize() {
		cin >> houses >> routers;

		int num_in;

		for (int i = 0; i < houses; i++) {
			cin >> num_in;
			location.push_back(num_in);
		}

		sort(location.begin(), location.end());
	}

	void operate() {
		//front, mid : �̰��ϴ� �Ÿ� �����,  mid : �Ÿ� �����
		int front = 1, back = location[houses - 1] - location[0], mid;

		// installed : ��ġ�� �������� ����, prev_installed : ������ �����Ⱑ ��ġ�� ���� index
		// result : �ִ� �̰ݰŸ�
		int installed, prev_installed, result = 0;

		while (front <= back) {
			mid = (front + back) / 2;
			installed = 1; prev_installed = 0;
			for (int mov = 1; mov < houses; mov++) {
				if (location[mov] - location[prev_installed] >= mid) {
					installed++;
					prev_installed = mov;
				}
			}

			if (installed >= routers) {
				result = max(result, mid);
				front = mid + 1;
			}
			else back = mid - 1;
		}

		cout << result << endl;
	}
};

int main() {
	ios::sync_with_stdio(false);
	router op;
	op.initialize();
	op.operate();
	return 0;
}
