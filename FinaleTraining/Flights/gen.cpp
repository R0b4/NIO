#include <iostream>

#define CASE_AMOUNT 10
#define DISTANCE 100000
#define STEPS DISTANCE / 100
#define MAX_WIND_STRENGTH 20

int main(){
	FILE *f = fopen("genin.txt", "wb");

	fprintf(f, "%i\n", CASE_AMOUNT);

	for (int i = 0; i < CASE_AMOUNT; i++){
		fprintf(f, "\n%i\n", DISTANCE);

		for (int j = 0; j < STEPS; j++){
			for (int k = 0; k < STEPS; k++){
				int w = rand();
				w %= (2 * MAX_WIND_STRENGTH);
				w -= MAX_WIND_STRENGTH;

				fprintf(f, "%i ", w);
			}
			fprintf(f, "\n");
		}
	}
}