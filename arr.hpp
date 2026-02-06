#include <iostream>

#pragma once
#include <iostream>
#include <string>
#include <iomanip>

struct Passenger {
    int id;
    std::string name;
    int seatRow;
    int seatCol; // 0-5 for A-F
    std::string seatClass;
};

class PassengerArray {
private:
    static const int MAX_CAPACITY = 10000;
    static const int ROWS = 31; // 1-30
    static const int COLS = 6;  // A-F
    
    Passenger* manifest[MAX_CAPACITY]; // 1D Array of pointers
    Passenger* grid[ROWS][COLS];       // 2D Array of pointers
    int count;

public:
    PassengerArray();
    ~PassengerArray();

    void insert(int id, const std::string& name, int row, int col, const std::string& seatClass);
    Passenger* search(const std::string& name) const;
    void deletePassenger(int id); // Changed name to avoid conflict with 'delete' keyword
    void sort();
    void display() const;
    void displayGrid() const;
};

void arrayInterface();