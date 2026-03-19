#pragma once
#include "LibrarySystem.h"
#include <string>
using namespace std;

class Menu {
private:
    LibrarySystem* library;
    User* currentUser;
    string currentUserType;
    
    void clearScreen();
    void pause();
    
public:
    Menu(LibrarySystem* lib);
    
    void displayMainMenu();
    void login();
    
    // Student Menus
    void studentMenu(Student* student);
    void viewAvailableBooks();
    void createReservation(Student* student);
    void viewMyReservations(Student* student);
    void viewMyIssuedBooks(Student* student);
    void cancelMyReservation(Student* student);
    
    // Teacher Menus
    void teacherMenu(Teacher* teacher);
    void addNewBook();
    void issueBookDirectly(Teacher* teacher);
    void viewAllReservations();
    void approveReservation();
    void returnBookMenu(Teacher* teacher);
    
    // Admin Menus
    void adminMenu(Admin* admin);
    void manageUsers();
    void addNewStudent();
    void addNewTeacher();
    void viewAllBooks();
    void viewAllUsers();
    
    void run();
};
