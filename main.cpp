#include "array.hpp"
#include "linkedlist.hpp"
using namespace std;

void mainInterface(){
  string choice;
    while (true) {
        cout << "-----------------------------------------------------------------------\n"
                  << " Please Select Your Desired Data Structure Demo (1 or 2 or q to quit)\n"
                  << "-----------------------------------------------------------------------\n"
                  << "1. Array\n"
                  << "2. Linked List\n"
                  << "> ";
        if (!getline(cin, choice)) break;
        if (choice == "1") {
            arrayInterface();
        } else if (choice == "2") {
            linkedListInterface();
        } else if (choice == "q" || choice == "Q") {
            break;
        } else {
            cout << "Invalid input\n";
        }
    }
}


int main() {
  mainInterface();
  return 0;
}