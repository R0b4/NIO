#include <iostream>

#define uchar uint_fast8_t
#define uint uint_fast32_t

uint pow(uint base, uint exponent) {
	uint result = base;
	for (uint i = 1; i < exponent; i++) result *= base;
	return result;
}

struct node {
	uint base;
	uint exponent;

	node *next;
};

const clock_t maxTime = 3 * (CLOCKS_PER_SEC / 2);

uint lstCount;
uint *bases = nullptr;
uint *exponents = nullptr;
uint maxUMS = 0;

void found(node *list) {
	uint count = 0;
	uint maxExp = 0;

	for (node *current = list; current != nullptr; current = current->next, count++) if (current->exponent > maxExp) maxExp = current->exponent;

	uint ums = 10 * (count - 1) + maxExp - 1;

	if (ums > maxUMS) {
		maxUMS = ums;

		if (bases != nullptr) delete [] bases;

		bases = (uint *)malloc(count * sizeof(uint) * 2);
		exponents = bases + count;

		for (uint i = 0; list != nullptr; list = list->next, i++) {
			bases[i] = list->base;
			exponents[i] = list->exponent;
		}

		lstCount = count;
	}
}

uint getNextExponent(node *list, uint last){
	for (int i = last + 1;; i++){
		for (; list != nullptr; list = list->next) if (list->exponent == i) goto end;

		return i;

		end:
		continue;
	}
}

bool find(node *next, uint sum, uint goal) {
	if (clock() > maxTime) return true;

	node n;
	n.next = next;
	n.base = next == nullptr ? 2 : next->base + 1;
	n.exponent = getNextExponent(next, 0);

	for (uint i = 0; sum + n.base <= goal; i++, n.exponent = 1, n.base = next == nullptr ? 2 + i : next->base + i + 1) {
		for (uint newSum = sum + pow(n.base, n.exponent); newSum <= goal; n.exponent = getNextExponent(next, n.exponent), newSum = sum + pow(n.base, n.exponent)) {
			//std::cout << n.base << "  " << n.exponent << std::endl;
			if (newSum == goal) found(&n);
			if (find(&n, newSum, goal)) return true;
		}
	}

	return false;
}

void sort() {
	for (int i = 0; i < lstCount; i++)
	{
		for (int j = i + 1; j < lstCount; j++)
		{
			if (exponents[i] < exponents[j])
			{
				uint a = exponents[i];
				uint b = bases[i];

				exponents[i] = exponents[j];
				bases[i] = bases[j];

				exponents[j] = a;
				bases[j] = b;
			}
		}

	}
}

int main() {
	uint num;
	std::cin >> num;

	find(nullptr, 0, num);
	//sort();

	std::cout << maxUMS << std::endl;
	for (int i = 0; i < lstCount; i++) {
		std::cout << bases[i] << " " << exponents[i] << std::endl;
	}
}