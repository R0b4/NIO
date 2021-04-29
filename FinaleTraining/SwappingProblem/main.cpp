#include <iostream>
#include <algorithm>

int testSwapDifference(int s1, int s2, int *a, int *b){
	int differenceold = std::abs(a[s1] - b[s1]) + std::abs(a[s2] - b[s2]);
	int differencenew = std::abs(a[s1] - b[s2]) + std::abs(a[s2] - b[s1]);
	return differenceold - differencenew;
};

int solve(int *a, int *b, int n){
	int max = -0x7FFFFFFF;
	int s1max, s2max;

	for (int i = 0; i < n; i++){
		for (int j = i; j < n; j++){
			int test = testSwapDifference(i, j, a, b);
			if (test > max){
				max = test;
				s1max = i;
				s2max = j;
			}
		}
	}

	int score = 0;
	std::swap(b[s1max], b[s2max]);
	for (int i = 0; i < n; i++){
		score += std::abs(a[i] - b[i]);
	}

	return score;
}

int main(){
	int n;
	scanf("%i", &n);

	int *a = new int[n];
	int *b = new int[n];

	for (int i = 0; i < n; i++) scanf("%i", &a[i]);
	for (int i = 0; i < n; i++) scanf("%i", &b[i]);

	printf("%i\n", solve(a, b, n));
}