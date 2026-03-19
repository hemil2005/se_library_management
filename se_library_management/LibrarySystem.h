#pragma once
#include <vector>
#include <string>
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "Book.h"
#include "Reservation.h"

using namespace std;

class LibrarySystem {
private:
    vector<Student*> students;
    vector<Teacher*> teachers;
    vector<Admin*> admins;
    vector<Book*> books;
    vector<Reservation*> reservations;
    
    int nextBookId;
    int nextReservationId;

public:
    LibrarySystem();
    ~LibrarySystem();
    
    // User Management
    Student* findStudent(string userId);
    Teacher* findTeacher(string userId);
    Admin* findAdmin(string userId);
    User* authenticateUser(string userId, string password, string& userType);
    
    void addStudent(Student* student);
    void addTeacher(Teacher* teacher);
    void addAdmin(Admin* admin);
    
    // Book Management
    Book* findBook(string bookId);
    Book* findBookByTitle(string title);
    void addBook(Book* book);
    void displayAllBooks();
    void displayAvailableBooks();
    vector<Book*> searchBooksByTitle(string keyword);
    vector<Book*> searchBooksByAuthor(string keyword);
    
    // Reservation Management
    Reservation* createReservation(string studentId, string bookId);
    Reservation* findReservation(string reservationId);
    vector<Reservation*> getActiveReservations();
    vector<Reservation*> getStudentReservations(string studentId);
    bool cancelReservation(string reservationId);
    void cleanupExpiredReservations();
    
    // Issue/Return Book
    bool issueBookDirect(string userId, string bookId, bool isTeacher);
    bool issueBookFromReservation(string reservationId);
    bool returnBook(string userId, string bookId, bool isTeacher, int daysLate = 0);
    
    // Helper functions
    string generateBookId();
    string generateReservationId();
    
    // Initialize with sample data
    void loadSampleData();
};
