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

	ll totalNums = s * p;

	ll *votes = new ll[totalNums];
	for (int i = 0; i < totalNums; i++){
		scanf("%llu", &votes[i]);
	}

	ll sum = 0;
	for (int i = 0; i < totalNums; i++){
		sum += votes[i];
	}

	ll sumUnder = 0;
	int counter = 0;

	ll best = INT32_MAX;
	ll a;

	for (int i = 0; i < s; i++){
		for (int j = 0; j < p; j++, counter++){
			sum -= votes[counter];
			sumUnder += votes[counter];
		}

		ll diff = sum - sumUnder;
		diff = abs(diff);

		if (diff < best){
			best = diff;
			a = i + 1;
		}
	}

	printf("%lli\n", a);

	fflush(stdout);
	return 0;
}