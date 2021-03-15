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

ull *count(int z, int p, int s, ll *votes){
	ll *partySum = new ll[p];
	for (int i = 0; i < s; i++){
		for (int j = 0; j < p; j++){
			partySum[j] = votes[i * p + j];
		}
	}

	ll sum = 0;
	for (int i = 0; i < p * s; i++){
		sum += votes[i];
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

	return volleZetels;
}

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

	ll district1Total;
	ll district2Total;


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
			district1Total = sumUnder;
			district2Total = sum;
		}
	}

	LOG(a);

	ull *district1 = count((z & 1) == 0 ? z / 2 : (district1Total >= district2Total ? z / 2 + 1 : z / 2), p, a, votes);
	ull *district2 = count((z & 1) == 0 ? z / 2 : (district1Total >= district2Total ? z / 2 : z / 2 + 1), p, s - a, votes + a * p);

	for (int i = 0; i < p; i++) printf("%llu %llu\n", district1[i], district2[i]);
	fflush(stdout);
	return 0;
}