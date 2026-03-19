#pragma once
#include "User.h"
#include <vector>

class Teacher : public User {
private:
    string department;
    vector<string> issuedBookIds;

public:
    Teacher();
    Teacher(string userId, string name, string password, string department);
    
    string getDepartment() const;
    void setDepartment(string dept);
    
    void addIssuedBook(string bookId);
    void removeIssuedBook(string bookId);
    vector<string> getIssuedBooks() const;
    
    void displayInfo() const override;
};
