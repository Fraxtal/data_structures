#pragma once
#include <string>

struct Node {
    int id;
    std::string name;
    int seatRow;
    std::string seatCol;
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
    void insertion(int id, const std::string& name, int row, std::string col, const std::string& seatClass);
    void load();
	bool deletion(int id);
    Node* search(const std::string& name) const;
    Node* split(Node* head);
    bool seatCompare(Node* first, Node* second);
    Node* merge(Node* first, Node* second, int criteria, bool desc);
    Node* mergeSort(Node* head, int criteria, bool desc);
	void sort(int criteria, bool desc);
    void display() const;
	Node* getTail();
	Node* getHead();
};

void linkedListInterface();