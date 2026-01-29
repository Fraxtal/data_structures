#pragma once
#include <iostream>
#include <string>
#include <iomanip>

struct Node {
    int id;
    std::string name;
    int seatRow;
    int seatCol;
    std::string seatClass;
};

class Array {
private:
    static const int MAX_CAPACITY = 10000;
    static const int ROWS = 31;
    static const int COLS = 6;
    
    Passenger* manifest[MAX_CAPACITY];
    Passenger* grid[ROWS][COLS];
    int count;

public:
    PassengerArray();
    ~PassengerArray();
    void insert(int id, const std::string& name, int row, int col, const std::string& seatClass);
    Passenger* search(int id) const;
    void deletePassenger(int id);
    void display() const;
    void displayGrid() const;
};

void arrayInterface();