#include "User.h"
#include <iostream>

User::User() {
    userId = "";
    name = "";
    password = "";
    userType = "";
}

User::User(string userId, string name, string password, string userType) {
    this->userId = userId;
    this->name = name;
    this->password = password;
    this->userType = userType;
}

string User::getUserId() const {
    return userId;
}

string User::getName() const {
    return name;
}

string User::getUserType() const {
    return userType;
}

bool User::validatePassword(string pwd) const {
    return password == pwd;
}

void User::setName(string name) {
    this->name = name;
}

void User::setPassword(string password) {
    this->password = password;
}

void User::displayInfo() const {
    cout << "User ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "User Type: " << userType << endl;
}
