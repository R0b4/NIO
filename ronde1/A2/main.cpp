#include <iostream>
#define LOG(x) std::cout << x << std::endl

struct node
{
    int value;
    node *next;
};

bool isRepeated(int number, node *first)
{
    for (;; first = first->next)
    {
        if (first->value == number)
            return true;
        if (first->next == nullptr)
            return false;
    }
}

node *addNumber(int number, node *first)
{
    node *newNode = new node;
    newNode->value = number;
    newNode->next = first;
    return newNode;
}

void delList(node *first)
{
    if (first->next != nullptr) delList(first->next);
    delete first;
}

int main()
{
    int number;
    std::cin >> number;

    int smallest = number;
    node *first = new node;
    first->value = number;
    first->next = nullptr;
    for (;;)
    {
        if (number % 3 == 0)
            number /= 3;
        else
            number += 4;

        if (number < smallest)
            smallest = number;

        if (isRepeated(number, first))
        {
            std::cout << smallest << std::endl;
            delList(first);
            std::cout.flush();
            return 0;
        }
        first = addNumber(number, first);
    }
}