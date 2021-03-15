#include <iostream>

#define uint uint_fast32_t
#define uchar uint_fast8_t

uint pow(uint base, uchar exponent){
	uint result = base;
	for (uchar i = 1; i < exponent; i++) result *= base;
	return result;
}

int main(){
	uint num;
	std::cin >> num;

	uint base;
	uint exp;
	uint best = UINT32_MAX;

	for (uchar i = 2;; i++){
		for (uint j = 2;; j++){
			uint result = pow(j, i);

			if (result > num){
				best = best < result ? best : result;

				if (j == 2){
					std::cout << best << std::endl;
					return 0;
				}

				break;
			}
		}
	}
}