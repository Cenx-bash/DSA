#include <iostream>
#include <set>
using namespace std;

int main() {
    // Create a set
    set<int> numbers;

    // Insert elements
    numbers.insert(10);
    numbers.insert(20);
    numbers.insert(30);
    numbers.insert(20); // Duplicate (ignored)

    // Display elements
    cout << "Set elements: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Find an element
    if (numbers.find(20) != numbers.end()) {
        cout << "20 found in the set." << endl;
    } else {
        cout << "20 not found." << endl;
    }

    // Count an element
    cout << "Count of 30: " << numbers.count(30) << endl;

    // Remove an element
    numbers.erase(10);

    cout << "After removing 10: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Size
    cout << "Size of set: " << numbers.size() << endl;

    // Check if empty
    if (numbers.empty()) {
        cout << "The set is empty." << endl;
    } else {
        cout << "The set is not empty." << endl;
    }

    // Clear the set
    numbers.clear();

    cout << "After clearing, size: " << numbers.size() << endl;

    return 0;
}
