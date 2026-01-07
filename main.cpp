#include <iostream>
#include <fstream>
#include <arr.hpp>
using namespace std;

int main() {
  mainInterface();
  return 0;
}

void mainInterface(){
  int choice;
  while (true){
    try
    {
      cout << "-----------------------------------------------------------------------" << endl 
        << " Please Select Your Desired Data Structure Demo ( 1 or 2 or q to quit) " << endl
        << "-----------------------------------------------------------------------" << endl
        << " 1. Array" << endl
        << " 2. Linked List" << endl;
      cin >> choice;
      if (choice == 1){
        arrayInterface();
      }
      else if (choice == 2){
        linkedListInterface();
      }
      else if (choice == 'q'){
        exit(0);
      }
      else{
        throw choice;
      }
    }
    catch(int choice)
    {
      cout << "Invalid Input" << endl;
      cin.clear();
      cin.ignore(1000, '\n');
    }  
  }
}
