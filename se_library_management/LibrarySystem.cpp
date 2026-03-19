#include "LibrarySystem.h"
#include <iostream>
#include <algorithm>

LibrarySystem::LibrarySystem() {
    nextBookId = 1;
    nextReservationId = 1;
}

LibrarySystem::~LibrarySystem() {
    for (auto student : students) delete student;
    for (auto teacher : teachers) delete teacher;
    for (auto admin : admins) delete admin;
    for (auto book : books) delete book;
    for (auto reservation : reservations) delete reservation;
}

Student* LibrarySystem::findStudent(string userId) {
    for (auto student : students) {
        if (student->getUserId() == userId) {
            return student;
        }
    }
    return nullptr;
}

Teacher* LibrarySystem::findTeacher(string userId) {
    for (auto teacher : teachers) {
        if (teacher->getUserId() == userId) {
            return teacher;
        }
    }
    return nullptr;
}

Admin* LibrarySystem::findAdmin(string userId) {
    for (auto admin : admins) {
        if (admin->getUserId() == userId) {
            return admin;
        }
    }
    return nullptr;
}

User* LibrarySystem::authenticateUser(string userId, string password, string& userType) {
    Student* student = findStudent(userId);
    if (student && student->validatePassword(password)) {
        userType = "Student";
        return student;
    }
    
    Teacher* teacher = findTeacher(userId);
    if (teacher && teacher->validatePassword(password)) {
        userType = "Teacher";
        return teacher;
    }
    
    Admin* admin = findAdmin(userId);
    if (admin && admin->validatePassword(password)) {
        userType = "Admin";
        return admin;
    }
    
    return nullptr;
}

void LibrarySystem::addStudent(Student* student) {
    students.push_back(student);
}

void LibrarySystem::addTeacher(Teacher* teacher) {
    teachers.push_back(teacher);
}

void LibrarySystem::addAdmin(Admin* admin) {
    admins.push_back(admin);
}

Book* LibrarySystem::findBook(string bookId) {
    for (auto book : books) {
        if (book->getBookId() == bookId) {
            return book;
        }
    }
    return nullptr;
}

Book* LibrarySystem::findBookByTitle(string title) {
    for (auto book : books) {
        if (book->getTitle() == title) {
            return book;
        }
    }
    return nullptr;
}

void LibrarySystem::addBook(Book* book) {
    books.push_back(book);
}

void LibrarySystem::displayAllBooks() {
    if (books.empty()) {
        cout << "No books in the library." << endl;
        return;
    }
    
    cout << "\n========== ALL BOOKS ==========" << endl;
    for (auto book : books) {
        cout << "\n";
        book->displayInfo();
        cout << "-------------------" << endl;
    }
}

