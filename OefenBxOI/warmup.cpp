#include <iostream>

#define MOD 1000000007

int main(){
	int n;
	scanf("%i", &n);

	int sum = 0;

	for (int i = 0; i < n; i++){
		int a;
		scanf("%i", &a);

		sum = (sum + a) % MOD;
	}

	printf("%i\n", sum);
}