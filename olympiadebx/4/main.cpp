#include <iostream>

struct Connection {
	int other;
	int distance;
	Connection *next;

	Connection() : next(nullptr){};
};

struct Node {
	int index;
	bool visited;
	int value;

	Node *next;
	Node *previous;

	Node() : visited(false), value(INT32_MAX), next(nullptr), previous(nullptr){}
};

int dijkstra(Connection *connections, int n){
	Node *nodes = new Node[n];
	
	for (int i = 0; i < n; i++) nodes[i].index = i;

	nodes->value = 0;

	Node *first = nodes;
	Node *last = nodes;

	for (;;){
		int least = INT32_MAX;
		Node *selected = nullptr;

		for (Node *current = first; current != nullptr; current = current->next){
			if (current->visited) continue;

			if (current->value < least){
				selected = current;
				least = current->value;
			}
		}

		if (selected == nullptr) return -1;
		if (selected->index == n - 1) return selected->value;

		for (Connection *current = connections[selected->index].next; current != nullptr; current = current->next){
			if (nodes[current->other].visited) continue;

			if (nodes[current->other].value == INT32_MAX) {
				last->next = &nodes[current->other];
				nodes[current->other].previous = last;
				last = last->next;
			}

			int newVal = selected->value + current->distance;
			if (newVal < nodes[current->other].value) nodes[current->other].value = newVal;
		}

		if (selected == first) first = selected->next;
		if (selected == last) last = selected->previous;

		if (selected->previous != nullptr) selected->previous->next = selected->next;
		if (selected->next != nullptr) selected->next->previous = selected->previous;
	}
}

int main(){
	int n, m;
	scanf("%i %i", &n, &m);

	Connection *connections = new Connection[n];

	{
		Connection **nodesLast = new Connection*[n];
		for (int i = 0; i < n; i++) nodesLast[i] = connections + i;

		for (int i = 0; i < m; i++){
			int first, second, distance;
			scanf("%i %i %i", &first, &second, &distance);

			Connection *newC = new Connection;
			newC->distance = distance;
			newC->other = second;
			nodesLast[first]->next = newC;
			nodesLast[first] = newC;

			newC = new Connection;
			newC->distance = distance;
			newC->other = first;
			nodesLast[second]->next = newC;
			nodesLast[second] = newC;
		}

		free(nodesLast);
	}

	int result = dijkstra(connections, n);
	printf("%i\n", result);
}