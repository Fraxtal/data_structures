//#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "array.hpp"

PassengerArray::PassengerArray() : count(0) {
    for (int i = 0; i < MAX_CAPACITY; ++i) manifest[i] = nullptr;
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            grid[r][c] = nullptr;
        }
    }
}

PassengerArray::~PassengerArray() {
    for (int i = 0; i < count; ++i) {
        delete manifest[i];
    }
}

void PassengerArray::insert(int id, const std::string& name, int row, int col, const std::string& seatClass) {
    if (count >= MAX_CAPACITY) {
        std::cout << "Error: Manifest full.\n";
        return;
    }
    Passenger* p = new Passenger{id, name, row, col, seatClass};
    manifest[count] = p;
    count++;
    grid[row][col] = p;
}

Passenger* PassengerArray::search(int id) const {
    for (int i = 0; i < count; ++i) {
        if (manifest[i]->id == id) {
            return manifest[i];
        }
    }
    return nullptr;
}

void PassengerArray::deletePassenger(int id) {
    for (int i = 0; i < count; ++i) {
        if (manifest[i]->id == id) {
            int r = manifest[i]->seatRow;
            int c = manifest[i]->seatCol;
            grid[r][c] = nullptr;
            delete manifest[i];
            for (int j = i; j < count - 1; ++j) {
                manifest[j] = manifest[j + 1];
            }
            manifest[count - 1] = nullptr;
            count--;
            std::cout << "Passenger " << id << " cancelled.\n";
            return;
        }
    }
}

void PassengerArray::displayGrid() const {
    std::cout << "\n--- Seating Chart ---\n";
    std::cout << "    A B C   D E F\n";
    for (int i = 1; i < ROWS; ++i) {
        std::cout << std::setw(2) << i << " ";
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j] == nullptr) std::cout << ". ";
            else std::cout << "X ";
            if (j == 2) std::cout << "  ";
        }
        std::cout << "\n";
    }
}

void arrayInterface() {
    // Implementation for array interface
}