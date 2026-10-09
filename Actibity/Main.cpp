#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

typedef Node* NodePtr;

// Insert at the beginning of the list
void insertBeginning(NodePtr& head, int value) {
    NodePtr newNode = new Node;
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;
    
    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;
}

// Delete a value from the list
void deleteValue(NodePtr& head, int value) {
    NodePtr current = head;
    
    while (current != NULL) {
        if (current->data == value) {
            // If it's the head node
            if (current == head) {
                head = current->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            }
            // If it's a middle or last node
            else {
                current->prev->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = current->prev;
                }
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

// Search for a value in the list
bool search(NodePtr head, int value) {
    NodePtr current = head;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Display the list
void display(NodePtr head) {
    if (head == NULL) {
        cout << "EMPTY";
        return;
    }
    
    NodePtr current = head;
    while (current != NULL) {
        cout << current->data;
        if (current->next != NULL) {
            cout << " ";
        }
        current = current->next;
    }
}

// Count nodes in the list
int countNodes(NodePtr head) {
    int count = 0;
    NodePtr current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Refresh/reset the list
void refresh(NodePtr& head) {
    while (head != NULL) {
        NodePtr temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    NodePtr head = NULL;
    char command;
    int value;
    
    while (cin >> command >> value) {
        if (command == 'i') {
            insertBeginning(head, value);
            cout << "[" << countNodes(head) << "] ";
            display(head);
            cout << endl;
        }
        else if (command == 'd') {
            if (search(head, value)) {
                deleteValue(head, value);
                cout << "[" << countNodes(head) << "] ";
                display(head);
                cout << endl;
            } else {
                cout << "VALUE NOT FOUND" << endl;
            }
        }
        else if (command == 's') {
            if (search(head, value)) {
                cout << "VALUE FOUND" << endl;
            } else {
                cout << "VALUE NOT FOUND" << endl;
            }
        }
        else if (command == 'r') {
            refresh(head);
            cout << "[" << countNodes(head) << "] ";
            display(head);
            cout << endl;
        }
    }
    
    return 0;
}
