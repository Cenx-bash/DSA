#include <iostream>
#include <stack>
using namespace std;

int main() {

    string input;
    cin >> input;

    stack<char> st;

    for (char c : input) {

        if (c == '(')
            st.push(c);

        else if (c == ')') {

            if (st.empty()) {
                cout << "Rejected";
                return 0;
            }

            st.pop();
        }
    }

    if (st.empty())
        cout << "Accepted";
    else
        cout << "Rejected";
}