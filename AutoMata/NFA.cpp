#include <iostream>
using namespace std;

int main() {

    string input;
    cin >> input;

    bool accepted = false;

    if (input == "ab" || input == "aab")
        accepted = true;

    if (accepted)
        cout << "Accepted";
    else
        cout << "Rejected";
}
