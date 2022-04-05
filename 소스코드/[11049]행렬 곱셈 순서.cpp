/*���� ��������*/
//� ������� ������ �ߴ��� ��ȣ�� �־ �� �ϳ��� ǥ���ϸ� ���?
//�ʿ� : ��ȣ �Ǻ� �˰��� -> �ڷᱸ������ ���� �������...??

#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;
#pragma warning (disable:4996)

struct mtx_sz {
	int row;
	int col;
};

class mtx_mult {
private:
	int mtx_cnt; /*matrix ����*/
	mtx_sz* size_info; /*matrix�� ������ ����*/
	unsigned int** rawdata; /*��� ���� Ƚ�� ����*/
	int i, j; /*iterating variable*/
public:
	mtx_mult() :mtx_cnt(0), rawdata(NULL), i(0), j(0) {};
	void initialize() {
		scanf("%d", &mtx_cnt); getchar();
		size_info = new mtx_sz[mtx_cnt + 1];

		for (i = 1; i <= mtx_cnt; i++) {
			scanf("%d %d", &size_info[i].row, &size_info[i].col); getchar();
		}
	}

	void get_opt() {
		int back_mov, front_mov;
		rawdata = new unsigned int*[mtx_cnt + 1];

		for (i = 1; i <= mtx_cnt; i++) {
			rawdata[i] = new unsigned int[mtx_cnt + 1];
		}

		for (i = 1; i <= mtx_cnt; i++) { /*�ڱ��ڽ��� ���� ���� ���� Ƚ�� == 0*/
			rawdata[i][i] = 0;
		}

		//Version 1
		/*AB, BC, CD ...�ϰ�(case 1) ABC, BCD, CDE ...�ϰ�(case 2) ABCD BCDE CDEF ...�ϴ½�(case 3)���� ����*/
		//for (i = 2; i <= mtx_cnt; i++) { /*case�� �ŵ�ɼ��� AB, ABC, ABCD �� ù ������ �� matrix �� �ڷΰ���*/
		//	back_mov = i;
		//	for (front_mov = 1; back_mov <= mtx_cnt; front_mov++, back_mov++) { /*case x ������ ���ư��� �ݺ���*/
		//		rawdata[front_mov][back_mov] = INT_MAX; /*initialize*/

		//		for (j = front_mov; j < back_mov; j++) { /*case x�� Ư�� ���Ұ� ���� ���� ����� �� ���� Ȯ�� (j : ������)*/
		//			rawdata[front_mov][back_mov] = min(rawdata[front_mov][back_mov], rawdata[front_mov][j] + rawdata[j + 1][back_mov]
		//				+ size_info[front_mov].row*size_info[j].col*size_info[back_mov].col);
		//		}
		//	}
		//}

		//Version 2 -> lecture version
		/*�� �� for loop�� �Ÿ��� �ɰ��� �ִ� �� �̿ܿ� �ٸ� �� ����.*/
		for (i = 1; i <= mtx_cnt - 1; i++) { // i : matrix �� �Ÿ�
			for (front_mov = 1; front_mov <= mtx_cnt - i; front_mov++) {
				back_mov = front_mov + i;

				rawdata[front_mov][back_mov] = INT_MAX; /*initialize*/

				for (j = front_mov; j < back_mov; j++) { /*case x�� Ư�� ���Ұ� ���� ���� ����� �� ���� Ȯ�� (j : ������)*/
					rawdata[front_mov][back_mov] = min(rawdata[front_mov][back_mov], rawdata[front_mov][j] + rawdata[j + 1][back_mov]
						+ size_info[front_mov].row*size_info[j].col*size_info[back_mov].col);
				}
			}
		}
	}
	
	void print_result() {
		printf("%d\n", rawdata[1][mtx_cnt]);
	}
};

int main() {
	mtx_mult op;
	op.initialize();
	op.get_opt();
	op.print_result();
	return 0;
}