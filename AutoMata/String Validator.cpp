#include <iostream>
using namespace std;

int main() {

    string s;
    cin >> s;

    bool valid = true;

    for (char c : s) {
        if (c != '0' && c != '1') {
            valid = false;
            break;
        }
    }

    if (valid)
        cout << "Valid Binary String";
    else
        cout << "Invalid";
}