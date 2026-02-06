#include "array.hpp"
//#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

PassengerArray::PassengerArray() : count(0) {
    // Initialize all array elements to nullptr
    for (int i = 0; i < MAX_CAPACITY; i++) manifest[i] = nullptr;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) grid[r][c] = nullptr;
    }
}

PassengerArray::~PassengerArray() {
    for (int i = 0; i < count; i++) {
        delete manifest[i]; // Clean up heap memory
    }
}

void PassengerArray::insert(int id, const std::string& name, int row, int col, const std::string& seatClass) {
    if (count >= MAX_CAPACITY) {
        std::cout << "Error: Manifest full.\n";
        return;
    }

    // Create new passenger on heap
    Passenger* p = new Passenger{id, name, row, col, seatClass};
    
    // Add to 1D Array
    manifest[count++] = p;

    // Add to 2D Grid if within bounds
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
            // 1. Remove from 2D Grid
            int r = manifest[i]->seatRow;
            int c = manifest[i]->seatCol;
            grid[r][c] = nullptr;

            // 2. Delete the actual object
            delete manifest[i];

            // 3. Shift 1D array to fill the gap (maintain continuity)
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

// Sort passengers by their IDs using Bubble Sort
void PassengerArray::sort() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (manifest[j]->id > manifest[j + 1]->id) {
                // Swap the pointers to sort based on passenger IDs
                Passenger* temp = manifest[j];
                manifest[j] = manifest[j + 1];
                manifest[j + 1] = temp;
            }
        }
    }
}
