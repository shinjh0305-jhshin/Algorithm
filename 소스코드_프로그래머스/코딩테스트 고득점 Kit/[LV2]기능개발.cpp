#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;
	int curTopProgress = 0, sz_progress = progresses.size();

	int progressToPop;
	while (curTopProgress < sz_progress) {
		for (int mov = curTopProgress; mov < sz_progress; mov++) { //�ð��� ���� ���Ѵ�.
			if (progresses[mov] >= 100) continue; //�̹� �Ϸ�Ǿ� �� �۾��� ���� �� ���� ��ٸ��� �۾�
			progresses[mov] += speeds[mov];
		}

		progressToPop = 0; //���� �۾��� ��ģ ��, �Ϸ�Ǿ� pop �� �� �ִ� ���α׷���
		for (int mov = curTopProgress; mov < sz_progress; mov++) {
			if (progresses[mov] >= 100) progressToPop++;
			else break;
		}

		if (progressToPop) answer.push_back(progressToPop);
		curTopProgress += progressToPop;
	}

	return answer;
}