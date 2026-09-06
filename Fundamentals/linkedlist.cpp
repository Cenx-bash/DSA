#include <iostream>
using namespace std;

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~LinkedList() {
        clear();
    }

    // INSERT OPERATIONS

    void pushFront(int value) {
        Node* newNode = new Node(value);

        newNode->next = head;
        head = newNode;

        if (tail == nullptr)
            tail = newNode;

        size++;
    }

    void pushBack(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    void insertAt(int index, int value) {
        if (index < 0 || index > size) {
            cout << "Invalid index.\n";
            return;
        }

        if (index == 0) {
            pushFront(value);
            return;
        }

        if (index == size) {
            pushBack(value);
            return;
        }

        Node* current = head;

        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* newNode = new Node(value);

        newNode->next = current->next;
        current->next = newNode;

        size++;
    }

    // DELETE OPERATIONS

    void popFront() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        head = head->next;

        delete temp;
        size--;

        if (size == 0)
            tail = nullptr;
    }

    void popBack() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }

        Node* current = head;

        while (current->next != tail) {
            current = current->next;
        }

        delete tail;

        tail = current;
        tail->next = nullptr;

        size--;
    }

    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index.\n";
            return;
        }

        if (index == 0) {
            popFront();
            return;
        }

        if (index == size - 1) {
            popBack();
            return;
        }

        Node* current = head;

        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* temp = current->next;

        current->next = temp->next;

        delete temp;
        size--;
    }

    // SEARCH

    int search(int value) {
        Node* current = head;
        int index = 0;

        while (current != nullptr) {
            if (current->data == value)
                return index;

            current = current->next;
            index++;
        }

        return -1;
    }

    bool contains(int value) {
        return search(value) != -1;
    }

    // ACCESS

    int get(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index.");
        }

        Node* current = head;

        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    // REVERSE

    void reverse() {
        Node* previous = nullptr;
        Node* current = head;

        tail = head;

        while (current != nullptr) {
            Node* nextNode = current->next;

            current->next = previous;

            previous = current;
            current = nextNode;
        }

        head = previous;
    }

    // FIND MIDDLE

    int findMiddle() {
        if (head == nullptr) {
            throw runtime_error("List is empty.");
        }

        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr &&
               fast->next != nullptr) {

            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->data;
    }

    // REMOVE DUPLICATES

    void removeDuplicates() {
        Node* current = head;

        while (current != nullptr) {
            Node* runner = current;

            while (runner->next != nullptr) {

                if (runner->next->data == current->data) {

                    Node* duplicate = runner->next;

                    runner->next = runner->next->next;

                    if (duplicate == tail)
                        tail = runner;

                    delete duplicate;
                    size--;

                } else {
                    runner = runner->next;
                }
            }

            current = current->next;
        }
    }

    // SORT

    void sort() {
        if (size < 2)
            return;

        for (Node* i = head; i != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {

                if (i->data > j->data) {
                    swap(i->data, j->data);
                }
            }
        }
    }

    // CYCLE DETECTION

    bool hasCycle() {
        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr &&
               fast->next != nullptr) {

            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true;
        }

        return false;
    }

    // DISPLAY

    void display() {
        Node* current = head;

        cout << "[ ";

        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }

        cout << "NULL ]\n";
    }

    // SIZE

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    // CLEAR

    void clear() {
        Node* current = head;

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};


// MAIN

int main() {

    LinkedList list;

    cout << "=== ADVANCED LINKED LIST ===\n\n";

    // Insert
    list.pushBack(30);
    list.pushBack(10);
    list.pushBack(20);
    list.pushFront(5);

    list.insertAt(2, 10);

    cout << "Initial List:\n";
    list.display();

    // Search
    cout << "\nIndex of 20: "
         << list.search(20) << endl;

    // Get
    cout << "Element at index 2: "
         << list.get(2) << endl;

    // Middle
    cout << "Middle element: "
         << list.findMiddle() << endl;

    // Duplicate removal
    list.removeDuplicates();

    cout << "\nAfter removing duplicates:\n";
    list.display();

    // Sort
    list.sort();

    cout << "\nAfter sorting:\n";
    list.display();

    // Reverse
    list.reverse();

    cout << "\nAfter reversing:\n";
    list.display();

    // Delete
    list.deleteAt(1);

    cout << "\nAfter deleting index 1:\n";
    list.display();

    cout << "\nSize: "
         << list.getSize() << endl;

    cout << "Contains 20: "
         << (list.contains(20) ? "Yes" : "No")
         << endl;

    cout << "Has cycle: "
         << (list.hasCycle() ? "Yes" : "No")
         << endl;

    return 0;
}
