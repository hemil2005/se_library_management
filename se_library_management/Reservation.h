#pragma once
#include <string>
#include <ctime>
using namespace std;

class Reservation {
private:
    string reservationId;
    string studentId;
    string bookId;
    time_t reservationDate;
    time_t expiryDate;
    bool isActive;

public:
    Reservation();
    Reservation(string reservationId, string studentId, string bookId);
    
    string getReservationId() const;
    string getStudentId() const;
    string getBookId() const;
    time_t getReservationDate() const;
    time_t getExpiryDate() const;
    bool getIsActive() const;
    
    bool isExpired() const;
    void cancelReservation();
    void fulfillReservation();
    
    int getDaysRemaining() const;
    
    void displayInfo() const;
};
