#include <iostream>
#include <stack>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

#define DURATION 60 //�ùķ��̼� �ð��� 100��
#define available true
#define busy false

// A : ���� ������, B : ���� ������
// C : ���� ������X��� �����, D : ���� ������X��� �����, E : ��� Ȱ�ַ�
// F : ���� ������X�Ϻ� �����, G : ���� ������X�Ϻ� �����, H : �Ϻ� Ȱ�ַ�
enum checkpoint{A, B, C, D, E, F, G, H};


//100�ʰ��� Ÿ�����̺� ����
// �ش� �ð��� �ش� checkpoint�� �����ϰ� �ִ� �װ����� index�� �����Ѵ�.
// 0��, 1�� ���� taxiway �迭�� ȣȯ�� ���� ���� dummy row. ������� �ʴ´�.
short timetable[8][DURATION]; 

//������ Ÿ�����̺�. ���Ϸ� ��� �����̱⿡, Ʃ�� ������ �ڷᱸ�� �ʿ�.
//row1 : A , row2 : B, tuple <first : ���� �ö󰡴� ����� ��� gate ��ȣ, second : �Ʒ��� �������� ����� ��� gate ��ȣ>
pair<short, short> taxiway[2][DURATION]; 

struct airplane {
	bool status; //available : ������� �ʴ� �����, busy : �������� �����
	char code[5]; //����� ���
	int gate; //�� �� ����Ʈ���� �Գ�
	int departure; //�� �� ��� �����ΰ�
	int case_type; //� ���̽��� �̿��ϴ°�
	int current_location; //�� ���������� ��ġ(0 : ����Ʈ, 1 : ������, 2 : �����, 3 : �������, 4 : Ȱ�ַ�, 5 : �̷�)
	short schedule[6]; //����Ʈ ���-������-�����-�������(A�� ��� ����ο� ����)-Ȱ�ַ�-�̷�
};

char offset[5][6] = { //����Ⱑ �ٴ� �� ���İ��� ����
	{0, 0, 0, 0, 0, 0},
	{0, 'A', 'C', 'C', 'E', 0},
	{0, 'A', 'F', 'F', 'H' ,0},
	{0, 'B', 'D', 'C', 'E', 0},
	{0, 'B', 'G', 'F', 'H', 0}
};

int latest; //���� ���� �� ����� �߿��� ���� �ʰ� �̷��ϴ� ������� �̷� ����
airplane plane[100]; //����Ʈ 10�� + ������ 3�� * ������ 2��, index 1���� ����
airplane landing_plane[2]; //�����ϴ� �����
int plane_index = 0; //plane index

bool gate[10]; //gate�� ���� ��� ���θ� Ȯ��

void initialize();
void make_route(int index);
void prNewPlane(int index);
void makeNewPlane();

int main() {
	//gate ���� �ܰ迡�� ��� Ȯ��
	srand((unsigned int)time(NULL));
	initialize();

	
	for (int t = 0; t < DURATION; t++) {
		//������ �ִ� ������� ���� ������Ʈ�� �����Ѵ�.
		cout << "���� �ð� : " << t << endl;
		for (int i = 1; i <= 10; i++) {
			if (plane[i].status == busy) { //�������� ������� ���
				if (plane[i].schedule[plane[i].current_location] == t) {
					if (plane[i].current_location == 0) { //gate���� ���� ������ �ִ� ���̱⿡, gate flag�� �ֽ�ȭ�Ѵ�.
						gate[plane[i].gate] = available;
					}

					if (plane[i].current_location == 0) 
						cout << plane[i].code << "��(��) ����Ʈ " << plane[i].gate << "���� �����ϰ� �ֽ��ϴ�." << endl;
					else if (plane[i].current_location == 4) {
						cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
						cout << plane[i].code << "��(��) �̷��߽��ϴ�." << endl;
						cout << "�̷������ð� : " << plane[i].departure << "   �����̷��ð� : " << plane[i].schedule[5] << endl;
						cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
					}
					else
						cout << plane[i].code << "��(��) " << offset[plane[i].case_type][plane[i].current_location] << "���� " << offset[plane[i].case_type][plane[i].current_location + 1] << "�� �̵����Դϴ�." << endl;

					plane[i].current_location++; //����Ⱑ ���� ���� ���� �ִ� ��. �� �������� ��ȭ �׸���.
					if (plane[i].current_location == 2 && (plane[i].case_type == 1 || plane[i].case_type == 2)) plane[i].current_location++; //���� ������(index 2�� 3)�� �ߺ����� �ذ��Ѵ�.

					if (plane[i].current_location == 5) {
						//����Ⱑ �̷��߱⿡ �ٽ� pool�� ����������.
						plane[i].status = available;
						available_plane.push(i);
					}
				}
			}
		}

		//���ο� ����⸦ �����Ѵ�.
		//latest�κ��� 2�� �̻� 5�� ���Ϸ� ������ ������ ����ϴ� ����⸦ �����.
		//������ ���� �������� ������ ��ҿ� �����.
		if (available_plane.size()>=3 && t%2) {
			int j;
			for (j = 0; j < 10; j++) {
				if (gate[j] == available) {
					break;
				}
			}
			if (j != 10) makeNewPlane();
			
		}
		cout << endl;
	}
}

