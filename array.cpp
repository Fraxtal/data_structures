#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "array.hpp"

PassengerArray::PassengerArray() : count(0) {
    for (int i = 0; i < MAX_CAPACITY; i++) manifest[i] = nullptr;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) grid[r][c] = nullptr;
    }
}

PassengerArray::~PassengerArray() {
    for (int i = 0; i < count; i++) {
        delete manifest[i];
    }
}

void loadCSV(PassengerArray& pa) {
    std::ifstream file("flight_passenger_data.csv"); 
    if (!file.is_open()) {
        std::cout << "Error: Could not open file.\n";
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, rowStr, colStr, sClass;
        
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, rowStr, ',');
        std::getline(ss, colStr, ',');
        std::getline(ss, sClass, ',');

        if(idStr.empty()) continue;

        int id = std::stoi(idStr);
        int row = std::stoi(rowStr);
        int col = colStr[0] - 'A'; 
        pa.insert(id, name, row, col, sClass);
    }
    std::cout << "Data loaded successfully.\n";
    file.close();
}

void PassengerArray::insert(int id, const std::string& name, int row, int col, const std::string& seatClass) {
    if (count >= MAX_CAPACITY) {
        std::cout << "Error: Manifest full.\n";
        return;
    }
    Passenger* p = new Passenger{id, name, row, col, seatClass};
    manifest[count++] = p;
    if (row >= 1 && row < ROWS && col >= 0 && col < COLS) {
        grid[row][col] = p;
    }
}

// Search by Name
Passenger* PassengerArray::search(const std::string& name) const {
    for (int i = 0; i < count; i++) {
        if (manifest[i]->name == name) return manifest[i];
    }
    return nullptr;
}

// Search by ID (Required by your .hpp)
Passenger* PassengerArray::search(int id) const {
    for (int i = 0; i < count; i++) {
        if (manifest[i]->id == id) return manifest[i];
    }
    return nullptr;
}

void PassengerArray::deletePassenger(int id) {
    for (int i = 0; i < count; i++) {
        if (manifest[i]->id == id) {
            int r = manifest[i]->seatRow;
            int c = manifest[i]->seatCol;
            
            // Remove from grid if applicable
            if (r >= 1 && r < ROWS && c >= 0 && c < COLS) {
                grid[r][c] = nullptr;
            }

            delete manifest[i];

            // Shift array to maintain 1D continuity
            for (int j = i; j < count - 1; j++) {
                manifest[j] = manifest[j + 1];
            }
            manifest[count - 1] = nullptr;
            count--;
            std::cout << "Passenger " << id << " deleted successfully.\n";
            return;
        }
    }
    std::cout << "Passenger ID not found.\n";
}

void PassengerArray::sort() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (manifest[j]->id > manifest[j + 1]->id) {
                Passenger* temp = manifest[j];
                manifest[j] = manifest[j + 1];
                manifest[j + 1] = temp;
            }
        }
    }
}

void PassengerArray::display() const {
    std::cout << std::left << std::setw(10) << "ID" << std::setw(20) << "NAME" << "SEAT\n";
    for (int i = 0; i < count; i++) {
        std::cout << std::setw(10) << manifest[i]->id 
                  << std::setw(20) << manifest[i]->name 
                  << manifest[i]->seatRow << (char)('A' + manifest[i]->seatCol) << '\n';
    }
}

// Implement the 2D Traversal requirement
void PassengerArray::displayGrid() const {
    std::cout << "\nSeating Grid (X = Occupied, . = Empty)\n";
    std::cout << "    A B C D E F\n";
    for (int r = 1; r < ROWS; r++) {
        std::cout << std::setw(2) << r << "  ";
        for (int c = 0; c < COLS; c++) {
            if (grid[r][c] != nullptr) std::cout << "X ";
            else std::cout << ". ";
        }
        std::cout << "\n";
    }
}

void arrayInterface() {
    PassengerArray pa;
    loadCSV(pa);
    std::string input;
    bool running = true;

    while (running) {
        std::cout << "\n--- Array System Menu ---\n"
                  << "1. Insert Passenger\n2. Delete Passenger\n3. Search by Name\n"
                  << "4. Sort by ID\n5. Display Manifest\n6. Display Grid\n7. Exit\n> ";
        std::cin >> input;

        try {
            int option = std::stoi(input);
            switch (option) {
                case 1: {
                    int id, row; char colChar; std::string name, sClass;
                    std::cout << "Enter ID, Name, Row (1-30), Col (A-F), Class: ";
                    std::cin >> id >> name >> row >> colChar >> sClass;
                    pa.insert(id, name, row, colChar - 'A', sClass);
                    break;
                }
                case 2: {
                    int id; std::cout << "Enter ID to delete: ";
                    std::cin >> id; pa.deletePassenger(id);
                    break;
                }
                case 3: {
                    std::string name; std::cout << "Enter Name: ";
                    std::cin >> name;
                    Passenger* p = pa.search(name);
                    if (p) std::cout << "Found: ID " << p->id << " at Seat " << p->seatRow << (char)('A' + p->seatCol) << "\n";
                    else std::cout << "Not found.\n";
                    break;
                }
                case 4: pa.sort(); std::cout << "Sorted.\n"; break;
                case 5: pa.display(); break;
                case 6: pa.displayGrid(); break;
                case 7: running = false; break;
                default: std::cout << "Invalid Option.\n";
            }
        } catch (...) {
            std::cout << "Invalid input. Please enter a number.\n";
        }
    }
}