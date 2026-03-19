#pragma once
#include "User.h"

class Admin : public User {
public:
    Admin();
    Admin(string userId, string name, string password);
    
    void displayInfo() const override;
};
