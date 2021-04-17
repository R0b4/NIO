#include <iostream>

#define	MAX_N 1000
#define MAX_K 1000

#define MOD 1000000

int cache[MAX_N + 1][MAX_K + 1];
bool isCached[MAX_N + 1][MAX_K + 1];

int solve(int num, int k){
	if (k == 1) return 1;
	if (isCached[num][k]) return cache[num][k];

	int sum = 0;
	for (int i = 0; i <= num; i++){
		sum += solve(num - i, k - 1);
	}

	sum %= MOD;

	cache[num][k] = sum;
	isCached[num][k] = true;
	return sum;
}

int main(){
	for (int i = 0; i < MAX_N + 1; i++) for (int j = 0; j < MAX_K + 1; j++) isCached[i][j] = false;

	for (;;){
		int n, k;
		scanf("%i %i", &n, &k);
		if (n == 0 && k == 0) return 0;

		int s = solve(n ,k);
		printf("%i\n", s);
	}
}