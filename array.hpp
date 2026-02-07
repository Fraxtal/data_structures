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
    static const int MAX_CAPACITY = 11000;
    static const int ROWS = 31;
    static const int COLS = 6;
    Passenger* manifest[MAX_CAPACITY];
    Passenger* grid[ROWS][COLS];
    int count;

public:
    PassengerArray();
    ~PassengerArray();
    void insertNewEntry(int id, const std::string& name, int row, int col, const std::string& seatClass);
    void deletePassengerByID(int id);
    void searchByName(const std::string& name) const;
    void sortByID();
    void listPassengers() const;
    void displaySeatAvailabilityGrid() const;
    int getCount() const { return count; }
    Passenger* getPassenger(int index) const { return manifest[index]; }
};

void loadCSV(PassengerArray& pa);
void saveCSV(const PassengerArray& pa);
void arrayInterface();
void arrayInterface();