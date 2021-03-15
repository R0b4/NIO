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

struct Connection {
	int other;
	Connection *next;

	Connection() : next(nullptr){};
};

int main(int argc, char **argv){
	int b, n, m;
	scanf("%i %i %i", &b, &n, &m);

	/*
	Connection *connections = new Connection[n];

	{
		Connection **nodesLast = new Connection*[n];
		for (int i = 0; i < n; i++) nodesLast[i] = connections + i;

		for (int i = 0; i < m; i++){
			int first, second;
			scanf("%i %i", &first, &second);

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
	*/

	int *count = new int[b + n];

	for (int i = 0; i < m; i++){
		int first, second;
		scanf("%i %i", &first, &second);

		count[first - 1]++;
		count[second - 1]++;
	}

	int max = INT32_MIN;
	for (int i = 0; i < b + n; i++){
		if (count[i] > max){
			max = count[i];
		}
	}

	int sum = 0;
	for (int i = 0; i < b + n; i++){
		if (count[i] == max){
			sum++;
		}
	}

	printf("%i\n%i\n", max, sum);

	fflush(stdout);
	return 0;
}