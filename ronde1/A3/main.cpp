#include <iostream>
#define LOG(x) std::cout << x << std::endl

struct node{
    int value;
    node *next;
    node *prev;

    node(int value){
        this->value = value;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

struct List{
    node *first;
    node *last;
    bool initialized;
};

void addToFront(int id, List &list){
    node *newNode = new node(id);
    if (list.initialized) {
        newNode->next = list.first;
        list.first->prev = newNode;
        list.first = newNode;
    } else {
        list.first = newNode;
        list.last = newNode;
        list.initialized = true;
    }
}

void addToBack(int id, List &list){
    node *newNode = new node(id);
    if (list.initialized) {
        newNode->prev = list.last;
        list.last->next = newNode;
        list.last = newNode;
    } else {
        list.first = newNode;
        list.last = newNode;
        list.initialized = true;
    }
}

void removeAtFront(List &list){
    if (!list.initialized) return;

    node *current = list.first;
    list.first = current->next;
    delete current;

    if (list.first == nullptr){
        list.initialized = false;
    } else {
        list.first->prev = nullptr;
    }
}

void removeAtBack(List &list){
    if (!list.initialized) return;

    node *current = list.last;
    list.last = current->prev;
    delete current;

    if (list.last == nullptr){
        list.initialized = false;
    } else {
        list.last->next = nullptr;
    }
}

int findID(int id, List &list){
    node *current = list.first;
    for (int i = 0;; current = current->next, i++){
        if (current->value == id)
            return i + 1;
        if (current->next == nullptr)
            return -1;
    }
}

int getIndex(unsigned int index, List &list, bool &found){
    found = true;
    node *current = list.first;
    for (int i = 0;;current = current->next, i++){
        if (i == index) 
            return current->value;
        if (current->next == nullptr)
            break;
    }
    found = false;
    return 0;
}

void deleteList(List &list){
    node *current = list.first;
    node *next;
    for (;;){
        next = current->next;
        delete current;
        current = next;
        if (current == nullptr) return;
    }
}

int main() {
    List list;
    list.initialized = false;
    const char* idNotFound = "id not found";
    const char* indexNotFound = "this index doesn't exist";

    std::string amountString;
    std::getline(std::cin, amountString);
    int amount = std::stoi(amountString);

    std::string *instructions = new std::string[amount];
    for (int i = 0; i < amount; i++){
        std::getline(std::cin, instructions[i]);
    }

    for (int i = 0; i < amount; i++){
        if (instructions[i][0] == 'v'){
            int num = std::atoi(instructions[i].c_str() + 2);
            addToFront(num, list);
        } else if (instructions[i][0] == 'a'){
            int num = std::atoi(instructions[i].c_str() + 2);
            addToBack(num, list);
        } else if (instructions[i][0] == 'V'){
            removeAtFront(list);
        } else if (instructions[i][0] == 'A'){
            removeAtBack(list);
        } else if (instructions[i][0] == '?'){
            int num = std::atoi(instructions[i].c_str() + 2);
            int index = findID(num, list);
            if (index < 0){
                std::cout << idNotFound << std::endl;
            } else {
                std::cout << index << std::endl;
            }
        } else if (instructions[i][0] == '#'){
            int num = std::atoi(instructions[i].c_str() + 2);
            bool found;
            int id = getIndex(num - 1, list, found);
            if (found){
                std::cout << id << std::endl;
            } else {
                std::cout << idNotFound << std::endl;
            }
        }
    }
    std::cout.flush();
    
    deleteList(list);
}