void LibrarySystem::displayAvailableBooks() {
    bool found = false;
    cout << "\n========== AVAILABLE BOOKS ==========" << endl;
    for (auto book : books) {
        if (book->isAvailable()) {
            cout << "\n";
            book->displayInfo();
            cout << "-------------------" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No books available at the moment." << endl;
    }
}

vector<Book*> LibrarySystem::searchBooksByTitle(string keyword) {
    vector<Book*> results;
    for (auto book : books) {
        if (book->getTitle().find(keyword) != string::npos) {
            results.push_back(book);
        }
    }
    return results;
}

vector<Book*> LibrarySystem::searchBooksByAuthor(string keyword) {
    vector<Book*> results;
    for (auto book : books) {
        if (book->getAuthor().find(keyword) != string::npos) {
            results.push_back(book);
        }
    }
    return results;
}

Reservation* LibrarySystem::createReservation(string studentId, string bookId) {
    Book* book = findBook(bookId);
    if (!book) {
        cout << "Book not found!" << endl;
        return nullptr;
    }
    
    if (!book->isAvailable()) {
        cout << "Book is not available!" << endl;
        return nullptr;
    }
    
    Student* student = findStudent(studentId);
    if (!student) {
        cout << "Student not found!" << endl;
        return nullptr;
    }
    
    // Reserve the book (decrease available copies)
    if (book->issueBook()) {
        string reservationId = generateReservationId();
        Reservation* reservation = new Reservation(reservationId, studentId, bookId);
        reservations.push_back(reservation);
        student->addReservation(reservationId);
        
        cout << "Reservation created successfully!" << endl;
        cout << "Reservation ID: " << reservationId << endl;
        cout << "Valid for 3 days. Please collect the book within this period." << endl;
        
        return reservation;
    }
    
    return nullptr;
}

Reservation* LibrarySystem::findReservation(string reservationId) {
    for (auto reservation : reservations) {
        if (reservation->getReservationId() == reservationId) {
            return reservation;
        }
    }
    return nullptr;
}

vector<Reservation*> LibrarySystem::getActiveReservations() {
    vector<Reservation*> activeReservations;
    for (auto reservation : reservations) {
        if (reservation->getIsActive() && !reservation->isExpired()) {
            activeReservations.push_back(reservation);
        }
    }
    return activeReservations;
}

vector<Reservation*> LibrarySystem::getStudentReservations(string studentId) {
    vector<Reservation*> studentReservations;
    for (auto reservation : reservations) {
        if (reservation->getStudentId() == studentId && reservation->getIsActive()) {
            studentReservations.push_back(reservation);
        }
    }
    return studentReservations;
}

bool LibrarySystem::cancelReservation(string reservationId) {
    Reservation* reservation = findReservation(reservationId);
    if (!reservation) {
        cout << "Reservation not found!" << endl;
        return false;
    }
    
    if (!reservation->getIsActive()) {
        cout << "Reservation is already inactive!" << endl;
        return false;
    }
    
    // Return the book copy to available pool
    Book* book = findBook(reservation->getBookId());
    if (book) {
        book->returnBook();
    }
    
    // Remove from student's reservation list
    Student* student = findStudent(reservation->getStudentId());
    if (student) {
        student->removeReservation(reservationId);
    }
    
    reservation->cancelReservation();
    cout << "Reservation cancelled successfully!" << endl;
    return true;
}

void LibrarySystem::cleanupExpiredReservations() {
    for (auto reservation : reservations) {
        if (reservation->getIsActive() && reservation->isExpired()) {
            Book* book = findBook(reservation->getBookId());
            if (book) {
                book->returnBook();
            }
            
            Student* student = findStudent(reservation->getStudentId());
            if (student) {
                student->removeReservation(reservation->getReservationId());
            }
            
            reservation->cancelReservation();
        }
    }
}

bool LibrarySystem::issueBookDirect(string userId, string bookId, bool isTeacher) {
    Book* book = findBook(bookId);
    if (!book) {
        cout << "Book not found!" << endl;
        return false;
    }
    
    if (!book->isAvailable()) {
        cout << "Book is not available!" << endl;
        return false;
    }
    
    if (book->issueBook()) {
        if (isTeacher) {
            Teacher* teacher = findTeacher(userId);
            if (teacher) {
                teacher->addIssuedBook(bookId);
            }
        } else {
            Student* student = findStudent(userId);
            if (student) {
                student->addIssuedBook(bookId);
            }
        }
        cout << "Book issued successfully!" << endl;
        return true;
    }
    
    return false;
}

bool LibrarySystem::issueBookFromReservation(string reservationId) {
    Reservation* reservation = findReservation(reservationId);
    if (!reservation) {
        cout << "Reservation not found!" << endl;
        return false;
    }
    
    if (!reservation->getIsActive()) {
        cout << "Reservation is not active!" << endl;
        return false;
    }
    
    if (reservation->isExpired()) {
        cout << "Reservation has expired!" << endl;
        cancelReservation(reservationId);
        return false;
    }
    
    Student* student = findStudent(reservation->getStudentId());
    if (student) {
        student->addIssuedBook(reservation->getBookId());
        student->removeReservation(reservationId);
    }
    
    reservation->fulfillReservation();
    cout << "Book issued successfully from reservation!" << endl;
    return true;
}

bool LibrarySystem::returnBook(string userId, string bookId, bool isTeacher, int daysLate) {
    Book* book = findBook(bookId);
    if (!book) {
        cout << "Book not found!" << endl;
        return false;
    }
    
    if (isTeacher) {
        Teacher* teacher = findTeacher(userId);
        if (!teacher) {
            cout << "Teacher not found!" << endl;
            return false;
        }
        
        teacher->removeIssuedBook(bookId);
    } else {
        Student* student = findStudent(userId);
        if (!student) {
            cout << "Student not found!" << endl;
            return false;
        }
        
        student->removeIssuedBook(bookId);
        
        // Deduct credits if late
        if (daysLate > 0) {
            int penalty = daysLate * 5;
            student->deductCredits(penalty);
            cout << "Late return! " << penalty << " credits deducted." << endl;
            cout << "Remaining credits: " << student->getCredits() << endl;
        }
    }
    
    book->returnBook();
    cout << "Book returned successfully!" << endl;
    return true;
}

string LibrarySystem::generateBookId() {
    return "B" + to_string(nextBookId++);
}

string LibrarySystem::generateReservationId() {
    return "R" + to_string(nextReservationId++);
}

void LibrarySystem::loadSampleData() {
    // Add sample students
    students.push_back(new Student("S001", "John Doe", "pass123"));
    students.push_back(new Student("S002", "Jane Smith", "pass456"));
    
    // Add sample teachers
    teachers.push_back(new Teacher("T001", "Dr. Smith", "teach123", "Computer Science"));
    teachers.push_back(new Teacher("T002", "Prof. Johnson", "teach456", "Mathematics"));
    
    // Add sample admin
    admins.push_back(new Admin("A001", "Admin", "admin123"));
    
    // Add sample books
    books.push_back(new Book("B001", "Introduction to C++", "Bjarne Stroustrup", "978-0321563842", 5, "Programming"));
    books.push_back(new Book("B002", "Data Structures and Algorithms", "Robert Sedgewick", "978-0132847377", 3, "Programming"));
    books.push_back(new Book("B003", "Operating Systems", "Abraham Silberschatz", "978-1118063330", 4, "Computer Science"));
    books.push_back(new Book("B004", "Database Systems", "Raghu Ramakrishnan", "978-0072465631", 2, "Database"));
    books.push_back(new Book("B005", "Computer Networks", "Andrew Tanenbaum", "978-0132126953", 3, "Networking"));
    
    nextBookId = 6;
    nextReservationId = 1;
    
    cout << "Sample data loaded successfully!" << endl;
}
