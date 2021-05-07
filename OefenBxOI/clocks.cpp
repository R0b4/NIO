#include <iostream>

#define HOURS 24

int main(){
	int n, m;
	scanf("%i %i", &n, &m);

	int count = 0;
	int *clocks = new int[n];

	for (int i = 0; i < n; i++) {
		scanf("%i", &clocks[i]);
		if (clocks[i] == 0) count++;
	}

	for (int i = 0; i < m; i++){
		int di, a, b;
		scanf("%i %i %i", &di, &a, &b);

		a--;
		b--;

		for (int j = a; j <= b; j++){
			bool wasZero = (clocks[j] == 0);

			clocks[j] = clocks[j] + di;
			if (clocks[j] > (HOURS - 1)) clocks[j] -= HOURS;

			bool isZero = (clocks[j] == 0);

			if (wasZero && !isZero) count--;
			if (!wasZero && isZero) count++;
		}

		printf("%i\n", count);
	}
}