#include <iostream>
using namespace std;

int main() {

    string tape;
    cin >> tape;

    for (int i = 0; i < tape.length(); i++) {

        if (tape[i] == '0')
            tape[i] = '1';
    }

    cout << tape;

    return 0;
}