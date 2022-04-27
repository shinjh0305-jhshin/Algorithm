#include <cstdio>
#include <cmath>
#include <stack>
#include <limits.h>
using namespace std;

#pragma warning (disable:4996)


/*greedy approach*/
//class operate {
//private:
//	double num;
//	int result;
//	stack<double> stack;
//
//public:
//	operate() : num(0), result(0) {};
//
//	void get_num() {
//		scanf("%lf", &num); getchar();
//	}
//
//	void get_sqrnum() {
//		double root = floor(sqrt(num));
//		stack.push(root);
//		num = num - pow(root, 2);
//		result++;
//
//		if (num >= 1) {
//			get_sqrnum();
//		}
//	}
//
//	void print_result() {
//		printf("%d\n", result);
//		while (!stack.empty()) {
//			printf("%2.0lf^2 + ", stack.top());
//			stack.pop();
//		}
//		printf("\n");
//	}
//};
//
//int main() {
//	operate op;
//	op.get_num();
//	op.get_sqrnum();
//	op.print_result();
//	return 0;
//}

/*Dynamic Programming --> ���⺻*/
class operate {
private:
	int num;
	int* rawdata;
public:
	operate() :num(0), rawdata(NULL) {};
	~operate() {
		delete[] rawdata;
	}

	void get_num() {
		scanf("%d", &num); getchar();
		rawdata = new int[num + 1];
	}

	void get_sqrnum() {
		/*****************************************************
		* ���� ��� 101�̶�� ���� ������ 
		* 1. �ش� ���� ���������� ���� �Ǵ��ϰ�,
		* 2. �������� �ƴϸ�, 1^2, 2^2, ... , 10^2���� ���鼭
		* 3. 101 - (2���� ���� ��)�� ��� ���������� �Ǵ��Ѵ�.
		* ***************************************************/
		if (floor(sqrt(num)) == sqrt(num)) { //��ǥ ���ڰ� �������̸� 1�� �����Ѵ�.
			rawdata[num] = 1;
			return;
		}

		int num_saved; /*3.�� ���� �� ����*/
		for (int current = 1; current <= num; current++) { //1���� ��ǥ ���ڱ��� ���鼭 ����Ѵ�.
			if (floor(sqrt(current)) == sqrt(current)) { //current�� �������� 1�� �����Ѵ�.
				rawdata[current] = 1;
				continue;
			}

			rawdata[current] = INT_MAX;

			for (int i = 1; i * i < current; i++) { //current���� ���� �������� ���� ����Ѵ�.
				num_saved = current - i * i; //3.�� �����Ѵ�.
				if (rawdata[num_saved] + 1 < rawdata[current]) { //�� ���� ��������� ���� ������ ������ ���.
					rawdata[current] = rawdata[num_saved] + 1;
				}
			}
		}
	}

	void print_result() {
		printf("%d\n", rawdata[num]);
	}
};

int main() {
	operate op;
	op.get_num();
	op.get_sqrnum();
	op.print_result();
	return 0;
}