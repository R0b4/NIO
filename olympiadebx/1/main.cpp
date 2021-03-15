#include <iostream>

#define uint uint_fast32_t

template <typename T>
struct pair{
	T first;
	T second;
};

pair<uint> findErrors(int *nums, uint size){
	pair<uint> p {0, 0};

	for (uint i = 1; i < size; i++) if (nums[i] < nums[i - 1]) {
		p.first = i - 1;
		break;
	}

	for (int i = size - 2; i > -1; i--) if (nums[i] > nums[i + 1]) {
		p.second = i + 2;
		break;
	}

	return p;
}

pair<int> getMinMax(int *nums, pair<uint> bounds){
	pair<int> p {INT32_MAX, INT32_MIN};

	for (uint i = bounds.first; i < bounds.second; i++) {
		if (nums[i] < p.first) p.first = nums[i];
		if (nums[i] > p.second) p.second = nums[i];
	}
	return p;
}

pair<uint> getBounds(int *nums, pair<int> minmax, pair<uint>errors, uint size){
	pair<uint> p {0, size - 1};

	for (int i = errors.first - 1; i > -1; i--) if (nums[i] <= minmax.first) {
		p.first = i + 1;
		break;
	}

	for (uint i = errors.second; i < size; i++) if (nums[i] >= minmax.second) {
		p.second = i - 1;
		break;
	}

	return p;
}

int main(){
	unsigned int size;
	scanf("%u", &size);

	int *nums = new int[size];
	for (int i = 0; i < size; i++){
		scanf("%i", &nums[i]);
	}

	pair<uint> errors = findErrors(nums, size);
	if (errors.first == 0 && errors.second == 0){
		std::cout << errors.first << ' ' <<  errors.second << std::endl;
		return 0;
	}

	pair<int> minmax = getMinMax(nums, errors);
	pair<uint> bounds = getBounds(nums, minmax, errors, size);
	std::cout << bounds.first << ' ' <<  bounds.second << std::endl;
}