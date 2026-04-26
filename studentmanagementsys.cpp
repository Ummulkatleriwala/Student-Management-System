#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Student {
public:
    int id;
    string name, branch, email;
    float cgpa;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Branch: ";
        getline(cin, branch);

        cout << "Enter CGPA: ";
        cin >> cgpa;
        cin.ignore();

        cout << "Enter Email: ";
        getline(cin, email);
    }
};

string formatRow(Student s) {
    stringstream ss;
    ss << left << setw(10) << s.id
       << setw(20) << s.name
       << setw(15) << s.branch
       << setw(10) << s.cgpa
       << setw(25) << s.email;
    return ss.str();     
}

// Add Student
void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    s.input();
    file << formatRow(s) << endl;
    cout << "Student added successfully!\n";
    file.close();
}

// Display Students
void displayStudents() {
    ifstream file("students.txt");
    string line;

    cout << "\n" << string(80, '=') << endl;
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Branch"
         << setw(10) << "CGPA"
         << setw(25) << "Email";
    cout << "\n" << string(80, '=') << endl;

    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Search Student 
void searchStudent() {
    ifstream file("students.txt");
    string line, id;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> id;

    while (getline(file, line)) {
        if (line.find(id) == 0) {  // ID is at start
            cout << "\nStudent Found:\n" << line << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Student not found!\n";

    file.close();
}

// Delete Student
void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line, id;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> id;

    while (getline(file, line)) {
        if (line.find(id) != 0) {
            temp << line << endl;
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

// Update Student
void updateStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line, id;
    bool found = false;

    cout << "Enter ID to update: ";
    cin >> id;
    cin.ignore();

    while (getline(file, line)) {
        if (line.find(id) == 0) {
            Student s;
            cout << "Enter new details:\n";
            s.input();
            temp << formatRow(s) << endl;
            found = true;
        } else {
            temp << line << endl;
        }
    }
    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Updated successfully!\n";
    else
        cout << "Student not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!";
        }

    } while (choice != 6);

    return 0;
}