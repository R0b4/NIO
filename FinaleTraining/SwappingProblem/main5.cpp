#include <iostream>

int findMax(int *arr, int n){
	int maxSum = -0x7FFFFFFF;

	int sum = 0;
	for (int i = 0; i < n; i++){
		sum += arr[i];
		if (sum > maxSum) maxSum = sum;
		if (sum < 0) sum = 0;
	}

	return sum;
}

int main(){
	int N, W;
	scanf("%i %i", &N, &W);

	int *arr = new int[N];
	for (int i = 0; i < N; i++) scanf("%i", &arr[i]);

	printf("%i\n", findMax(arr, N));

	for (int i = 0; i < W; i++){
		int j, s;
		scanf("%i %i", &j, &s);
		arr[j - 1] = s;

		printf("%i\n", findMax(arr, N));
	}
}