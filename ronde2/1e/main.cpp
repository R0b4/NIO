#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

#define ll long long
#define ull unsigned long long

#define LOG(x) std::cerr << x << std::endl;



int main(int argc, char **argv){
	int p;
	int s;
	int z;
	scanf("%i", &p);
	scanf("%i", &s);
	scanf("%i", &z);

	ull sum = 0;
	ull *partySum = new ull[p];
	for (int i = 0; i < p; i++) partySum[i] = 0;

	for (int i = 0; i < s; i++){
		for (int j = 0; j < p; j++){
			unsigned int num;
			scanf("%i", &num);
			sum += num;
			partySum[j] += num;
		}
	}

	float ratio = (float)sum / (float)z;
	ull kiesdeler = (int)ceilf(ratio);

	ull *volleZetels = new ull[p];

	int restZetels = z;

	for (int i = 0; i < p; i++) {
		volleZetels[i] = partySum[i] / kiesdeler;
		restZetels -= volleZetels[i];
	}

	for (int i = 0; i < restZetels; i++){
		int breuk = INT32_MIN;
		int party = 0;
		for (int i = 0; i < p; i++){
			if (volleZetels[i] == 0) continue;

			int num = partySum[i] / (volleZetels[i] + 1);
			if (num > breuk){
				breuk = num;
				party = i;
			}
		}

		volleZetels[party]++;
	}

	for (int i = 0; i < p; i++) printf("%llu\n", volleZetels[i]);

	fflush(stdout);
	return 0;
}