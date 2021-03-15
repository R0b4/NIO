#include <iostream>

#define REJECTION_CHANCE 50

struct Connection {
	int other;
	int distance;
	Connection *next;

	Connection() : next(nullptr){};
};

int main(int c, char **argv){
	FILE *file = fopen("test.txt", "w+");
	srand(time(0));

	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	fprintf(file, "%i %i\n", n, m);

	Connection *connections = new Connection[n];
	Connection **nodesLast = new Connection*[n];

	for (int i = 0; i < n; i++) nodesLast[i] = connections + i;

	for (int i = 0; i < m; i++){
		int first, second, distance;
		distance = rand() % 1000;

		for (;;){
			first = rand() % n;
			for (second = rand() % n; second == first; second = rand() % n);

			bool accept = true;
			for (Connection *current = connections[first].next; current != nullptr; current = current->next){
				if (current->other == second || rand() % 100 < REJECTION_CHANCE){
					accept = false;
					break;
				}		
			}

			if (accept) break;
		}

		fprintf(file, "%i %i %i\n", first, second, distance);
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

	fflush(file);
	free(nodesLast);
}