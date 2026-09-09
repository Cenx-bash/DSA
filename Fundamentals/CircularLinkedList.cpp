#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class CircularLinkedList {
private:
    Node* rear;   // rear->next always points to the first node (the "head")
    int count;    // keeps track of size so we don't have to walk the list to count

public:
    CircularLinkedList() : rear(nullptr), count(0) {}

    // Destructor: frees every node so we don't leak memory when the list dies
    ~CircularLinkedList() {
        clear();
    }

    bool isEmpty() const {
        return rear == nullptr;
    }

    int size() const {
        return count;
    }

    // ---------- INSERT AT REAR (append) ----------
    void insertAtRear(int value) {
        Node* newNode = new Node();
        newNode->data = value;

        if (rear == nullptr) {
            newNode->next = newNode; // points to itself
            rear = newNode;
        } else {
            newNode->next = rear->next;
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    // ---------- INSERT AT FRONT ----------
    void insertAtFront(int value) {
        Node* newNode = new Node();
        newNode->data = value;

        if (rear == nullptr) {
            newNode->next = newNode;
            rear = newNode;
        } else {
            newNode->next = rear->next;
            rear->next = newNode;
            // rear stays the same — only the head changes
        }
        count++;
    }

    // ---------- INSERT AT A SPECIFIC POSITION (0-indexed) ----------
    void insertAtPosition(int value, int position) {
        if (position <= 0 || isEmpty()) {
            insertAtFront(value);
            return;
        }
        if (position >= count) {
            insertAtRear(value);
            return;
        }

        Node* newNode = new Node();
        newNode->data = value;

        Node* prev = rear->next; // start at head
        for (int i = 0; i < position - 1; i++) {
            prev = prev->next;
        }
        newNode->next = prev->next;
        prev->next = newNode;
        count++;
    }

    // ---------- DELETE FROM FRONT ----------
    void deleteFromFront() {
        if (isEmpty()) {
            cout << "List is empty, nothing to delete." << endl;
            return;
        }

        Node* head = rear->next;

        if (head == rear) {
            delete head;
            rear = nullptr;
        } else {
            rear->next = head->next;
            delete head;
        }
        count--;
    }

    // ---------- DELETE FROM REAR ----------
    void deleteFromRear() {
        if (isEmpty()) {
            cout << "List is empty, nothing to delete." << endl;
            return;
        }

        if (rear->next == rear) {
            delete rear;
            rear = nullptr;
            count--;
            return;
        }

        // need to find the node just BEFORE rear (singly linked, so we walk)
        Node* current = rear->next;
        while (current->next != rear) {
            current = current->next;
        }
        current->next = rear->next; // second-to-last now points to head
        delete rear;
        rear = current;
        count--;
    }

    // ---------- DELETE BY VALUE ----------
    bool deleteValue(int value) {
        if (isEmpty()) return false;

        Node* head = rear->next;

        // special case: deleting the head
        if (head->data == value) {
            deleteFromFront();
            return true;
        }

        Node* prev = head;
        Node* current = head->next;
        while (current != head) {
            if (current->data == value) {
                prev->next = current->next;
                if (current == rear) {
                    rear = prev; // update rear if we deleted the last node
                }
                delete current;
                count--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false; // value not found
    }

    // ---------- SEARCH ----------
    bool search(int value) const {
        if (isEmpty()) return false;

        Node* current = rear->next;
        for (int i = 0; i < count; i++) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    // ---------- TRAVERSE ----------
    void traverse() const {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        Node* head = rear->next;
        Node* current = head;

        do {
            cout << current->data << " -> ";
            current = current->next;
        } while (current != head);

        cout << "(back to head)" << endl;
    }

    // ---------- CLEAR (free all nodes) ----------
    void clear() {
        while (!isEmpty()) {
            deleteFromFront();
        }
    }
};

// ---------- MENU-DRIVEN MAIN ----------
int main() {
    CircularLinkedList list;
    int choice, value, position;

    do {
        cout << "\n===== CIRCULAR LINKED LIST MENU =====\n";
        cout << "1. Insert at Rear\n";
        cout << "2. Insert at Front\n";
        cout << "3. Insert at Position\n";
        cout << "4. Delete from Front\n";
        cout << "5. Delete from Rear\n";
        cout << "6. Delete by Value\n";
        cout << "7. Search\n";
        cout << "8. Traverse (Display)\n";
        cout << "9. Show Size\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                list.insertAtRear(value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                list.insertAtFront(value);
                break;
            case 3:
                cout << "Enter value: ";
                cin >> value;
                cout << "Enter position (0-indexed): ";
                cin >> position;
                list.insertAtPosition(value, position);
                break;
            case 4:
                list.deleteFromFront();
                break;
            case 5:
                list.deleteFromRear();
                break;
            case 6:
                cout << "Enter value to delete: ";
                cin >> value;
                if (list.deleteValue(value))
                    cout << value << " deleted.\n";
                else
                    cout << value << " not found.\n";
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> value;
                cout << (list.search(value) ? "Found!" : "Not found.") << endl;
                break;
            case 8:
                list.traverse();
                break;
            case 9:
                cout << "Size: " << list.size() << endl;
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0; // shift na ba?
}
