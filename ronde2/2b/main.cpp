#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

#define ll long long
#define ull unsigned long long

#define LOG(x) std::cerr << x << std::endl;

int b, n, m;

struct Connection {
	int other;
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

void findMaxDepth(int depth, int from, Connection *conn, int *max, bool *visited){
	if (visited[from]) return; else visited[from] = true;

	if (depth > *max){
		*max = depth;
	}

	for (Connection *current = conn[from].next; current != nullptr; current = current->next){
		if (current->other < b) continue;
		findMaxDepth(depth + 1, current->other, conn, max, visited);
	}
}

int dijkstra(Connection *connections, int n, int start){
	Node *nodes = new Node[n];
	
	for (int i = 0; i < n; i++) nodes[i].index = i;

	nodes[start].value = 0;

	Node *first = &nodes[start];
	Node *last = &nodes[start];

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

		if (selected == nullptr) {
			int max = INT32_MIN;
			for (int i = 0; i < n; i++){
				if (nodes[i].value > max){
					max = nodes[i].value;
				}
			}
			return max;
		}

		for (Connection *current = connections[selected->index].next; current != nullptr; current = current->next){
			if (nodes[current->other].visited) continue;

			if (nodes[current->other].value == INT32_MAX) {
				last->next = &nodes[current->other];
				nodes[current->other].previous = last;
				last = last->next;
			}

			int newVal = selected->value + 1;
			if (newVal < nodes[current->other].value) nodes[current->other].value = newVal;
		}

		if (selected == first) first = selected->next;
		if (selected == last) last = selected->previous;

		if (selected->previous != nullptr) selected->previous->next = selected->next;
		if (selected->next != nullptr) selected->next->previous = selected->previous;
	}
}

int main(int argc, char **argv){
	scanf("%i %i %i", &b, &n, &m);

	Connection *connections = new Connection[n + b];

	{
		Connection **nodesLast = new Connection*[n + b];
		for (int i = 0; i < n + b; i++) nodesLast[i] = connections + i;

		for (int i = 0; i < m; i++){
			int first, second;
			scanf("%i %i", &first, &second);
			first--;
			second--;

			Connection *newC = new Connection;
			newC->other = second;
			nodesLast[first]->next = newC;
			nodesLast[first] = newC;

			newC = new Connection;
			newC->other = first;
			nodesLast[second]->next = newC;
			nodesLast[second] = newC;
		}

		free(nodesLast);
	}

	for (int i = 0; i < b; i++) {
		int max = dijkstra(connections, n + b, i);
		printf("%i\n", max);
	}

	fflush(stdout);
	return 0;
}