#include <string>
using namespace std;

struct Node {
    int id;
    string name;
    int seatRow;
    int seatCol;
    string Class;

    struct Node* next;
} Node;