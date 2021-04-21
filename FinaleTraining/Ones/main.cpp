#include <iostream>
#include <inttypes.h>

#define MOD (1 << 29)

int64_t pow(int64_t base, int64_t exp, int64_t mod){
	int64_t ans = 1;
	do {
		if (exp & 1) ans = (ans * base) % mod;
		base = (base * base) % mod;
	} while (exp >>= 1);
	return ans;
}

int64_t modinv(int64_t num, int64_t mod){
	return pow(num, mod - 2, mod);
}

int solve(int n){
	int p = 1;
	int s = 0;
	for (int i = 0; i < 20; i++, p *= 10){
		s += p;
		printf("%i\n", s);

		if (s % n == 0) return i + 1;
	}
}

int main(){
	printf("%i\n", solve(9901));
}