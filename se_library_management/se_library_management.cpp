#include <iostream>
#include "LibrarySystem.h"
#include "Menu.h"

using namespace std;

int main()
{
    LibrarySystem library;

    cout << "Initializing Library Management System..." << endl;
    cout << "Loading sample data..." << endl;
    library.loadSampleData();

    cout << "\n========================================" << endl;
    cout << "   SAMPLE LOGIN CREDENTIALS" << endl;
    cout << "========================================" << endl;
    cout << "Student: S001 / pass123" << endl;
    cout << "Teacher: T001 / teach123" << endl;
    cout << "Admin:   A001 / admin123" << endl;
    cout << "========================================" << endl;
    cout << "\nPress Enter to continue...";
    cin.get();

    Menu menu(&library);
    menu.run();

    return 0;
}
