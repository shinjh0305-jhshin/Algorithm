#include <iostream>
#include <cstring>
using namespace std;
#pragma warning (disable:4996)

struct info {
	char name[50];
	int score;
};

int maxSize = 5;
info* heap = nullptr;
int sz_heap = 0;

void increaseHeap() {
	maxSize *= 2;
	info* newheap = new info[maxSize];
	for (int i = 1; i <= sz_heap; i++) {
		strcpy(newheap[i].name, heap[i].name);
		newheap[i].score = heap[i].score;
	}

	delete[] heap;
	heap = newheap;

	cout << "���� ũ�Ⱑ 2��� �����Ǿ� ���� ũ��� " << maxSize << "�Դϴ�." << endl;
}

void deleteHeap() {
	if (sz_heap == 0) {
		cout << "�� ���Դϴ�." << endl;
		return;
	}

	int parent = 1, child = 2;

	char topName[50], endName[50];
	int topScore, endScore;

	strcpy(topName, heap[1].name);
	topScore = heap[1].score;

	strcpy(endName, heap[sz_heap].name);
	endScore = heap[sz_heap].score;

	sz_heap--;

	while (child <= sz_heap) {
		if (child < sz_heap && heap[child].score < heap[child + 1].score) child++;
		if (endScore >= heap[child].score) break;

		strcpy(heap[parent].name, heap[child].name);
		heap[parent].score = heap[child].score;
		parent = child;
		child *= 2;
	}

	strcpy(heap[parent].name, endName);
	heap[parent].score = endScore;

	cout << topName << "�л��� " << topScore << "�� �Դϴ�." << endl;
}

void insertHeap() {
	if (sz_heap + 2 == maxSize) {
		//increase heap
		increaseHeap();
	}

	sz_heap++;
	int curIdx = sz_heap;

	char inName[50];
	int inScore;

	cout << "�̸� ---->>  ";
	cin.getline(inName, 50, '\n');

	cout << "���� ---->>  ";
	cin >> inScore; cin.get();
	

	while ((curIdx != 1) && (inScore > heap[curIdx / 2].score)) {
		strcpy(heap[curIdx].name, heap[curIdx / 2].name);
		heap[curIdx].score = heap[curIdx / 2].score;
		curIdx /= 2;
	}

	strcpy(heap[curIdx].name, inName);
	heap[curIdx].score = inScore;

	cout << "�� �߰� ����!(���� �� ũ�� : " << sz_heap << ")" << endl;
}

int main() {
	heap = new info[maxSize];

	int op;
	while (1) {
		cout << "� �۾��� �����ұ��? (1 : Ǫ��, 2 : ��)   >>  ";
		cin >> op; cin.get();

		if (op == 1) {
			insertHeap();
		}
		if (op == 2) {
			deleteHeap();
		}
	}
}