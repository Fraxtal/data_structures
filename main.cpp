#include <iostream>
#include <arr.h>
#include <llist.h>
using namespace std;

int main() {
  mainInterface();
  return 0;
}

void mainInterface(){
  int r;
  while (true){
    try
    {
      cout << "-----------------------------------------------------------------------" << endl 
        << " Please Select Your Desired Data Structure Demo ( 1 or 2 or q to quit) " << endl
        << "-----------------------------------------------------------------------" << endl
        << " 1. Array" << endl
        << " 2. Linked List" << endl;
      cin >> r;
      if (r == 1){
        arrayInterface();
      }
      else if (r == 2){
        linkedListInterface();
      }
      else{
        throw r;
      }
    }
    catch(int r)
    {
      cout << "Invalid Input" << endl;
      cin.clear();
      cin.ignore(1000, '\n');
    }  
  }
}
