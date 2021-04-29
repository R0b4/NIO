//https://codeforces.com/problemset/problem/1513/C

//works on my machine

#include <iostream>
#include <inttypes.h>

#define MOD 1000000007
#define MAX_M 200000

uint64_t digitsAt0[MAX_M + 1];
uint64_t digitsSums[9];

uint64_t digitsAfterAt0(uint64_t m, uint64_t mod){
	uint64_t sum = 1;

	if (m > 9){
		sum = (sum + digitsSums[(m + 8) % 9]) % mod;
		sum = (sum + MOD - digitsAt0[m - 1]) % mod;
	}

	digitsSums[m % 9] = (digitsSums[m % 9] + sum) % mod;
	digitsAt0[m] = sum;
	return sum;
}

uint64_t digitsAfter(uint64_t n, uint64_t m, uint64_t mod){
	uint64_t sum = 0;
	for (uint64_t i = n; i != 0; i /= 10){
		sum = (sum + digitsAt0[m + (i % 10)]) % mod;
	}
	return sum;
}

int main(){
	for (int i = 0; i < 9; i++) digitsSums[i] = 0;
	for (int i = 0; i < MAX_M; i++){
		digitsAfterAt0(i, MOD);
	}

	int t;
	scanf("%i", &t);

	for (int i = 0; i < t; i++){
		uint64_t n, m;
		scanf("%lu %lu", &n, &m);
		printf("%lu\n", digitsAfter(n, m, MOD));
	}
}
