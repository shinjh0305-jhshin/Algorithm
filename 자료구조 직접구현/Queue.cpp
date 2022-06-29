#include <iostream>
using namespace std;

struct info {
	char name[60];
	int score;
};
struct node {
	info data;
	node* nextnode;
};

node* root = nullptr;
node* curnode = nullptr;
int sz_queue = 0;

void pop() {
	if (sz_queue == 0) {
		cout << "���� �� �����Ͱ� �����ϴ�." << endl;
		return;
	}

	node* temp = root;
	root = root->nextnode;
	delete temp;

	cout << root->data.name << "�л�(���� : " << root->data.score << "��)�� �����մϴ�." << endl;
	sz_queue--;
}

void push() {
	curnode->nextnode = new node;
	curnode = curnode->nextnode;
	sz_queue++;

	cout << "�̸��� �Է��ϼ���   >>  ";
	cin.getline(curnode->data.name, 60, '\n');  //getline�� ���ۿ� ���๮�� �� ���ܵ�!

	cout << "������ �Է��ϼ���   >>  ";
	cin >> curnode->data.score; cin.get();

	cout << "�Էµ� �̸��� " << curnode->data.name << "�̸�, ������ " << curnode->data.score << "�� �Դϴ�." << endl;
}

void printScore() {
	cout << endl << endl;
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "                    ���ھ��                     " << endl;

	node* mov = root->nextnode;
	for (int i = 0; i < sz_queue; i++) {
		cout << mov->data.name << "  |  " << mov->data.score << "��" << endl;
		mov = mov->nextnode;
	}
	cout << "//////////////////////////////////////////////////" << endl << endl;
}

int main() {
	root = new node;
	curnode = root;

	int op;

	while (1) {
		cout << "� �۾��� �����ұ��? (1 : Ǫ��, 2 : ��)   >>  ";
		cin >> op; cin.get();

		if (op == 1) {
			push();
			printScore();
		}
		if (op == 2) {
			pop();
			printScore();
		}
	}

	
}