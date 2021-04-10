#include <iostream>
#include <vector>

struct Task{
	bool top;
	bool added;
	std::vector<int> depends;

	Task() : added(false), top(true){}
};

Task *tasks;
std::vector<int> order;

void goThrough(int task){
	if (tasks[task].added) return;
	for (auto d : tasks[task].depends) goThrough(d);

	order.push_back(task);
	tasks[task].added = true;
}

int main(){
	int n, m;
	scanf("%i %i", &n, &m);

	tasks = new Task[n + 1];

	for (;;){
		int i, j;
		scanf("%i %i", &i, &j);
		if (i == 0 && j == 0) break;

		tasks[j].depends.push_back(i);
		tasks[i].top = false;
	}

	for (int i = 1; i <= n; i++){
		if (tasks[i].top) {
			goThrough(i);
		}
	}

	for (auto t : order){
		printf("%i ", t);
	}
	printf("\n");
}