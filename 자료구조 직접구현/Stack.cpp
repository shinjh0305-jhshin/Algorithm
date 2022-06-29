#include <iostream>
using namespace std;

struct info {
	char name[60];
	int score;
};

struct node {
	info data;
	node* nextnode;
	node* prevnode;
};

node* root = nullptr;
node* curNode = nullptr;
int sz_stack = 0;

void push() {
	curNode->nextnode = new node;
	curNode->nextnode->prevnode = curNode;
	curNode = curNode->nextnode;
	sz_stack++;

	cout << "�̸��� �Է��ϼ���   >>  ";
	cin.getline(curNode->data.name, 60, '\n');  //getline�� ���ۿ� ���๮�� �� ���ܵ�!

	cout << "������ �Է��ϼ���   >>  ";
	cin >> curNode->data.score; cin.get();

	cout << "�Էµ� �̸��� " << curNode->data.name << "�̸�, ������ " << curNode->data.score << "�� �Դϴ�." << endl;
}

void pop() {
	if (sz_stack == 0) {
		cout << "���� �� �����Ͱ� �����ϴ�." << endl;
		return;
	}

	node* temp = curNode;
	curNode = curNode->prevnode;
	curNode->nextnode = nullptr;

	cout << sz_stack << "��° �л��� " << temp->data.name << "(���� : " << temp->data.score << ")�� ���� �����͸� �����մϴ�." << endl;
	sz_stack--;
	delete temp;
}

void printScore() {
	cout << endl << endl;
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "                    ���ھ��                     " << endl;

	node* mov = root->nextnode;
	for (int i = 0; i < sz_stack; i++) {
		cout << mov->data.name << "  |  " << mov->data.score << "��" << endl;
		mov = mov->nextnode;
	}
	cout << "//////////////////////////////////////////////////" << endl << endl;
}

int main() {
	root = new node; //dummy node
	curNode = root;

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