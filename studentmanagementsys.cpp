#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    char branch[50];
    float cgpa;
    char email[50];

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Branch: ";
        cin.getline(branch, 50);

        cout << "Enter CGPA: ";
        cin >> cgpa;
        cin.ignore();

        cout << "Enter Email: ";
        cin.getline(email, 50);
    }

    void display() {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(15) << branch
             << setw(10) << cgpa
             << setw(25) << email << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "Student added successfully!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n-- Student List --\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Branch"
         << setw(10) << "CGPA"
         << setw(25) << "Email" << endl;

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

void searchStudent() {
    Student s;
    int id, found = 0;

    cout << "Enter ID to search: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "\nStudent Found:\n";
            s.display();
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Student not found!\n";

    file.close();
}

void updateStudent() {
    Student s;
    int id, found = 0;

    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Student updated!\n";
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Student not found!\n";

    file.close();
}

void deleteStudent() {
    Student s;
    int id, found = 0;

    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = 1;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n=== Student Management System ===\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}