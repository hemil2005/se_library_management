#include "Menu.h"
#include <iostream>
#include <limits>

Menu::Menu(LibrarySystem* lib) {
    library = lib;
    currentUser = nullptr;
    currentUserType = "";
}

void Menu::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Menu::pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Menu::displayMainMenu() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "   LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

void Menu::login() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "              LOGIN" << endl;
    cout << "========================================" << endl;
    
    string userId, password;
    cout << "Enter User ID: ";
    cin >> userId;
    cout << "Enter Password: ";
    cin >> password;
    
    string userType;
    User* user = library->authenticateUser(userId, password, userType);
    
    if (user) {
        currentUser = user;
        currentUserType = userType;
        cout << "\nLogin successful! Welcome, " << user->getName() << endl;
        pause();
        
        if (userType == "Student") {
            studentMenu(dynamic_cast<Student*>(user));
        } else if (userType == "Teacher") {
            teacherMenu(dynamic_cast<Teacher*>(user));
        } else if (userType == "Admin") {
            adminMenu(dynamic_cast<Admin*>(user));
        }
    } else {
        cout << "\nInvalid credentials! Please try again." << endl;
        pause();
    }
}

void Menu::studentMenu(Student* student) {
    while (true) {
        library->cleanupExpiredReservations();
        clearScreen();
        cout << "========================================" << endl;
        cout << "         STUDENT MENU" << endl;
        cout << "========================================" << endl;
        cout << "Welcome, " << student->getName() << endl;
        cout << "Credits: " << student->getCredits() << endl;
        cout << "========================================" << endl;
        cout << "1. View Available Books" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. View My Reservations" << endl;
        cout << "4. Cancel Reservation" << endl;
        cout << "5. View My Issued Books" << endl;
        cout << "6. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                viewAvailableBooks();
                break;
            case 2:
                createReservation(student);
                break;
            case 3:
                viewMyReservations(student);
                break;
            case 4:
                cancelMyReservation(student);
                break;
            case 5:
                viewMyIssuedBooks(student);
                break;
            case 6:
                cout << "Logging out..." << endl;
                currentUser = nullptr;
                currentUserType = "";
                return;
            default:
                cout << "Invalid choice! Please try again." << endl;
                pause();
        }
    }
}

void Menu::viewAvailableBooks() {
    clearScreen();
    library->displayAvailableBooks();
    pause();
}

void Menu::createReservation(Student* student) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        CREATE RESERVATION" << endl;
    cout << "========================================" << endl;
    
    library->displayAvailableBooks();
    
    cout << "\nEnter Book ID to reserve (or 0 to cancel): ";
    string bookId;
    cin >> bookId;
    
    if (bookId == "0") {
        return;
    }
    
    library->createReservation(student->getUserId(), bookId);
    pause();
}

void Menu::viewMyReservations(Student* student) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        MY RESERVATIONS" << endl;
    cout << "========================================" << endl;
    
    vector<Reservation*> reservations = library->getStudentReservations(student->getUserId());
    
    if (reservations.empty()) {
        cout << "You have no active reservations." << endl;
    } else {
        for (auto reservation : reservations) {
            cout << "\n";
            reservation->displayInfo();
            Book* book = library->findBook(reservation->getBookId());
            if (book) {
                cout << "Book: " << book->getTitle() << endl;
            }
            cout << "-------------------" << endl;
        }
    }
    pause();
}

void Menu::viewMyIssuedBooks(Student* student) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        MY ISSUED BOOKS" << endl;
    cout << "========================================" << endl;
    
    vector<string> issuedBooks = student->getIssuedBooks();
    
    if (issuedBooks.empty()) {
        cout << "You have no issued books." << endl;
    } else {
        for (const string& bookId : issuedBooks) {
            Book* book = library->findBook(bookId);
            if (book) {
                cout << "\n";
                book->displayInfo();
                cout << "-------------------" << endl;
            }
        }
    }
    pause();
}

void Menu::cancelMyReservation(Student* student) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        CANCEL RESERVATION" << endl;
    cout << "========================================" << endl;
    
    vector<Reservation*> reservations = library->getStudentReservations(student->getUserId());
    
    if (reservations.empty()) {
        cout << "You have no active reservations to cancel." << endl;
        pause();
        return;
    }
    
    for (auto reservation : reservations) {
        cout << "\n";
        reservation->displayInfo();
        cout << "-------------------" << endl;
    }
    
    cout << "\nEnter Reservation ID to cancel (or 0 to go back): ";
    string reservationId;
    cin >> reservationId;
    
    if (reservationId != "0") {
        library->cancelReservation(reservationId);
    }
    pause();
}

