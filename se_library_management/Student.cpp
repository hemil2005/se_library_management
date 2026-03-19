#include "Student.h"
#include <iostream>
#include <algorithm>

Student::Student() : User() {
    credits = 100;
    userType = "Student";
}

Student::Student(string userId, string name, string password) 
    : User(userId, name, password, "Student") {
    credits = 100;
}

int Student::getCredits() const {
    return credits;
}

void Student::deductCredits(int amount) {
    credits -= amount;
    if (credits < 0) credits = 0;
}

void Student::addCredits(int amount) {
    credits += amount;
}

void Student::addReservation(string reservationId) {
    reservationIds.push_back(reservationId);
}

void Student::removeReservation(string reservationId) {
    auto it = find(reservationIds.begin(), reservationIds.end(), reservationId);
    if (it != reservationIds.end()) {
        reservationIds.erase(it);
    }
}

vector<string> Student::getReservations() const {
    return reservationIds;
}

void Student::addIssuedBook(string bookId) {
    issuedBookIds.push_back(bookId);
}

void Student::removeIssuedBook(string bookId) {
    auto it = find(issuedBookIds.begin(), issuedBookIds.end(), bookId);
    if (it != issuedBookIds.end()) {
        issuedBookIds.erase(it);
    }
}

vector<string> Student::getIssuedBooks() const {
    return issuedBookIds;
}

void Student::displayInfo() const {
    User::displayInfo();
    cout << "Credits: " << credits << endl;
    cout << "Active Reservations: " << reservationIds.size() << endl;
    cout << "Books Issued: " << issuedBookIds.size() << endl;
}
