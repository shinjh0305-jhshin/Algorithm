#include <stdio.h>
#pragma warning (disable:4996)

struct node {
	int num; //RAWDATA
	int sum; //���� ��
	//int from; /*for backtracking*/
};

class operate {
private:
	int len;
	int max_end; /*�ִ� ���� ����*/
	int max_sum; /*�ִ� ��*/
	node* arr;
public:
	operate() : len(0), arr(NULL), max_end(0), max_sum(0){};
	~operate() {
		delete[] arr;
	}

	void get_num() {
		scanf("%d", &len); getchar();
		arr = new node[len];
	}

	void get_max_sum() {
		int in_num, sum_temp;
		for (int i = 0; i < len; i++) {

			scanf("%d", &in_num);
			arr[i].num = in_num;
			if (i == 0) { //INITIALIZE
				//arr[0].from = 0;
				arr[0].sum = max_sum = in_num;
				continue;
			}

			sum_temp = arr[i - 1].sum + in_num; //���� ���� �տ� �� ���� ���Ѵ�.
			if (in_num >= sum_temp) { //�� ������ �ٽ� ������ �����ϴ� ���� ���� ���� �����ϴ� �ͺ��� �����ϴ�.
				//arr[i].from = i; //������ �ٽ� ����
				arr[i].sum = in_num;
			}
			else { //���� ���� �����ϴ� ���� �� �����ϴ�.
				//arr[i].from = arr[i - 1].from;
				arr[i].sum = sum_temp;
			}

			if (arr[i].sum > max_sum) { //���� ���� �ִ��� ��ŵ� ���
				//max_end = i;
				max_sum = arr[i].sum;
			}
		}
	}

	void print_result() {
		printf("%d\n", max_sum);
		
		///*backtracking ���*/
		//int start = arr[max_end].from;
		//for (int i = start; arr[i].from == start; i++) {
		//	printf("%d ", arr[i].num);
		//}
		//printf("\n");
	}
};

int main() {
	operate op;
	op.get_num();
	op.get_max_sum();
	op.print_result();

	return 0;
}