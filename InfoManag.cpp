#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    int id;
    string name;
    string course;
    int yearLevel;
};

class InformationManagement {

private:
    vector<Student> students;

public:

    // Create
    void addStudent(int id, string name, string course, int year) {
        students.push_back({id, name, course, year});
        cout << "Student added successfully.\n";
    }

    // Read
    void displayStudents() {
        if (students.empty()) {
            cout << "No records found.\n";
            return;
        }

        cout << "\n===== STUDENT RECORDS =====\n";

        for (const auto& student : students) {
            cout << "ID: " << student.id << endl;
            cout << "Name: " << student.name << endl;
            cout << "Course: " << student.course << endl;
            cout << "Year: " << student.yearLevel << endl;
            cout << "-------------------------\n";
        }
    }

    // Search
    void searchStudent(int id) {
        for (const auto& student : students) {
            if (student.id == id) {
                cout << "\nStudent Found\n";
                cout << "Name: " << student.name << endl;
                cout << "Course: " << student.course << endl;
                cout << "Year: " << student.yearLevel << endl;
                return;
            }
        }

        cout << "Student not found.\n";
    }

    // Update
    void updateStudent(int id, string newName) {
        for (auto& student : students) {
            if (student.id == id) {
                student.name = newName;
                cout << "Student updated.\n";
                return;
            }
        }

        cout << "Student not found.\n";
    }

    // Delete
    void deleteStudent(int id) {

        for (auto it = students.begin(); it != students.end(); it++) {

            if (it->id == id) {
                students.erase(it);
                cout << "Student deleted.\n";
                return;
            }
        }

        cout << "Student not found.\n";
    }
};

int main() {

    InformationManagement ims;

    ims.addStudent(101, "Karl", "BS Information Systems", 2);
    ims.addStudent(102, "John", "Computer Science", 1);

    ims.displayStudents();

    ims.searchStudent(101);

    ims.updateStudent(101, "Karl Ancel");

    ims.displayStudents();

    ims.deleteStudent(102);

    ims.displayStudents();

    return 0;
}
