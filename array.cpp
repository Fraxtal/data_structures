//#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "array.hpp"

PassengerArray::PassengerArray() : count(0) {
    for (int i = 0; i < MAX_CAPACITY; i++) manifest[i] = nullptr;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) grid[r][c] = nullptr;
    }
}

void loadCSV(PassengerArray& pa) {
    std::ifstream file("flight_passenger_data.csv"); 
    if (!file.is_open()) {
        std::cout << "Error: Could not open file. Check the path!\n";
        return;
    }
    std::string line, word;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, rowStr, colStr, sClass;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, rowStr, ',');
        std::getline(ss, colStr, ',');
        std::getline(ss, sClass, ',');
        int id = std::stoi(idStr);
        int row = std::stoi(rowStr);
        int col = colStr[0] - 'A'; 
        pa.insert(id, name, row, col, sClass);
    }
    std::cout << "Data loaded successfully from CSV.\n";
    file.close();
}

PassengerArray::~PassengerArray() {
    for (int i = 0; i < count; i++) {
        delete manifest[i];
    }
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

Passenger* PassengerArray::search(const std::string& name) const {
    for (int i = 0; i < count; i++) {
        if (manifest[i]->name == name) return manifest[i];
    }
    return nullptr;
}

void PassengerArray::deletePassenger(int id) {
    for (int i = 0; i < count; i++) {
        if (manifest[i]->id == id) {
            int r = manifest[i]->seatRow;
            int c = manifest[i]->seatCol;
            grid[r][c] = nullptr;
            delete manifest[i];
            for (int j = i; j < count - 1; j++) {
                manifest[j] = manifest[j + 1];
            }
            manifest[count - 1] = nullptr;
            count--;
            std::cout << "Passenger " << id << " deleted.\n";
            return;
        }
    }
    std::cout << "Passenger not found.\n";
}

void PassengerArray::display() const {
    std::cout << std::left << std::setw(10) << "ID" << std::setw(20) << "NAME" << "SEAT\n";
    for (int i = 0; i < count; i++) {
        std::cout << std::setw(10) << manifest[i]->id 
                  << std::setw(20) << manifest[i]->name 
                  << manifest[i]->seatRow << (char)('A' + manifest[i]->seatCol) << '\n';
    }
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

void arrayInterface(){
    PassengerArray pa;
    loadCSV(pa);
    int option = -1;
    bool running = true;
    std::string temp;
    while (running)
    {
        try {
            option = -1;
            std::cout << "Please select an operation to proceed(Enter option's number):" << std::endl 
            << "1. Insert New Data" << std::endl
            << "2. Delete Data" << std::endl
            << "3. Search by Name" << std::endl
            << "4. Sort Data by ID" << std::endl
            << "5. Display Manifest" << std::endl
            << "6. Exit" << std::endl;
            std::cin >> temp;
            option = stoi(temp);
            switch (option) {
                case 1 : {
                    std::string name, seatClass;
                    int id, seatRow, seatCol;
                    std::cout << "Please enter ID, name, seat row, seat column and seat class: ";
                    std::cin >> id >> name >> seatRow >> seatCol >> seatClass;
                    pa.insert(id, name, seatRow, seatCol, seatClass);
                    break;
                }
                case 2 : {
                    int id;
                    std::cout << "Please enter the ID to delete: ";
                    std::cin >> id;
                    pa.deletePassenger(id);
                    break;
                }
                case 3 : {
                    std::string name;
                    std::cout << "Please enter the name to search: ";
                    std::cin >> name;
                    Passenger* temp = pa.search(name);
                    if (temp != nullptr) {
                        std::cout << "ID: " << temp->id << std::endl
                        << "Name: " << temp->name << std::endl
                        << "Seat Row: " << temp->seatRow << std::endl
                        << "Seat Column: " << temp->seatCol << std::endl
                        << "Seat Class: " << temp->seatClass << std::endl;
                    } else {
                        std::cout << "Name not found!" << std::endl;
                    }
                    break;
                }
                case 4 : {
                    pa.sort();
                    std::cout << "Sort Done" << std::endl;
                    break;
                }
                case 5 : {
                    pa.display();
                    break;
                }
                case 6 : {
                    running = false;
                    break;
                }
                default : {
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
                }
            }
        }
        { catch (const std::invalid_argument& ia) {
            std::cout << "Invalid input. Please enter a number corresponding to the options." << std::endl;
        }
    }
}
}