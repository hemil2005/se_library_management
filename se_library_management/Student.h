#pragma once
#include "User.h"
#include <vector>

class Student : public User {
private:
    int credits;
    vector<string> reservationIds;
    vector<string> issuedBookIds;

public:
    Student();
    Student(string userId, string name, string password);
    
    int getCredits() const;
    void deductCredits(int amount);
    void addCredits(int amount);
    
    void addReservation(string reservationId);
    void removeReservation(string reservationId);
    vector<string> getReservations() const;
    
    void addIssuedBook(string bookId);
    void removeIssuedBook(string bookId);
    vector<string> getIssuedBooks() const;
    
    void displayInfo() const override;
};