void Menu::teacherMenu(Teacher* teacher) {
    while (true) {
        library->cleanupExpiredReservations();
        clearScreen();
        cout << "========================================" << endl;
        cout << "         TEACHER MENU" << endl;
        cout << "========================================" << endl;
        cout << "Welcome, " << teacher->getName() << endl;
        cout << "Department: " << teacher->getDepartment() << endl;
        cout << "========================================" << endl;
        cout << "1. View Available Books" << endl;
        cout << "2. Add New Book" << endl;
        cout << "3. Issue Book Directly" << endl;
        cout << "4. View All Reservations" << endl;
        cout << "5. Approve/Issue Book from Reservation" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. View My Issued Books" << endl;
        cout << "8. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                viewAvailableBooks();
                break;
            case 2:
                addNewBook();
                break;
            case 3:
                issueBookDirectly(teacher);
                break;
            case 4:
                viewAllReservations();
                break;
            case 5:
                approveReservation();
                break;
            case 6:
                returnBookMenu(teacher);
                break;
            case 7:
                viewMyIssuedBooks(nullptr);
                break;
            case 8:
                cout << "Logging out..." << endl;
                currentUser = nullptr;
                currentUserType = "";
                return;
            default:
                cout << "Invalid choice! Please try again." << endl;
                pause();
        }
    }
}

void Menu::addNewBook() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "          ADD NEW BOOK" << endl;
    cout << "========================================" << endl;
    
    cin.ignore();
    string title, author, isbn, category;
    int copies;
    
    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter ISBN: ";
    getline(cin, isbn);
    cout << "Enter Category: ";
    getline(cin, category);
    cout << "Enter Number of Copies: ";
    cin >> copies;
    
    string bookId = library->generateBookId();
    Book* newBook = new Book(bookId, title, author, isbn, copies, category);
    library->addBook(newBook);
    
    cout << "\nBook added successfully!" << endl;
    cout << "Book ID: " << bookId << endl;
    pause();
}

void Menu::issueBookDirectly(Teacher* teacher) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        ISSUE BOOK DIRECTLY" << endl;
    cout << "========================================" << endl;
    
    library->displayAvailableBooks();
    
    cout << "\nEnter Book ID: ";
    string bookId;
    cin >> bookId;
    
    cout << "Issue to (1-Student / 2-Self): ";
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        cout << "Enter Student ID: ";
        string studentId;
        cin >> studentId;
        library->issueBookDirect(studentId, bookId, false);
    } else {
        library->issueBookDirect(teacher->getUserId(), bookId, true);
    }
    pause();
}

void Menu::viewAllReservations() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "       ALL ACTIVE RESERVATIONS" << endl;
    cout << "========================================" << endl;
    
    vector<Reservation*> reservations = library->getActiveReservations();
    
    if (reservations.empty()) {
        cout << "No active reservations." << endl;
    } else {
        for (auto reservation : reservations) {
            cout << "\n";
            reservation->displayInfo();
            
            Student* student = library->findStudent(reservation->getStudentId());
            if (student) {
                cout << "Student Name: " << student->getName() << endl;
            }
            
            Book* book = library->findBook(reservation->getBookId());
            if (book) {
                cout << "Book: " << book->getTitle() << endl;
            }
            cout << "-------------------" << endl;
        }
    }
    pause();
}

void Menu::approveReservation() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "   APPROVE/ISSUE BOOK FROM RESERVATION" << endl;
    cout << "========================================" << endl;
    
    viewAllReservations();
    
    cout << "\nEnter Reservation ID to issue book (or 0 to cancel): ";
    string reservationId;
    cin >> reservationId;
    
    if (reservationId != "0") {
        library->issueBookFromReservation(reservationId);
    }
    pause();
}

