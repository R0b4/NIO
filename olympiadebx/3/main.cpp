#pragma GCC optimize "Ofast"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define uint uint_fast32_t
#define MAX_NUM 1000000000
#define DIV_SCALE 0b1000000

#define SHIFT 6

void find(uint * const out, const uint * const in, uint size) {
	memset(out, 0, size * sizeof(uint));

	size_t totalSize = 0;
	int divAmount = 0;

	for (long i = 1 << SHIFT; i < MAX_NUM; totalSize += i, divAmount++, i = i << SHIFT);

	totalSize += MAX_NUM;
	divAmount++;

	unsigned short **divisions = new unsigned short*[divAmount];
	unsigned short *allDiv = (unsigned short*)malloc(totalSize * sizeof(unsigned short));
	memset(allDiv, 0, totalSize * sizeof(unsigned short));

	long len = 1;
	for (long i = 0; i < divAmount; len = len << SHIFT, i++) divisions[i] = allDiv + len - 1;

	for (int i = size - 1; i > -1; i--) {
		uint shiftLen = 0;
		for (int j = divAmount - 1; j > -1; j--, shiftLen += SHIFT) {
			uint max = in[i] >> shiftLen;
			uint start = (max >> SHIFT) << SHIFT;

			for (uint k = start; k < max; k++) out[i] += divisions[j][k];

			divisions[j][max]++;
		}
	}
}

int main() {
	uint size;
	scanf("%lu", &size);

	uint *nums = new uint[size * 2];
	uint *result = nums + size;

	for (int i = 0; i < size; i++) scanf("%lu", &nums[i]);

	find(result, nums, size);

	for (int i = 0; i < size; i++) printf("%lu\n", result[i]);
}