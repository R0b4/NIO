#include <iostream>
#include <string.h>

#define MAX_NODE 10000

struct path{
	int value;
	path *next;
};

struct connection{
	bool matched;
	int other;

	connection *next;
	connection *cother;

	connection() : next(nullptr), matched(false) {}
	connection(int other) : next(nullptr), other(other), matched(false) {}
};

struct node{
	bool hasmatched;
	connection first;
	connection *last;

	node() : last(&first){}
};

int r, l, e;
node *right;
node *left;

bool rightPath[MAX_NODE];
bool leftPath[MAX_NODE];

void simpleMatching(){
	for (int i = 0; i < r; i++){
		for (connection *c = right[i].first.next; c != nullptr; c = c->next){
			if (left[c->other].hasmatched) continue;

			c->matched = true;
			c->cother->matched = true;

			right[i].hasmatched = true;
			left[c->other].hasmatched = true;

			break;
		}
	}
}

bool traceLeft(int ln);

bool traceRight(int rn){
	rightPath[rn] = true;

	for (connection *c = right[rn].first.next; c != nullptr; c = c->next){
		if (!c->matched) continue;
		if (leftPath[c->other]) continue;

		if (traceLeft(c->other)){
			c->matched = false;
			c->cother->matched = false;
			//right[rn].hasmatched = false;
			//left[c->other].hasmatched = false;

			rightPath[rn] = false;
			return true;
		} else continue;
	}

	rightPath[rn] = false;
	return true;
}

bool traceLeft(int ln){
	leftPath[ln] = true;

	for (connection *c = left[ln].first.next; c != nullptr; c = c->next){
		//if (c->matched) continue;
		if (rightPath[c->other]) continue;

		if (traceRight(c->other)){
			c->matched = true;
			c->cother->matched = true;
			left[ln].hasmatched = true;
			right[c->other].hasmatched = true;

			leftPath[ln] = false;
			return true;
		} else continue;
	}

	leftPath[ln] = false;
	return false;
}

int main(){
	scanf("%i %i %i", &l, &r, &e);

	right = new node[r];
	left = new node[l];

	memset(rightPath, false, MAX_NODE * sizeof(bool));
	memset(leftPath, false, MAX_NODE * sizeof(bool));

	for (int i = 0; i < e; i++){
		int rn, ln;
		scanf("%i", &ln);
		scanf("%i", &rn);

		//printf("%i %i\n", ln, rn);

		right[rn].last->next = new connection(ln);
		right[rn].last = right[rn].last->next;

		left[ln].last->next = new connection(rn);
		left[ln].last = left[ln].last->next;

		right[rn].last->cother = left[ln].last;
		left[ln].last->cother = right[rn].last;
	}

	simpleMatching();

	for (int i = 0; i < l; i++){
		if (left[i].hasmatched) continue;

		printf("start %i:\n", i);
		traceLeft(i);
	}

	printf("final\n");

	int counter = 0;
	for (int i = 0; i < l; i++){
		if (left[i].hasmatched){
			counter++;
			for (connection *c = left[i].first.next; c != nullptr; c = c->next){
				if (c->matched) printf("%i -> %i\n", i, c->other);
			}
		}
	}

	printf("%i", counter);

}