// #pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include "linkedlist.hpp"
using namespace std::chrono;
using namespace std;

LinkedList::LinkedList() = default;
LinkedList::~LinkedList()
{
	Node *cur = head;
	while (cur)
	{
		Node *next = cur->next;
		delete cur;
		cur = next;
	}
}

void LinkedList::insertion(int id, const string &name, int row, string col, const string &seatClass)
{
	Node *n = new Node{id, name, row, col, seatClass, nullptr};
	if (!head)
	{
		head = tail = n;
	}
	else
	{
		tail->next = n;
		tail = n;
	}
}

void LinkedList::load()
{
	auto start = high_resolution_clock::now();
	ifstream file("data/flight_passenger_data.csv");
	if (!file.is_open())
	{
		cout << "Error: Could not read file " << endl;
		return;
	}
	string line;
	getline(file, line);
	while (getline(file, line))
	{
		stringstream str2(line);
		string segmt;
		int id, seatRow;
		string name, seatCol, seatClass;
		getline(str2, segmt, ',');
		id = stoi(segmt);
		getline(str2, name, ',');
		getline(str2, segmt, ',');
		seatRow = stoi(segmt);
		getline(str2, seatCol, ',');
		getline(str2, seatClass, ',');
		insertion(id, name, seatRow, seatCol, seatClass);
	}
	auto end = high_resolution_clock::now();
	cout << "Loaded!" << endl;
	cout << "Loading Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
	PROCESS_MEMORY_COUNTERS pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
	{
		cout << "Memory Usage (Linked List): "
				  << pmc.WorkingSetSize / 1024 << " KB" << endl;
	}
	else
	{
		cerr << "Unable to retrieve memory information." << endl;
	}
}

bool LinkedList::deletion(int id)
{
	if (head->id == id)
	{
		Node *toDel = head;
		head = head->next;
		delete toDel;
		return true;
	}
	Node *prev = head;
	Node *cur = head->next;
	while (cur != nullptr)
	{
		if (cur->id == id)
		{
			prev->next = cur->next;
			delete cur;
			return true;
		}
		prev = cur;
		cur = cur->next;
	}
	return false;
}

Node *LinkedList::search(int id)
{
	for (Node *cur = head; cur; cur = cur->next)
		if (cur->id == id)
			return cur;
	return nullptr;
}

Node *LinkedList::split(Node *head)
{
	Node *full = head;
	Node *half = head;
	while (full != nullptr && full->next != nullptr)
	{
		full = full->next->next;
		if (full != nullptr)
		{
			half = half->next;
		}
	}
	Node *temp = half->next;
	half->next = nullptr;
	return temp;
}

bool LinkedList::seatCompare(Node *first, Node *second)
{
	if (first->seatRow == second->seatRow)
	{
		return (first->seatCol >= second->seatCol);
	}
	return (first->seatRow > second->seatRow);
}

Node *LinkedList::merge(Node *first, Node *second, int criteria, bool desc)
{
	if (first == nullptr)
	{
		return second;
	}
	if (second == nullptr)
	{
		return first;
	}
	bool cmpResult = false;
	switch (criteria)
	{
		case 1:
		{
			cmpResult = (first->id > second->id);
			break;
		}
		case 2:
		{
			cmpResult = (first->name >= second->name);
			break;
		}
		case 3:
		{
			cmpResult = seatCompare(first, second);
			break;
		}
	}
	if ((cmpResult && desc) || (!cmpResult && !desc))
	{
		first->next = merge(first->next, second, criteria, desc);
		return first;
	}
	else
	{
		second->next = merge(first, second->next, criteria, desc);
		return second;
	}
}

Node *LinkedList::mergeSort(Node *head, int criteria, bool desc)
{
	if (head == nullptr || head->next == nullptr)
	{
		return head;
	}
	Node *second = split(head);

	head = mergeSort(head, criteria, desc);
	second = mergeSort(second, criteria, desc);

	return merge(head, second, criteria, desc);
}

