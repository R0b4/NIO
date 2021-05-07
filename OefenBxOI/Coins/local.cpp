// DO NOT SUBMIT THIS FILE


// Compile with this file to test locally
// use e.g. the command `g++ local.cpp magictrick.cpp -o magictrick` to compile
//
// The format of an input consists of a line containing N, the number of coins, followed by a line with N integers, either 1 or 2
// The runner will output whether your code was successful or not


#include "magictrick.h"
#include <bits/stdc++.h>
using namespace std;

int K;
bool stage = false;
vector<int> input;
vector<int> stage1;

void remove(int i) {
    assert(0 <= i && i < input.size() && "Index not in range");
    assert(!stage && "Cannot call `remove` in the magician phase.");
    stage1[i] = 0;
}

void reveal(int i) {
    assert(0 <= i && i < input.size() && "Index not in range");
    assert(stage && "Cannot call `reveal` in the assistant phase.");
    assert(stage1[i] == 1 && "Cannot reveal removed or previously revealed coins");
    stage1[i] = 0;
    if (input[i] == 2) {
        cerr << "Failed: revealed a coins showing tails." << endl;
        exit(0);
    }
}

int main() {
    int N;
    cin >> N;
    assert(N >= 3 && "N should be at least 3");
    assert(N % 3 == 0 && "N should be divisible by 3");

    input.resize(N);
    stage1.resize(N);
    K = N / 3;
    for (int i = 0; i < N; i++) {
        cin >> input[i];
        assert((input[i] == 1 || input[i] == 2) && "Invalid input");
        stage1[i] = 1;
    }

    assistant(input);

    if (accumulate(stage1.begin(), stage1.end(), 0) != 2*K) {
        cerr << "Failed: Exactly K coins should be removed" << endl;
        return 0;
    }

    stage = true;

    magician(stage1);

    if (accumulate(stage1.begin(), stage1.end(), 0) != K) {
        cerr << "Failed: Exactly K coins should be revealed" << endl;
        return 0;
    }

    cerr << "Success" << endl;
}
