#pragma once
#include <string>

struct Node {
    int id;
    std::string name;
    int seatRow;
    int seatCol;
    std::string seatClass;
    Node* next = nullptr;
};

class LinkedList {
private:
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    LinkedList();
    ~LinkedList();
    void insert(int id, const std::string& name, int row, int col, const std::string& seatClass);
    Node* searchByName(const std::string& name) const;
    void sortById();
    void display() const;
};

void linkedListInterface();