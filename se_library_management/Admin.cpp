#include "Admin.h"
#include <iostream>

Admin::Admin() : User() {
    userType = "Admin";
}

Admin::Admin(string userId, string name, string password)
    : User(userId, name, password, "Admin") {
}

void Admin::displayInfo() const {
    User::displayInfo();
    cout << "Administrator Account" << endl;
}
