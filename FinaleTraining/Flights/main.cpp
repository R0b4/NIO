#include <iostream>
#include <queue>
#include <inttypes.h>

#define LEVELS 10

#define CLIMB_COST 60
#define HOLD_COST 30
#define LOWER_COST 20

#define STEP_SIZE 100

struct pos{
	int distance;
	int level;
	int cost;
};

struct Compare{
	bool operator()(const pos &a, const pos &b){
		return a.cost > b.cost;
	}
};

int solve(int x, int **windstrengths){
	int result;
	std::priority_queue<pos, std::vector<pos>, Compare> queue;

	int **costs = new int*[x];
	for (int i = 0; i < x; i++) {
		costs[i] = new int[LEVELS];
		for (int j = 0; j < LEVELS; j++) costs[i][j] = INT32_MAX;
	}

	queue.push({0, 0, 0});

	for (;;){
		pos p = queue.top();
		queue.pop();

		if (p.distance == x) {
			if (p.level == 0) {
				result = p.cost;
				break;
			}

			continue;
		}

		if (p.level == -1) continue;
		if (p.level == LEVELS) continue;
		if (costs[p.distance][p.level] <= p.cost) continue;

		costs[p.distance][p.level] = p.cost;

		int cost = p.cost - windstrengths[p.distance][p.level];

		queue.push({p.distance + 1, p.level + 1, cost + CLIMB_COST});
		queue.push({p.distance + 1, p.level, cost + HOLD_COST});
		queue.push({p.distance + 1, p.level - 1, cost + LOWER_COST});
	}

	for (int i = 0; i < x; i++) delete [] costs[i];
	delete [] costs;

	return result;
}

int main(){
	int cases;
	scanf("%i", &cases);

	for (int i = 0; i < cases; i++){
		int x;

		scanf("%i", &x);

		x /= STEP_SIZE;

		int **windstrengths = new int*[x];
		for (int j = 0; j < x; j++) windstrengths[j] = new int[LEVELS];

		for (int j = LEVELS - 1; j > -1; j--){
			for (int k = 0; k < x; k++){
				int w;
				scanf("%i", &w);
				windstrengths[k][j] = w;
			}
		}

		int result = solve(x, windstrengths);
		printf("%i\n\n", result);

		for (int j = 0; j < x; j++) delete [] windstrengths[j];
		delete [] windstrengths;
	}
}