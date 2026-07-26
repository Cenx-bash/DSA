#include <iostream>
#include <cctype>
using namespace std;

int main() {

    string s;
    cin >> s;

    int letters = 0;
    int digits = 0;

    for (char c : s) {

        if (isalpha(c))
            letters++;

        if (isdigit(c))
            digits++;
    }

    cout << "Letters: " << letters << endl;
    cout << "Digits: " << digits << endl;
}