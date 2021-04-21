#include <iostream>
#include <vector>

#define MAX_N 1000000

bool isDigitPrime(int num, std::vector<bool> *primes){
	int sum = 0;
	for (int i = num; i != 0; i /= 10) sum += (i % 10);
	return (*primes)[sum];
}

void countDigitPrimes(int *digitPrimeCount){
	std::vector<bool> *prime = new std::vector<bool>(MAX_N + 1, true);

	int digitPrimes = 0;

	digitPrimeCount[0] = 0;
	digitPrimeCount[1] = 0;

	for (int i = 2; i < MAX_N + 1; i++){
		digitPrimeCount[i] = digitPrimes;
		if ((*prime)[i] == false) continue;

		for (int j = i * 2; j < MAX_N + 1; j += i){
			(*prime)[j] = false;
		}

		if (isDigitPrime(i, prime)) digitPrimes++;
		digitPrimeCount[i] = digitPrimes;
	}

	delete prime;
}

int main(){
	int n;
	scanf("%i", &n);

	int *digitPrimeCount = new int[MAX_N + 1];
	countDigitPrimes(digitPrimeCount);

	for (int i = 0; i < n; i++){
		int t1, t2;
		scanf("%i %i", &t1, &t2);

		printf("%i\n", digitPrimeCount[t2] - digitPrimeCount[t1 - 1]);
	}
}