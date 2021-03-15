#include <iostream>

int main(){
    int number;
    int amountDivisors = 0;

    std::cin >> number;

    for (int i = 1; i <= number; i++){
        if (number % i == 0){
            amountDivisors++;
        }
    }

    std::cout << amountDivisors << std::endl;
    std::cout.flush();
}