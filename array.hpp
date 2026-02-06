#pragma once
#include <iostream>
#include <string>
#include <iomanip>

struct Passenger {
    int id;
    std::string name;
    int seatRow;
    int seatCol;
    std::string seatClass;
};

class PassengerArray {
private:
    static const int MAX_CAPACITY = 10100;
    static const int ROWS = 31;
    static const int COLS = 6;
    
    Passenger* manifest[MAX_CAPACITY];
    Passenger* grid[ROWS][COLS];
    int count;

public:
    PassengerArray();
    ~PassengerArray();
    void insert(int id, const std::string& name, int row, int col, const std::string& seatClass);
    Passenger* search(const std::string& name) const;
    Passenger* search(int id) const;    // Keep only one search by ID
    void deletePassenger(int id);       // Keep only one delete
    void sort();
    void display() const;
    void displayGrid() const;
};

void arrayInterface();