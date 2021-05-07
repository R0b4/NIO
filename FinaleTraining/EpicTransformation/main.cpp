#include <map>
#include <algorithm>
#include <vector>
#include <stdio.h>

int main(){
	int t;
	scanf("%i", &t);

	for (int i = 0; i < t; i++){
		int n;
		scanf("%i", &n);

		std::vector<int> v;
		{
			std::map<int, int> nums;
			for (int j = 0; j < n; j++){
				int a;
				scanf("%i", &a);

				if (nums.find(a) == nums.end()) nums[a] = 1;
				else nums[a]++;
			}
			for (auto t : nums){
				//printf("%i\n", t.second);
				v.push_back(t.second);
			}
			std::sort(v.begin(), v.end(), std::greater<int>());
		}

		int p1 = 0;
		int p2 = 1;
		for (;;){
			if (p1 > v.size() || p2 > v.size()) break;

			if (v[p1] > v[p2]){
				v[p1] -= v[p2];
				v[p2] = 0;
				p2++;
			} else {
				v[p2] -= v[p1];
				v[p1] = 0;
				p1 = p2;
				p2++;
			}
		}

		printf("%i\n", v[p1]);
	}
}