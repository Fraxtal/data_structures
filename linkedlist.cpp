#pragma once
#include <iostream>
#include <string>
#include "linkedlist.hpp"

LinkedList::LinkedList() = default;
LinkedList::~LinkedList() {
    Node* cur = head;
    while (cur) { Node* next = cur->next; delete cur; cur = next; }
}

void LinkedList::insert(int id, const std::string& name, int row, int col, const std::string& seatClass) {
    Node* n = new Node{id, name, row, col, seatClass, nullptr};
    if (!head) head = tail = n;
    else { tail->next = n; tail = n; }
}

Node* LinkedList::search(const std::string& name) const {
    for (Node* cur = head; cur; cur = cur->next) if (cur->name == name) return cur;
    return nullptr;
}

void LinkedList::sort() {
    //To sort
}

void LinkedList::display() const {
    for (Node* cur = head; cur; cur = cur->next)
        std::cout << cur->id << ' ' << cur->name << '\n';
}

void linkedListInterface(){
    // Implementation for linked list interface
}