#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "array.hpp"
#include <chrono>
using namespace std::chrono;

PassengerArray::PassengerArray() : count(0) {
    for (int i = 0; i < MAX_CAPACITY; i++) {
        manifest[i] = nullptr;
    }
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            grid[r][c] = nullptr;
        }
    }
}

PassengerArray::~PassengerArray() {
    for (int i = 0; i < count; i++) {
        delete manifest[i];
    }
}

void loadCSV(PassengerArray& pa) {
    std::ifstream file("C:\\Users\\User\\Desktop\\Homework Folder\\DS\\data_structures\\data\\flight_passenger_data.csv");
    if (!file.is_open()) {
        std::cout << "Error: Could not open file.\n";
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, rowStr, colStr, sClass;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, rowStr, ',');
        std::getline(ss, colStr, ',');
        std::getline(ss, sClass, ',');
        if (idStr.empty()) {
            continue;
        }
        pa.insertNewEntry(std::stoi(idStr), name, std::stoi(rowStr), colStr[0] - 'A', sClass);
    }
    file.close();
    std::cout << "Data loaded successfully.\n";
}

void saveCSV(const PassengerArray& pa) {
    std::ofstream file("C:\\Users\\User\\Desktop\\Homework Folder\\DS\\data_structures\\data\\flight_passenger_data.csv");
    if (!file.is_open()) {
        std::cout << "Error: Could not save file.\n";
        return;
    }
    file << "PassengerID,Name,SeatRow,SeatColumn,Class\n";
    for (int i = 0; i < pa.getCount(); i++) {
        Passenger* p = pa.getPassenger(i);
        file << p->id << "," << p->name << "," << p->seatRow << "," << char('A' + p->seatCol) << "," << p->seatClass << "\n";
    }
    file.close();
    std::cout << "All changes saved to CSV.\n";
}

void PassengerArray::insertNewEntry(int id, const std::string& name, int row, int col, const std::string& seatClass) {
    if (count >= MAX_CAPACITY) {
        std::cout << "Manifest full.\n";
        return;
    }
    Passenger* p = new Passenger{id, name, row, col, seatClass};
    manifest[count++] = p;
    if (row >= 1 && row < ROWS && col >= 0 && col < COLS) {
        grid[row][col] = p;
    }
}

void PassengerArray::searchByName(const std::string& name) const {
    bool found = false;
    for (int i = 0; i < count; i++) {
        Passenger* p = manifest[i];
        if (p->name == name) {
            std::cout << "Found: ID " << p->id << " at Seat " << p->seatRow << char('A' + p->seatCol) << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Not found.\n";
    }
}

void PassengerArray::deletePassengerByID(int id) {
    for (int i = 0; i < count; i++) {
        if (manifest[i]->id == id) {
            Passenger* p = manifest[i];
            if (p->seatRow >= 1 && p->seatRow < ROWS) {
                grid[p->seatRow][p->seatCol] = nullptr;
            }
            delete p;
            for (int j = i; j < count - 1; j++) {
                manifest[j] = manifest[j + 1];
            }
            manifest[--count] = nullptr;
            std::cout << "Passenger deleted.\n";
            return;
        }
    }
    std::cout << "Passenger ID not found.\n";
}

void PassengerArray::sortByID() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (manifest[j]->id > manifest[j + 1]->id) {
                std::swap(manifest[j], manifest[j + 1]);
            }
        }
    }
}

void PassengerArray::listPassengers() const {
    std::cout << std::left << std::setw(10) << "ID" << std::setw(20) << "NAME" << "SEAT\n";
    for (int i = 0; i < count; i++) {
        Passenger* p = manifest[i];
        std::cout << std::setw(10) << p->id<< std::setw(20) << p->name << p->seatRow << char('A' + p->seatCol) << "\n";
    }
}

void PassengerArray::displaySeatAvailabilityGrid() const {
    std::cout << "\nSeating Grid (X = Occupied, . = Empty)\n";
    std::cout << "    A B C D E F\n";
    for (int r = 1; r < ROWS; r++) {
        std::cout << std::setw(2) << r << "  ";
        for (int c = 0; c < COLS; c++) {
            std::cout << (grid[r][c] ? "X " : ". ");
        }
        std::cout << "\n";
    }
}

void arrayInterface() {
    PassengerArray pa;
    loadCSV(pa);
    bool running = true;
    while (running) {
        std::cout <<
            "\n--- Array System Menu ---\n"
            "1. Insert Passenger\n"
            "2. Delete Passenger\n"
            "3. Search by Name\n"
            "4. Sort by ID\n"
            "5. List Passengers\n"
            "6. Display Available Seats\n"
            "7. Exit\n> ";
        int option;
        std::cin >> option;
        switch (option) {
            case 1: {
                int id, row;
                char col;
                std::string name, cls;
                std::cout << "ID: ";
                std::cin >> id;
                std::cout << "Name: ";
                std::getline(std::cin >> std::ws, name);
                std::cout << "Row: ";
                std::cin >> row;
                std::cout << "Col (A-F): ";
                std::cin >> col;
                std::cout << "Class: ";
                std::cin >> cls;
                auto start = high_resolution_clock::now();
                pa.insertNewEntry(id, name, row, col - 'A', cls);
                auto end = high_resolution_clock::now();
                std::cout << "Insertion Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
                saveCSV(pa);
                break;
            }
            case 2: {
                int id;
                std::cout << "ID to delete: ";
                std::cin >> id;
                auto start = high_resolution_clock::now();
                pa.deletePassengerByID(id);
                auto end = high_resolution_clock::now();
                std::cout << "Deletion Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
                saveCSV(pa);
                break;
            }
            case 3: {
                std::string name;
                std::cout << "Enter Name: ";
                std::getline(std::cin >> std::ws, name);
                auto start = high_resolution_clock::now();
                pa.searchByName(name);
                auto end = high_resolution_clock::now();
                std::cout << "Search Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
                break;
            }
            case 4: {
                auto start = high_resolution_clock::now();
                pa.sortByID();
                auto end = high_resolution_clock::now();
                std::cout << "Sort Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n" << "Sorted.\n";
                saveCSV(pa);
                break;
            }
            case 5: {
                pa.listPassengers();
                break;
            }
            case 6: {
                pa.displaySeatAvailabilityGrid();
                break;
            }
            case 7: {
                saveCSV(pa);
                running = false;
                break;
            }
            default: {
                std::cout << "Invalid option.\n";
            }
        }
    }
}