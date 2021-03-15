#include <iostream>

#define uint uint_fast32_t

bool isPrime(uint num) {
	if ((num & 1) == 0) return false;

	uint half = num / 2;

	for (uint i = 3; i < half; i += 2) {
		if (num % i == 0) return false;
	}

	return true;
}

int main(){
	uint num;
	std::cin >> num;

	for (int i = num + 1;; i++){
		if (isPrime(i)) {
			std::cout << i << std::endl;
			return 0;
		}
	}
}