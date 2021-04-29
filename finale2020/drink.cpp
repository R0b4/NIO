#include <iostream>

#define MOD 100

uint64_t pow(uint64_t base, uint64_t exp, uint64_t mod);

uint64_t getFirstPos(uint64_t m){
	return 3 * pow(2, m - 1, MOD);
}

