#pragma once
#include <iostream>
#include <node.h>
#include <string>
using namespace std;

class linkedlist{
private:
    node*head;
    node*tail;
public:
    linkedlist();
    void insert(string, string, string, string, string, string);
    void search(string);
    void sort(string);
    void display();
};