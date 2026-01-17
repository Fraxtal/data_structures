#include <iostream>
#include <fstream>
#include "arr.hpp"
#include "linkedlist.hpp"

void mainInterface(){
  std::string choice;
    while (true) {
        std::cout << "-----------------------------------------------------------------------\n"
                  << " Please Select Your Desired Data Structure Demo (1 or 2 or q to quit)\n"
                  << "-----------------------------------------------------------------------\n"
                  << "1. Array\n"
                  << "2. Linked List\n"
                  << "> ";
        if (!std::getline(std::cin, choice)) break;

        if (choice == "1") {
            arrayInterface();
        } else if (choice == "2") {
            linkedListInterface();
        } else if (choice == "q" || choice == "Q") {
            break;
        } else {
            std::cout << "Invalid input\n";
        }
    }
}


int main() {
  mainInterface();
  return 0;
}