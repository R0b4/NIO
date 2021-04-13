#include <iostream>
#include <vector>

struct Task{
	bool top;
	bool added;
	std::vector<int> depends;

	Task() : added(false), top(true){}
};

Task *tasks;
std::vector<int> *gorder;

void goThrough(int task){
	if (tasks[task].added) return;
	for (auto d : tasks[task].depends) goThrough(d);

	gorder->push_back(task);
	tasks[task].added = true;
}

int main(){
	for (;;){
		std::vector<int> order;
		gorder = &order;

		int n, m;
		scanf("%i %i", &n, &m);
		if (n == 0 && m == 0) return 0;

		tasks = new Task[n + 1];

		for (int k = 0; k < m; k++){
			int i, j;
			scanf("%i %i", &i, &j);

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
}