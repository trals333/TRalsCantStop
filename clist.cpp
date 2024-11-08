#include "player.hpp"
#include "enums.hpp"

using namespace std;

// Forward declaration of CList
class CList;

// Typedef for unique pointer to Player
template<typename Player>
using upp = std::unique_ptr<Player>;

// Cell class
class Cell {
    friend class CList;

private:
    upp<Player> data;
    Cell* next;

public:
    // Constructor with default value for next
    Cell(Player d, Cell* n = nullptr) : data(new Player(d)), next(n) {}

    // Destructor
    ~Cell() {}
};

// CList class
class CList {
private:
    int counter;
    Cell* head;
    Cell* tail;
    Cell* current;

public:
    // Constructor
    CList() : counter(0), head(nullptr), tail(nullptr), current(nullptr) {}

    // Destructor
    ~CList() {}

    // Accessor function to return the number of Cells in the list
    int count() const {
        return counter;
    }

    // Function to check if the list is empty
    bool empty() const {
        return counter == 0;
    }

    // Function to print all the Cells in the list
    void print() const {
        if (empty()) {
            cout << "List is empty." << std::endl;
            return;
        }

        Cell* temp = head;
        cout << "Printing list: \n";
        do {
            temp->data.get()->print(cout);
            cout << endl;
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    // Function to add a new Cell to the list
    void addCell(Player player) {
        Cell *newCell = new Cell(player);

        if (empty()) {
            head = newCell;
            tail = newCell;
            head->next = head; // Circular link
        } else {
            tail->next = newCell;
            tail = newCell;
            tail->next = head; // Circular link
        }

        counter++;
    }

    // Function to initialize the current pointer to the first cell in the list
    void init() {
        if (!empty()) {
            current = head;
        }
    }

    Player* isCurrent() {
        return current->data.get();
    }

    // Function to move the current pointer to the next Cell in the list
    void next() {
        if (empty()) {
            // Handle empty list
            cerr << "List is empty." << endl;
            return;
        }

        current = current->next;
    }

    // Function to remove the current Cell from the list
    void remove() {
        if (empty()) {
            // Handle empty list
            cerr << "List is empty." << std::endl;
            return;
        }

        Cell* temp = head;
        if (current == head) {
            head = head->next;
        }
        while (temp->next != current) {
            temp = temp->next;
        }

        temp->next = current->next;
        delete current;
        current = temp->next;
        counter--;

    }
};