void initialize() {
	for (int i = 0; i < 10; i++) { //��� ����Ʈ�� �ʱ⿡�� ��� ������ ���·� �����.
		gate[i] = available;
	}
	for (int i = 1; i <= 10; i++) { //��� ����Ⱑ �ʱ⿡�� ��� ������ ���·� �����.
		available_plane.push(i);
		plane[i].status = available;
		for (int j = 0; j < 6; j++) { //��� ������� ��ε� �ʱ�ȭ�Ѵ�.
			plane[i].schedule[j] = -1;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < DURATION; j++) {
			timetable[i][j] = 0; //timetable�� �ʱ�ȭ�Ѵ�.
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < DURATION; j++) { //������ timetable�� �ʱ�ȭ�Ѵ�.
			taxiway[i][j].first = taxiway[i][j].second = -1;
		}
	}

	int initial_planes = rand() % 5 + 1; //ó������ 1�� ~ 5���� ����⸦ �����.
	priority_queue<int> departure; //��� �ð� ������� �̾Ƴ��� ���� �켱���� ť�� �����.
	
	int temp;
	for (int i = 0; i < initial_planes; i++) { //ó������ 5�ʿ��� 10�� ���̿� ����ϴ� ����⸦ �����.
		temp = rand() % 6 + 5;
		departure.push(-temp);
		//for debugging : heap input checking
		cout << i << " : " << temp << endl;
	}
	 
	//for debugging : heap searching
	//while (!departure.empty()) {
	//	cout << -departure.top() << endl;
	//	departure.pop();
	//}

	for (int i = 0; i < initial_planes; i++) { //�ʱ� ����⿡ ���� ����Ʈ�� �����Ѵ�. �� �ܰ迡�� ��� Ȯ���� �Ͼ��.
		if (available_plane.empty()) break;
		temp = available_plane.front(); available_plane.pop();
		plane[temp].status = busy;
		plane[temp].departure = -departure.top(); //���� �ִ� �ʱ� �װ��� �� ���� �̸� �װ����� ��� �ð�
		departure.pop();

		plane[temp].code[0] = 'S';
		plane[temp].code[1] = 'G';
		plane[temp].code[2] = rand() % 10 + '0';
		plane[temp].code[3] = rand() % 10 + '0';
		plane[temp].code[4] = rand() % 10 + '0';

		make_route(temp);
		plane[temp].current_location = 0;

		prNewPlane(temp);
		
	}
	latest = plane[initial_planes].schedule[5];

}

