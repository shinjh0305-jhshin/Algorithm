#include <iostream>
using namespace std;

struct info {
	char name[60];
	int score;
};

struct node {
	info data;
	node* nextnode = nullptr;
};

node** list = nullptr;
int* sz_node = nullptr;

int main() {
	int nodes = 10;
	cout << "ũ�Ⱑ " << nodes << "�� linked list�� ����ϴ�." << endl;

	list = new node*[nodes];
	sz_node = new int[nodes]{0};

	sz_node[0]++;
	sz_node[0] += 3;

	return 0;
}

