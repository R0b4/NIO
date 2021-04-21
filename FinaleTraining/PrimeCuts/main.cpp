#include <iostream>
#include <vector>

std::vector<bool> *zeef(int end){
	std::vector<bool> *prime = new std::vector<bool>(end, true);

	for (int i = 0; i < prime->size(); i++){
		if (!(*prime)[i]) continue;

		for (int j = i * 2; j < prime->size(); j += i){
			(*prime)[j] = false;
		}
	}

	return prime;
}

int main(){
	int n, c;
	if (scanf("%i %i", &n, &c) != 2) return 0;

	std::vector<bool> *primes = zeef(n);

	int amount = 0;
	for (int i = 0; 0 < primes->size(); i++){
		if ( (*primes)[i] ) amount++;
	} 

	int end = (amount & 1) == 0 ? 2 * c : 2 * c - 1;

	int j = n / 2;
	for (int i = 0; i < end; i++){
		for (;; j++){
			if ((*primes)[j]){
				printf("%i ", j);
				break;
			}
		}
	}
}