void Menu::returnBookMenu(Teacher* teacher) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "          RETURN BOOK" << endl;
    cout << "========================================" << endl;
    
    cout << "Return for (1-Student / 2-Self): ";
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        cout << "Enter Student ID: ";
        string studentId;
        cin >> studentId;
        
        Student* student = library->findStudent(studentId);
        if (!student) {
            cout << "Student not found!" << endl;
            pause();
            return;
        }
        
        vector<string> issuedBooks = student->getIssuedBooks();
        if (issuedBooks.empty()) {
            cout << "Student has no issued books." << endl;
            pause();
            return;
        }
        
        cout << "\nStudent's Issued Books:" << endl;
        for (const string& bookId : issuedBooks) {
            Book* book = library->findBook(bookId);
            if (book) {
                cout << bookId << " - " << book->getTitle() << endl;
            }
        }
        
        cout << "\nEnter Book ID to return: ";
        string bookId;
        cin >> bookId;
        
        cout << "Enter number of days late (0 if on time): ";
        int daysLate;
        cin >> daysLate;
        
        library->returnBook(studentId, bookId, false, daysLate);
    } else {
        vector<string> issuedBooks = teacher->getIssuedBooks();
        if (issuedBooks.empty()) {
            cout << "You have no issued books." << endl;
            pause();
            return;
        }
        
        cout << "\nYour Issued Books:" << endl;
        for (const string& bookId : issuedBooks) {
            Book* book = library->findBook(bookId);
            if (book) {
                cout << bookId << " - " << book->getTitle() << endl;
            }
        }
        
        cout << "\nEnter Book ID to return: ";
        string bookId;
        cin >> bookId;
        
        library->returnBook(teacher->getUserId(), bookId, true, 0);
    }
    pause();
}

void Menu::adminMenu(Admin* admin) {
    while (true) {
        clearScreen();
        cout << "========================================" << endl;
        cout << "          ADMIN MENU" << endl;
        cout << "========================================" << endl;
        cout << "Welcome, " << admin->getName() << endl;
        cout << "========================================" << endl;
        cout << "1. View All Books" << endl;
        cout << "2. Add New Book" << endl;
        cout << "3. View All Users" << endl;
        cout << "4. Add New Student" << endl;
        cout << "5. Add New Teacher" << endl;
        cout << "6. View All Reservations" << endl;
        cout << "7. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                viewAllBooks();
                break;
            case 2:
                addNewBook();
                break;
            case 3:
                viewAllUsers();
                break;
            case 4:
                addNewStudent();
                break;
            case 5:
                addNewTeacher();
                break;
            case 6:
                viewAllReservations();
                break;
            case 7:
                cout << "Logging out..." << endl;
                currentUser = nullptr;
                currentUserType = "";
                return;
            default:
                cout << "Invalid choice! Please try again." << endl;
                pause();
        }
    }
}

void Menu::viewAllBooks() {
    clearScreen();
    library->displayAllBooks();
    pause();
}

void Menu::viewAllUsers() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "          ALL USERS" << endl;
    cout << "========================================" << endl;
    
    cout << "\n--- STUDENTS ---" << endl;
    // This would need additional methods in LibrarySystem to expose users
    cout << "(Student listing functionality to be added)" << endl;
    
    cout << "\n--- TEACHERS ---" << endl;
    cout << "(Teacher listing functionality to be added)" << endl;
    
    pause();
}

void Menu::addNewStudent() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        ADD NEW STUDENT" << endl;
    cout << "========================================" << endl;
    
    string userId, name, password;
    cout << "Enter Student ID: ";
    cin >> userId;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Password: ";
    cin >> password;
    
    Student* newStudent = new Student(userId, name, password);
    library->addStudent(newStudent);
    
    cout << "\nStudent added successfully!" << endl;
    pause();
}

void Menu::addNewTeacher() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        ADD NEW TEACHER" << endl;
    cout << "========================================" << endl;
    
    string userId, name, password, department;
    cout << "Enter Teacher ID: ";
    cin >> userId;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Password: ";
    cin >> password;
    cin.ignore();
    cout << "Enter Department: ";
    getline(cin, department);
    
    Teacher* newTeacher = new Teacher(userId, name, password, department);
    library->addTeacher(newTeacher);
    
    cout << "\nTeacher added successfully!" << endl;
    pause();
}

void Menu::run() {
    while (true) {
        displayMainMenu();
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                cout << "\nThank you for using Library Management System!" << endl;
                return;
            default:
                cout << "Invalid choice! Please try again." << endl;
                pause();
        }
    }
}
