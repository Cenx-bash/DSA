#include <iostream>
using namespace std;

int main() {

    string input;
    cin >> input;

    int state = 0;

    for (char c : input) {
        if (c == '1')
            state = 1 - state;
    }

    if (state == 0)
        cout << "Accepted";
    else
        cout << "Rejected";
}