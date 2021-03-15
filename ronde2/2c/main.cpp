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

struct node{
	int n;
	node *next;

	node() : next(nullptr){};
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

node *colorNext(int b, node *locs, int *colors, Connection *conns, int *people){
	node *first = new node;
	node *last = first;

	int max = 1;
	for (node *current = locs->next; current != nullptr; current = current->next){
		int count = 1;
		for (Connection *conn = conns[current->n].next; conn != nullptr; conn = conn->next, count++){

			if (colors[conn->other] != INT32_MAX) continue;
			colors[conn->other] = b;
			node *t = new node;
			t->n = conn->other;
			last->next = t;
			last = t;
		}
		if (count > max){
			max = count;
		}
	}

	*people *= max;

	return first;
}

void color(Connection *conn){
	node **locs = new node*[b];
	for (int i = 0; i < b; i++){
		locs[i] = new node;
		node *t = new node;
		t->n = i;
		locs[i]->next = t;
	}

	int *maxes = new int[b];
	for (int i = 0; i < b; i++) maxes[i] = 1;

	int *colors = new int[n + b];
	for (int i = 0; i < n + b; i++) colors[i] = INT32_MAX;

	for(;;){
		bool conti = false;
		for (int i = 0; i < b; i++){
			locs[i] = colorNext(i, locs[i], colors, conn, &maxes[i]);
			if (locs[i]->next != nullptr) conti = true;
		}
		if (!conti) break;
	}

	for (int i = 0; i < b; i++){
		printf("%i\n", maxes[i]);
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

	color(connections);

	fflush(stdout);
	return 0;
}