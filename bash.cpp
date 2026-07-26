#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Bash {

public:

    void execute(const string& command) {

        cout << "\n$ " << command << endl;

        int status = system(command.c_str());

        if (status == 0)
            cout << "\nCommand executed successfully.\n";
        else
            cout << "\nCommand failed.\n";
    }

};

int main() {

    Bash terminal;

    int choice;

    do {

        cout << "\n========== Bash Executor ==========\n";
        cout << "1. List Files (ls)\n";
        cout << "2. Current Directory (pwd)\n";
        cout << "3. Show Date\n";
        cout << "4. Custom Command\n";
        cout << "0. Exit\n";
        cout << "\nChoice: ";
        cin >> choice;

        cin.ignore();

        switch (choice) {

        case 1:
            terminal.execute("ls");
            break;

        case 2:
            terminal.execute("pwd");
            break;

        case 3:
            terminal.execute("date");
            break;

        case 4: {
            string command;
            cout << "Enter Bash command: ";
            getline(cin, command);
            terminal.execute(command);
            break;
        }

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
