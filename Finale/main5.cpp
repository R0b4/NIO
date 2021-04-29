#include <iostream>

int findMax(int *bestSum, int *sums, int *arr, int n, int from){
	int maxSum = -0x7FFFFFFF;
	int sum = 0;

	if (from > 0){
		maxSum = bestSum[from - 1];
		sum = sums[from - 1];
	}

	for (int i = from; i < n; i++){
		sum += arr[i];
		if (sum > maxSum) maxSum = sum;
		if (sum < 0) sum = 0; 
	}

	return maxSum;
}

int findMax(int *bestSum, int *sums, int *arr, int n){
	int maxSum = -0x7FFFFFFF;

	int sum = 0;
	for (int i = 0; i < n; i++){
		sum += arr[i];
		if (sum > maxSum) maxSum = sum;
		if (sum < 0) sum = 0;

		bestSum[i] = maxSum;
		sums[i] = sum;
	}

	return maxSum;
}

int main(){
	int N, W;
	scanf("%i %i", &N, &W);

	int *arr = new int[N];
	for (int i = 0; i < N; i++) scanf("%i", &arr[i]);

	int *bestSum = new int[N];
	int *sum = new int[N];

	printf("%i\n", findMax(bestSum, sum, arr, N));

	for (int i = 0; i < W; i++){
		int j, s;
		scanf("%i %i", &j, &s);
		arr[j - 1] = s;

		printf("%i\n", findMax(bestSum, sum, arr, N, j - 1));
	}
}