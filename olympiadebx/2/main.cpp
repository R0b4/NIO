#include <iostream>
#include <chrono>
#include <string>

#define uint uint_fast32_t

template <typename T>
struct pair{
	T first;
	T second;
};

pair<uint> find(int *nums, uint size){
	pair<uint> best;
	int64_t maxSum = INT64_MIN;

	pair<uint> current {0, 0};
	int64_t sum = 0;

	for (; current.second < size; current.second++){
		if (sum < 1) {
			sum = 0;
			current.first = current.second;
		}

		sum += nums[current.second];

		if (sum > maxSum) goto newBest;
		else if (sum == maxSum) {
			if (best.second - best.first > current.second - current.first) goto newBest;
			else if (best.second - best.first == current.second - current.first) {
				if (best.first > current.first) goto newBest;
			}
		}

		continue;

	newBest:
		maxSum = sum;
		best = current;
	}

	return best;
}

int main(){
	unsigned int size;
	scanf("%u", &size);

	int *nums = new int[size];
	for (int i = 0; i < size; i++){
		scanf("%i", &nums[i]);
	}

	pair<uint> result = find(nums, size);

	std::cout << result.first << ' ' << result.second << std::endl;
}