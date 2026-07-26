 #include <iostream>
using namespace std;

int main() {
    string input;
    cin >> input;

    int state = 0;

    for (char c : input) {
        if (state == 0) {
            if (c == '0')
                state = 0;
            else if (c == '1')
                state = 1;
        }
        else if (state == 1) {
            if (c == '0')
                state = 0;
            else if (c == '1')
                state = 1;
        }
    }

    if (state == 1)
        cout << "Accepted";
    else
        cout << "Rejected";

    return 0;
}