void make_route(int index)  //index : plane �迭 �󿡼��� plane ��ȣ
{
	//���� ���, ���� �Ϻ�, ���� ���, ���� �Ϻθ� ��� �˻��Ѵ�.
	//��, ��Ʈ���� ������ ����(����Ʈ ��ߺ��� �̷����� 3�� �ҿ�) ��ΰ� �߻��ϸ� ������ �˻����� �ʴ´�.
	//���� �����̶��, ��� Ȱ�ַθ� �̿��ϴ� ���� ��ȣ�Ѵ�.
	//�����̰� �ִ��� ������ ����� ���� ��ǥ��.

	//�������� : �װ��� Ǫ�ù�, ������ ���� ���������� ���� �����̰� �߻����� �ʴ´�. ����Ʈ���� �ʰ� ����ϴ� ������� �ذ��Ѵ�.

	int departure = plane[index].departure;
	int time; //�� ��쿡�� ��������� ���� ����ؾ� �ϴ� �����뼱 �ð�
	int candid[5]; //�ĺ� ����Ʈ
	int test, i;

	deque<int> case1, case2, case3, case4; //�� �̵� ��ο� ���� case ����
	
	//1. ���� ��� �̵� ����
	for (i = 0; i <= 2; i++) { //�ĺ� ����Ʈ�� �����Ѵ�.
		if (gate[i] == busy) continue;
		candid[1] = i; break;
	}
	if (i == 3) goto second;

	time = departure - 4; 
	for (time = departure - 4; time < DURATION ; time++) {
		if (taxiway[A][time].first != -1) continue; //���� �ö󰡴� ����Ⱑ �ִ�.
		if (taxiway[A][time].second != -1) { //�Ʒ��� �������� ����Ⱑ �ִ�.
			test = taxiway[A][time].second;
			if (test < candid[1]) continue; //�Ʒ��� �������� ����Ⱑ �� ���� �ִ� ����Ʈ���� ����� ������̴�.
		}
		if (timetable[C][time + 2] != 0) continue; //����ο� �̹� ����Ⱑ �ִ�.
		break;
	}
	case1.push_back(time); //Ǫ�ù� �� ������ ���� ���� �ð��� �����Ѵ�.
	time++; //������ ���� �Ϸ� �ð����� �ٲ۴�.
	case1.push_back(time); //������ ���� �Ϸ� �ð��� �����Ѵ�. A�� �ִ� �ð�.
	time++; //����� ���� �Ϸ� �ð����� �ٲ۴�.
	case1.push_back(time); //����� ���� �Ϸ� �ð��� �����Ѵ�.
	time++;
	while (timetable[E][time] != 0) time++; //Ȱ�ַΰ� ��� �ð����� �ٲ۴�.
	case1.push_back(time); //Ȱ�ַ� ���� �Ϸ� �ð��� �����Ѵ�.
	time++;
	/*������ ���õ� �ڵ�*/
	case1.push_back(time); //�̷� �Ϸ� �ð��� �����Ѵ�. // ���� ����� �������� �� �κ� �ٲܲ�.

	if (time == departure) { //���� ���̽����� ������ ��ΰ� ������.
		if (candid[1] == 2) goto second; //�߰� ����Ʈ�� ���� �ٸ� ����⸦ ������ ��ų �� �ִ�.

		plane[index].case_type = 1;

		for (i = case1[0]; i <= case1[1]; i++) { //Ǫ�ù�, ������ ����
			taxiway[A][i].first = candid[1];
		}
		for (i = case1[2]; i < case1[3]; i++) { //�����ο��� ���
			timetable[C][i] = index;
		}
		for (i = case1[3]; i < case1[4]; i++) { //Ȱ��
			timetable[E][i] = index;
		}
		
		//������� �̵� �������� �����Ѵ�.
		plane[index].schedule[0] = case1[0];
		plane[index].schedule[1] = case1[1];
		plane[index].schedule[2] = case1[2];
		plane[index].schedule[3] = case1[2];
		plane[index].schedule[4] = case1[3];
		plane[index].schedule[5] = case1[4];


		gate[candid[1]] = busy; //����Ʈ ��� ������ ǥ��
		plane[index].gate = candid[1]; //����Ⱑ ����� ����Ʈ
		return;
	}

second:;
	//2. ���� �Ϻ� �̵� ����
	for (i = 4; i >= 2; i--) { //�ĺ� ����Ʈ�� �����Ѵ�.
		if (gate[i] == busy) continue;
		candid[2] = i; break;
	}
	if (i == 1) goto third;

	time = departure - 4;
	for (time = departure - 4; time < DURATION ; time++) {
		if (taxiway[A][time].second != -1) continue; //�Ʒ��� �������� ����Ⱑ �ִ�.
		if (taxiway[A][time].first != -1) { //���� �ö󰡴� ����Ⱑ �ִ�.
			test = taxiway[A][time].first;
			if (test > candid[2]) continue; //���� �ö󰡴� ����Ⱑ �� ���� �ִ� ����Ʈ���� ����� ������̴�.
		}
		if (timetable[F][time + 2] != 0) continue; //����ο� �̹� ����Ⱑ �ִ�.
		break;
	}
	case2.push_back(time); //Ǫ�ù� �� ������ ���� ���� �ð��� �����Ѵ�.
	time++; //������ ���� �Ϸ� �ð����� �ٲ۴�.
	case2.push_back(time); //������ ���� �Ϸ� �ð��� �����Ѵ�.
	time++; //����� ���� �Ϸ� �ð����� �ٲ۴�.
	case2.push_back(time); //����� ���� �Ϸ� �ð��� �����Ѵ�.
	time++;
	while (timetable[H][time] != 0) time++; //Ȱ�ַΰ� ��� �ð����� �ٲ۴�.
	case2.push_back(time); //Ȱ�ַ� ���� �Ϸ� �ð��� �����Ѵ�.
	time++;
	/*������ ���õ� �ڵ�*/
	case2.push_back(time); //�̷� �Ϸ� �ð��� �����Ѵ�. // ���� ����� �������� �� �κ� �ٲܲ�.

	if (time == departure) { //���� ���̽����� ������ ��ΰ� ������.
		if (candid[2] == 2) goto third; //�߰� ����Ʈ�� ���� �ٸ� ����⸦ ������ ��ų �� �ִ�.

		plane[index].case_type = 2;

		for (i = case2[0]; i <= case2[1]; i++) { //Ǫ�ù�, ������ ����
			taxiway[A][i].second = candid[2];
		}
		for (i = case2[2]; i < case2[3]; i++) { //�����ο��� ���
			timetable[F][i] = index;
		}
		for (i = case2[3]; i < case2[4]; i++) { //Ȱ��
			timetable[H][i] = index;
		}

		//������� �̵� �������� �����Ѵ�.
		plane[index].schedule[0] = case2[0];
		plane[index].schedule[1] = case2[1];
		plane[index].schedule[2] = case2[2];
		plane[index].schedule[3] = case2[2];
		plane[index].schedule[4] = case2[3];
		plane[index].schedule[5] = case2[4];

		gate[candid[2]] = busy; //����Ʈ ��� ������ ǥ��
		plane[index].gate = candid[2]; //����Ⱑ ����� ����Ʈ
		return;
	}

third:;
	//3. ������ ��� �̵� ����
	for (i = 5; i <= 7; i++) { //�ĺ� ����Ʈ�� �����Ѵ�.
		if (gate[i] == busy) continue;
		candid[3] = i; break;
	}
	if (i == 8) goto fourth;

	time = departure - 5;
	for (time = departure - 5; time < DURATION ; time++) {
		if (taxiway[B][time].first != -1) continue; //���� �ö󰡴� ����Ⱑ �ִ�.
		if (taxiway[B][time].second != -1) { //�Ʒ��� �������� ����Ⱑ �ִ�.
			test = taxiway[B][time].second;
			if (test < candid[3]) continue; //�Ʒ��� �������� ����Ⱑ �� ���� �ִ� ����Ʈ���� ����� ������̴�.
		}
		if (timetable[D][time + 2] != 0) continue; //����ο� �̹� ����Ⱑ �ִ�.
		break;
	}
	case3.push_back(time); //Ǫ�ù� �� ������ ���� ���� �ð��� �����Ѵ�.
	time++; //������ ���� �Ϸ� �ð����� �ٲ۴�.
	case3.push_back(time); //������ ���� �Ϸ� �ð��� �����Ѵ�.
	time++; //�����(D) ���� �Ϸ� �ð����� �ٲ۴�.
	case3.push_back(time); //�����(D) ���� �Ϸ� �ð��� �����Ѵ�.
	time++; 
	while (timetable[C][time] != 0) time++; //�����(C)�� ��� �ð����� �ٲ۴�.
	case3.push_back(time); //�����(C) ���� �Ϸ� �ð��� �����Ѵ�.
	time++; 
	while (timetable[E][time] != 0) time++; //Ȱ�ַΰ� ��� �ð����� �ٲ۴�.
	case3.push_back(time); //Ȱ�ַ� ���� �Ϸ� �ð��� �����Ѵ�.
	time++;
	/*������ ���õ� �ڵ�*/
	case3.push_back(time); //�̷� �ð��� �����Ѵ�. // ���� ����� �������� �� �κ� �ٲܲ�.

	if (time == departure) { //���� ���̽����� ������ ��ΰ� ������.
		if (candid[3] == 7) goto fourth; //�߰� ����Ʈ�� ���� �ٸ� ����⸦ ������ ��ų �� �ִ�.

		plane[index].case_type = 3;

		for (i = case3[0]; i <= case3[1]; i++) { //Ǫ�ù�, ������ ����
			taxiway[B][i].first = candid[3];
		}
		for (i = case3[2]; i < case3[3]; i++) { //������(D)���� ���
			timetable[D][i] = index;
		}
		for (i = case3[3]; i < case3[4]; i++) { //������(C)���� ���
			timetable[C][i] = index;
		}
		for (i = case3[4]; i < case3[5]; i++) { //Ȱ��
			timetable[E][i] = index;
		}

		//������� �̵� �������� �����Ѵ�.
		plane[index].schedule[0] = case3[0];
		plane[index].schedule[1] = case3[1];
		plane[index].schedule[2] = case3[2];
		plane[index].schedule[3] = case3[3];
		plane[index].schedule[4] = case3[4];
		plane[index].schedule[5] = case3[5];

		gate[candid[3]] = busy; //����Ʈ ��� ������ ǥ��
		plane[index].gate = candid[3]; //����Ⱑ ����� ����Ʈ
		return;
	}

fourth:;
	//4. ���� �Ϻ� �̵� ����
	for (i = 9; i >= 7; i--) { //�ĺ� ����Ʈ�� �����Ѵ�.
		if (gate[i] == busy) continue;
		candid[4] = i; break;
	}
	if (i == 6) goto finale;

	time = departure - 5;
	for (time = departure - 5; time < DURATION ; time++) {
		if (taxiway[B][time].second != -1) continue; //�Ʒ��� �������� ����Ⱑ �ִ�.
		if (taxiway[B][time].first != -1) { //���� �ö󰡴� ����Ⱑ �ִ�.
			test = taxiway[B][time].first;
			if (test > candid[4]) continue; //���� �ö󰡴� ����Ⱑ �� ���� �ִ� ����Ʈ���� ����� ������̴�.
		}
		if (timetable[G][time + 2] != 0) continue; //����ο� �̹� ����Ⱑ �ִ�.
		break;
	}
	case4.push_back(time); //Ǫ�ù� �� ������ ���� ���� �ð��� �����Ѵ�.
	time++; //������ ���� �Ϸ� �ð����� �ٲ۴�.
	case4.push_back(time); //������ ���� �Ϸ� �ð��� �����Ѵ�.
	time++; //�����(G) ���� �Ϸ� �ð����� �ٲ۴�.
	case4.push_back(time); //�����(G) ���� �Ϸ� �ð��� �����Ѵ�.
	time++; 
	while (timetable[F][time] != 0) time++; //�����(F)�� ��� �ð����� �ٲ۴�.
	case4.push_back(time); //�����(F) ���� �Ϸ� �ð��� �����Ѵ�.
	time++; 
	while (timetable[H][time] != 0) time++; //Ȱ�ַΰ� ��� �ð����� �ٲ۴�.
	case4.push_back(time); //Ȱ�ַ� ���� �Ϸ� �ð��� �����Ѵ�.
	time++;
	/*������ ���õ� �ڵ�*/
	case4.push_back(time); //�̷� �ð��� �����Ѵ�. // ���� ����� �������� �� �κ� �ٲܲ�.

	if (time == departure) { //���� ���̽����� ������ ��ΰ� ������.
		if (candid[4] == 7) goto finale; //�߰� ����Ʈ�� ���� �ٸ� ����⸦ ������ ��ų �� �ִ�.

		plane[index].case_type = 4;

		for (i = case4[0]; i <= case4[1]; i++) { //Ǫ�ù�, ������ ����
			taxiway[B][i].second = candid[4];
		}
		for (i = case4[2]; i < case4[3]; i++) { //������(G)���� ���
			timetable[G][i] = index;
		}
		for (i = case4[3]; i < case4[4]; i++) { //������(F)���� ���
			timetable[F][i] = index;
		}
		for (i = case4[4]; i < case4[5]; i++) { //Ȱ��
			timetable[H][i] = index;
		}
		
		//������� �̵� �������� �����Ѵ�.
		plane[index].schedule[0] = case4[0];
		plane[index].schedule[1] = case4[1];
		plane[index].schedule[2] = case4[2];
		plane[index].schedule[3] = case4[3];
		plane[index].schedule[4] = case4[4];
		plane[index].schedule[5] = case4[5];

		gate[candid[4]] = busy; //����Ʈ ��� ������ ǥ��
		plane[index].gate = candid[4]; //����Ⱑ ����� ����Ʈ
		return;
	}

finale:; 
	//�� ���� ���� ��Ʈ�� ����, �ݵ�� �����̰� �߻��ǰų�, �߰� ����Ʈ�� ������ ������̴�.
	//�� ���� case1 ~ 4 �߿��� ���� �ҿ�ð��� ª�� ��θ� �����ؾ� �Ѵ�.

	int min; //�� ��° ���̽��� ������ ��Ʈ�� �ִ��� �����Ѵ�.
	int min_back = 999; //������ ��Ʈ�� ���� �̷��� �� �ִ� �ð��� �����Ѵ�.

	if (!case1.empty() && case1.back() < min_back) {
		min = 1;
		min_back = case1.back();
	}
	if (!case2.empty() && case2.back() < min_back) {
		min = 2;
		min_back = case2.back();
	} 
	if (!case3.empty() && case3.back() < min_back) {
		min = 3;
		min_back = case3.back();
	}
	if (!case4.empty() && case4.back() < min_back) {
		min = 4;
		min_back = case4.back();
	}

	if (min == 1) {
		for (i = case1[0]; i <= case1[1]; i++) { //Ǫ�ù�, ������ ����
			taxiway[A][i].first = candid[1];
		}
		for (i = case1[2]; i < case1[3]; i++) { //�����ο��� ���
			timetable[C][i] = index;
		}
		for (i = case1[3]; i < case1[4]; i++) { //Ȱ��
			timetable[E][i] = index;
		}
		
		plane[index].case_type = 1;

		plane[index].schedule[0] = case1[0];
		plane[index].schedule[1] = case1[1];
		plane[index].schedule[2] = case1[2];
		plane[index].schedule[3] = case1[2];
		plane[index].schedule[4] = case1[3];
		plane[index].schedule[5] = case1[4];

		gate[candid[1]] = busy; //����Ʈ ��� ������ ǥ��
		plane[index].gate = candid[1]; //����Ⱑ ����� ����Ʈ
	}

	else if (min == 2) {
		for (i = case2[0]; i <= case2[1]; i++) { //Ǫ�ù�, ������ ����
			taxiway[A][i].second = candid[2];
		}
		for (i = case2[2]; i < case2[3]; i++) { //�����ο��� ���
			timetable[F][i] = index;
		}
		for (i = case2[3]; i < case2[4]; i++) { //Ȱ��
			timetable[H][i] = index;
		}

		plane[index].case_type = 2;

		plane[index].schedule[0] = case2[0];
		plane[index].schedule[1] = case2[1];
		plane[index].schedule[2] = case2[2];
		plane[index].schedule[3] = case2[2];
		plane[index].schedule[4] = case2[3];
		plane[index].schedule[5] = case2[4];

		gate[candid[2]] = busy; //����Ʈ ��� ������ ǥ��
		plane[index].gate = candid[2]; //����Ⱑ ����� ����Ʈ
	}

	else if (min == 3) {
		for (i = case3[0]; i <= case3[1]; i++) { //Ǫ�ù�, ������ ����
			taxiway[B][i].first = candid[3];
		}
		for (i = case3[2]; i < case3[3]; i++) { //������(D)���� ���
			timetable[D][i] = index;
		}
		for (i = case3[3]; i < case3[4]; i++) { //������(C)���� ���
			timetable[C][i] = index;
		}
		for (i = case3[4]; i < case3[5]; i++) { //Ȱ��
			timetable[E][i] = index;
		}

		plane[index].case_type = 3;

		//������� �̵� �������� �����Ѵ�.
		plane[index].schedule[0] = case3[0];
		plane[index].schedule[1] = case3[1];
		plane[index].schedule[2] = case3[2];
		plane[index].schedule[3] = case3[3];
		plane[index].schedule[4] = case3[4];
		plane[index].schedule[5] = case3[5];

		gate[candid[3]] = busy; //����Ʈ ��� ������ ǥ��
		plane[index].gate = candid[3]; //����Ⱑ ����� ����Ʈ
	}

	else if (min == 4) {
		for (i = case4[0]; i <= case4[1]; i++) { //Ǫ�ù�, ������ ����
			taxiway[B][i].second = candid[4];
		}
		for (i = case4[2]; i < case4[3]; i++) { //������(G)���� ���
			timetable[G][i] = index;
		}
		for (i = case4[3]; i < case4[4]; i++) { //������(F)���� ���
			timetable[F][i] = index;
		}
		for (i = case4[4]; i < case4[5]; i++) { //Ȱ��
			timetable[H][i] = index;
		}

		plane[index].case_type = 4;

		//������� �̵� �������� �����Ѵ�.
		plane[index].schedule[0] = case4[0];
		plane[index].schedule[1] = case4[1];
		plane[index].schedule[2] = case4[2];
		plane[index].schedule[3] = case4[3];
		plane[index].schedule[4] = case4[4];
		plane[index].schedule[5] = case4[5];
		gate[candid[4]] = busy; //����Ʈ ��� ������ ǥ��
		plane[index].gate = candid[4]; //����Ⱑ ����� ����Ʈ
	}
}

void prNewPlane(int index) {
	cout << "-----------------------------------" << endl;
	cout << "���ο� ����Ⱑ �����Ǿ����ϴ�." << endl;
	cout << "��� : " << plane[index].code << endl;
	cout << "����Ʈ : " << plane[index].gate << endl;
	cout << "-----------------------------------" << endl;
}

void makeNewPlane() {
	//���ο� ����⸦ �����Ѵ�.
	//latest�κ��� 2�� �̻� 5�� ���Ϸ� ������ ������ ����ϴ� ����⸦ �����.
	//������ ���� �������� ������ ��ҿ� �����.
	int newplane; //���ο� ����Ⱑ ����� �ð�

	newplane = latest + rand() % 4 + 2;
	latest = newplane;
	
	int temp = available_plane.front(); available_plane.pop();
	plane[temp].status = busy;
	plane[temp].departure = newplane;

	plane[temp].code[0] = 'S';
	plane[temp].code[1] = 'G';
	plane[temp].code[2] = rand() % 10 + '0';
	plane[temp].code[3] = rand() % 10 + '0';
	plane[temp].code[4] = rand() % 10 + '0';

	make_route(temp);

	plane[temp].current_location = 0;

	prNewPlane(temp);
}