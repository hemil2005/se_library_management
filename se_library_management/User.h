#pragma once
#include <string>
using namespace std;

class User {
protected:
    string userId;
    string name;
    string password;
    string userType;

public:
    User();
    User(string userId, string name, string password, string userType);
    
    string getUserId() const;
    string getName() const;
    string getUserType() const;
    bool validatePassword(string pwd) const;
    
    void setName(string name);
    void setPassword(string password);
    
    virtual void displayInfo() const;
};
