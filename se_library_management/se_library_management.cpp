#include <iostream>
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "Book.h"
#include "Reservation.h"

using namespace std;

int main()
{
    cout << "=== Library Management System ===" << endl;
    cout << "\nTesting Classes...\n" << endl;

    Student student1("S001", "John Doe", "pass123");
    cout << "Student Created:" << endl;
    student1.displayInfo();

    cout << "\n-------------------\n" << endl;

    Teacher teacher1("T001", "Dr. Smith", "teach123", "Computer Science");
    cout << "Teacher Created:" << endl;
    teacher1.displayInfo();

    cout << "\n-------------------\n" << endl;

    Book book1("B001", "Introduction to C++", "Bjarne Stroustrup", "978-0321563842", 5, "Programming");
    cout << "Book Created:" << endl;
    book1.displayInfo();

    cout << "\n-------------------\n" << endl;

    Reservation reservation1("R001", "S001", "B001");
    cout << "Reservation Created:" << endl;
    reservation1.displayInfo();

    cout << "\n\nAll classes created successfully!" << endl;

    return 0;
}
