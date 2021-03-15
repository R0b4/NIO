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

	ull *sum = new ull[p];
	for (int i = 0; i < s; i++){
		for (int j = 0; j < p; j++){
			int num;
			scanf("%i", &num);
			sum[j] += num;
		}
	}

	for (int i = 0; i < p; i++) printf("%llu\n", sum[i]);

	fflush(stdout);
	return 0;
}