void LinkedList::sort(int criteria, bool desc)
{
	auto start = high_resolution_clock::now();
	head = mergeSort(head, criteria, desc);
	if (head == nullptr)
	{
		tail == nullptr;
		return;
	}
	Node *cur = head;
	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
	tail = cur;
	auto end = high_resolution_clock::now();
	cout << "Sorting Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
}

void LinkedList::display() const
{
	auto start = high_resolution_clock::now();
	for (Node *cur = head; cur; cur = cur->next)
		cout << cur->id << ' ' << cur->name << ' ' << cur->seatRow << cur->seatCol << ' ' << cur->seatClass << '\n';
	auto end = high_resolution_clock::now();
	cout << "Display Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
}

Node *LinkedList::getTail()
{
	return tail;
}

Node *LinkedList::getHead()
{
	return head;
}

void linkedListInterface()
{
	LinkedList list;
	int option = -1;
	bool running = true;
	string temp;
	while (running)
	{
		try
		{
			option = -1;
			cout << "Please select an operation to proceed(Enter option's number):" << endl
				 << "1. Load Passenger Data" << endl
				 << "2. Insert New Data" << endl
				 << "3. Delete Data" << endl
				 << "4. Search by ID" << endl
				 << "5. Sort Data" << endl
				 << "6. Display Data" << endl
				 << "7. Exit" << endl;
			cin >> temp;
			cin.ignore();
			option = stoi(temp);
			switch (option)
			{
				case 1:
				{
					list.load();
					break;
				}
				case 2:
				{
					string name, seatCol, seatClass, temp;
					int seatRow;
					cout << "Please enter information as below: " << endl << "Name: ";
					getline(cin, name);
					cout << "Seat Row: ";
					getline(cin, temp);
					seatRow = stoi(temp);
					cout << "Seat Column: ";
					cin >> seatCol;
					cout << "Seat Class: ";
					cin >> seatClass;
					cin.ignore();
					auto start = high_resolution_clock::now();
					list.insertion((list.getTail()->id + 1), name, seatRow, seatCol, seatClass);
					auto end = high_resolution_clock::now();
					cout << "Insert successful" << endl;
					cout << "Insertion Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
					break;
				}
				case 3:
				{
					int id;
					cout << "Please enter the ID to delete: ";
					cin >> id;
					auto start = high_resolution_clock::now();
					if (list.deletion(id))
					{
						cout << "Deletion completed!" << endl;
					}
					else
					{
						cout << "ID not found!" << endl;
					}
					auto end = high_resolution_clock::now();
					cout << "Deletion Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
					break;
				}
				case 4:
				{
					int id;
					cout << "Please enter the ID to search: ";
					cin >> id;
					auto start = high_resolution_clock::now();
					Node *temp = list.search(id);
					if (temp != nullptr)
					{
						cout << "ID: " << temp->id << endl
							<< "Name: " << temp->name << endl
							<< "Seat Row: " << temp->seatRow << endl
							<< "Seat Column: " << temp->seatCol << endl
							<< "Seat Class: " << temp->seatClass << endl;
					}
					else
					{
						cout << "ID not found!" << endl;
					}
					auto end = high_resolution_clock::now();
					cout << "Search Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";
					break;
				}
				case 5:
				{
					int criteria;
					string temp;
					cout << "Please select the criteria to sort(Enter option's number):" << endl
						<< "1. ID" << endl
						<< "2. Name" << endl
						<< "3. Seat" << endl;
					cin.ignore();
					getline(cin, temp);
					criteria = stoi(temp);
					cout << "Do you want to sort it as descending order?(Enter \"Y\" for yes): ";
					cin >> temp;
					bool desc = (temp == "Y" ? true : false);
					list.sort(criteria, desc);
					cout << "Sort Done" << endl;
					break;
				}
				case 6:
				{
					list.display();
					cout << "The end of data" << endl;
					break;
				}
				case 7:
				{
					running = false;
					break;
				}
				default:
				{
					cout << "Invalid input! Please try again" << endl;
					break;
				}
			}
		}
		catch (exception exception)
		{
			cout << "Invalid input! Please try again" << endl;
		}
	}
}