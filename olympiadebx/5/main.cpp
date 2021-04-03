#include <iostream>
#include <string.h>

struct connection{
	int value;
	connection *next;

	connection() : next(nullptr){}
	connection(int value) : next(nullptr), value(value){} 
};

struct node{
	int hierarchy;
	connection first;
	connection *end;

	node() {
		end = &first;
	}
};

node *graph;

void findMaxDepth(int start, int parent, int depth, int *max){
	if (*max < depth) *max = depth;

	for (connection *c = graph[start].first.next; c != nullptr; c = c->next){
		if (parent != c->value) findMaxDepth(c->value, start, depth + 1, max);
	}
}

int findTop(){
	int pos = 1;
	int depth = 0;
	findMaxDepth(pos, -1, 0, &depth);

	for (;;){
		for (connection *c = graph[pos].first.next; c != nullptr; c = c->next){
			int cdepth = 0;
			findMaxDepth(c->value, -1, 0, &cdepth);

			if (cdepth < depth) {
				pos = c->value;
				depth = cdepth;
				goto found;
			}
		}
		return pos;

		found:
		continue;
	}
}

void makeHierarchy(int top){
	
}

int findParent(int start, int count){
	if (count == 0) return start;
	for (connection *c = graph[start].first.next; c != nullptr; c = c->next){
		if (graph[start].hierarchy < graph[c->value].hierarchy) return findParent(c->value, count - 1);
	}
	return 0;
}

int main(){
	int n, q;

	scanf("%i", &n);
	scanf("%i", &q);

	graph = new node[n + 1];


	for (int i = 1; i < n; i++){
		int p1, p2;

		scanf("%i", &p1);
		scanf("%i", &p2);

		graph[p1].end->next = new connection(p2);
		graph[p1].end = graph[p1].end->next;

		graph[p2].end->next = new connection(p1);
		graph[p2].end = graph[p2].end->next;
	}

	for (int i = 0; i < q; i++){
		int instruction, a, b;

		scanf("%i", &instruction);
		scanf("%i", &a);
		scanf("%i", &b);

		int result;

		switch (instruction) {
			case 1:

			case 2:
			case 3:
		}
	}
}