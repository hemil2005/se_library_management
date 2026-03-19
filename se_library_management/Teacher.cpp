#include "Teacher.h"
#include <iostream>
#include <algorithm>

Teacher::Teacher() : User() {
    department = "";
    userType = "Teacher";
}

Teacher::Teacher(string userId, string name, string password, string department)
    : User(userId, name, password, "Teacher") {
    this->department = department;
}

string Teacher::getDepartment() const {
    return department;
}

void Teacher::setDepartment(string dept) {
    department = dept;
}

void Teacher::addIssuedBook(string bookId) {
    issuedBookIds.push_back(bookId);
}

void Teacher::removeIssuedBook(string bookId) {
    auto it = find(issuedBookIds.begin(), issuedBookIds.end(), bookId);
    if (it != issuedBookIds.end()) {
        issuedBookIds.erase(it);
    }
}

vector<string> Teacher::getIssuedBooks() const {
    return issuedBookIds;
}

void Teacher::displayInfo() const {
    User::displayInfo();
    cout << "Department: " << department << endl;
    cout << "Books Issued: " << issuedBookIds.size() << endl;
}
