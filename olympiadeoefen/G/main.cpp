#include <iostream>

#define uint uint_fast32_t
#define uchar uint_fast8_t

#define PRIME_AMOUNT 3

struct node {
	uint value;
	node *next;

	node() : next(nullptr) {}
};

node *primeList = nullptr;
node *end = nullptr;

bool isPrime(uint num) {
	if (num == 2) return true;
	if ((num & 1) == 0) return false;

	uint half = num >> 1;
	uint start = 3;

	if (primeList != nullptr){
		for (node *current = primeList; current != nullptr; current = current->next) {
			if (num % current->value == 0) return false;
		}
		start = end->value + 2;
	}

	for (uint i = start; i < half; i += 2) {
		if (num % i == 0) return false;
	}

	return true;
}

uint findNextPrime(uint num) {
	for (uint i = num + 1;; i++) {
		if (isPrime(i)) {
			if (primeList == nullptr) {
				primeList = new node;
				end = primeList;
				end->value = i;
			} else {
				node *n = new node;
				n->value = i;
				end->next = n;
				end = n;
			}

			//std::cout << i << std::endl;

			return i;
		}
	}
}

bool isSphenisch(uint num) {
	uchar primes = 0;

	for (node *current = primeList; current != nullptr; current = current->next) {
		if (num % current->value == 0) {
			num /= current->value;
			primes++;
			if (primes == PRIME_AMOUNT) {
				return num == 1 ? true : false;
			}
		}

		if (current->value > num) return false;
	}

	for (uint i = findNextPrime(primeList == nullptr ? 1 : end->value);; i = findNextPrime(i)) {
		if (num % i == 0) {
			primes++;
			num /= i;
			if (primes == PRIME_AMOUNT) {
				return num == 1 ? true : false;
			}
		}

		if (i > num) return false;
	}
}

int main() {
	uint num;
	std::cin >> num;

	for (int i = num + 1;; i++) {
		if (isSphenisch(i)) {
			std::cout << i << std::endl;
			return 0;
		}
	}
}