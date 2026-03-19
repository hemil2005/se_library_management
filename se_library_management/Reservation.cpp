#include "Reservation.h"
#include <iostream>

Reservation::Reservation() {
    reservationId = "";
    studentId = "";
    bookId = "";
    reservationDate = time(0);
    expiryDate = reservationDate + (3 * 24 * 60 * 60);
    isActive = true;
}

Reservation::Reservation(string reservationId, string studentId, string bookId) {
    this->reservationId = reservationId;
    this->studentId = studentId;
    this->bookId = bookId;
    reservationDate = time(0);
    expiryDate = reservationDate + (3 * 24 * 60 * 60);
    isActive = true;
}

string Reservation::getReservationId() const {
    return reservationId;
}

string Reservation::getStudentId() const {
    return studentId;
}

string Reservation::getBookId() const {
    return bookId;
}

time_t Reservation::getReservationDate() const {
    return reservationDate;
}

time_t Reservation::getExpiryDate() const {
    return expiryDate;
}

bool Reservation::getIsActive() const {
    return isActive;
}

bool Reservation::isExpired() const {
    time_t currentTime = time(0);
    return (currentTime >= expiryDate) || !isActive;
}

void Reservation::cancelReservation() {
    isActive = false;
}

void Reservation::fulfillReservation() {
    isActive = false;
}

int Reservation::getDaysRemaining() const {
    if (!isActive) return 0;
    
    time_t currentTime = time(0);
    double secondsRemaining = difftime(expiryDate, currentTime);
    
    if (secondsRemaining < 0) return 0;
    
    return (int)(secondsRemaining / (24 * 60 * 60)) + 1;
}

void Reservation::displayInfo() const {
    cout << "Reservation ID: " << reservationId << endl;
    cout << "Student ID: " << studentId << endl;
    cout << "Book ID: " << bookId << endl;
    cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    cout << "Days Remaining: " << getDaysRemaining() << endl;
}
