#include <iostream>
#include <string>
using namespace std;

string story[5] = {
	"\"����Լ��� ������?\"",
	"\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.",
	"���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.",
	"���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"",
	"��� �亯�Ͽ���."
};
string answer = "\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"";
int depth;

void initialize() {
	cin >> depth;
}

void tellStory(int iter) {
	string prefix = "";

	for (int i = 0; i < iter * 4; i++) {
		prefix += '_';
	}

	if (iter == depth) {
		cout << prefix << story[0] << endl;
		cout << prefix << answer << endl;
		cout << prefix << story[4] << endl;
		return;
	}


	for (int i = 0; i < 4; i++) {
		cout << prefix << story[i] << endl;
	}

	tellStory(iter + 1);

	cout << prefix << story[4] << endl;
}

void operate() {
	cout << "��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������." << endl;
	tellStory(0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	initialize();
	operate();

	return 0;
}