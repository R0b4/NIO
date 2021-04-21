#include <iostream>
#include <tuple>

std::tuple<int, int, int> gcd2(int a, int b){
	if (b == 0) return {1, 0, a};

	int x, y, d;
	std::tie(x, y, d) = gcd2(b, a % b);

	return {y, x - (a / b) * y, d};
}

int main(){
	for (;;){
		int a, b;
		if (scanf("%i %i", &a, &b) != 2) return 0;

		int x, y, d;
		std::tie(x, y, d) = gcd2(a, b);

		printf("%i %i %i\n", x, y, d);
	}
}