#include <iostream>
#include <queue>

struct node{
	int distance;
	int n;
};

struct Connection{
	int other;
	int distance;
};

struct Location{
	std::vector<Connection> connections;
	bool isTest = true;
};

struct Compare{
	bool operator()(const node& a, const node& b){
		return a.distance > b.distance;
	}
};

int dijkstra(Location *locs, int n){
	std::priority_queue<node, std::vector<node>, Compare> pqueue;
	int *smallest = new int[n];
	for (int i = 0; i < n; i++) smallest[i] = 0x7FFFFFFF;
		smallest[0] = 0;

	pqueue.push({0, n});
	int last = 0;
	for (; pqueue.size() > 0;){
		node n = pqueue.top();
		if (locs[n.n].isTest) last = n.distance;

		for (auto t : locs[n.n].connections){
			if (smallest[t.other] < n.distance + t.distance) continue;
			smallest[t.other] = n.distance + t.distance;
			pqueue.push({n.distance + t.distance, t.other});
		}

		pqueue.pop();
	}

	return last;
}

int main(){
	int n, m, k;
	scanf("%i %i %i", &n, &m, &k);

	Location *locs = new Location[n];
	std::vector<int> distributieCentra;

	for (int i = 0; i < k; i++){
		int a;
		scanf("%i", &a);
		locs[a].isTest = false;
		distributieCentra.push_back(a);
	}

	for (int i = 0; i < m; i++){
		int a, b, d;
		scanf("%i %i %i", &a, &b, &d);

		a--;
		b--;

		locs[a].connections.push_back({b, d});
		locs[b].connections.push_back({a, d});
	}

	int maxd = -0x7FFFFFFF;
	for (auto t : distributieCentra){
		int d = dijkstra(locs, t);
		if (d > maxd) maxd = d;
	}

	printf("%i\n", maxd);
}