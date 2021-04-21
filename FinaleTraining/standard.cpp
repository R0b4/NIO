#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <inttypes.h>

#define INT_MAX 0x7FFFFFFF

int gcd(int a, int b){
	if (b == 0) return a;

	return gcd(b, a % b);
}

std::tuple<int, int, int> fancygcd(int a, int b){
	if (b == 0) return {0, 1, a};

	int x, y, d;
	std::tie(x, y, d) = fancygcd(b, a % b);

	return {y, x - (a / b) * y, d};
}

int lcm(int a, int b){
	return (a * b) / gcd(a, b);
}

void warshall(int **table, int n){
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) table[i][j] = INT_MAX;
	for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++){
		table[i][j] = std::min(table[i][j], table[i][k] + table[k][j]);
	}
}

uint64_t pow(uint64_t base, uint64_t exp, uint64_t mod){
	int ans = 0;
	do {
		if (exp & 1) ans = (base * ans) % mod;
		base = (base * base) % mod;
	} while (exp >>= 1);
	
}