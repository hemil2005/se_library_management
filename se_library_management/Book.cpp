#include "Book.h"
#include <iostream>

Book::Book() {
    bookId = "";
    title = "";
    author = "";
    isbn = "";
    totalCopies = 0;
    availableCopies = 0;
    category = "";
}

Book::Book(string bookId, string title, string author, string isbn, int totalCopies, string category) {
    this->bookId = bookId;
    this->title = title;
    this->author = author;
    this->isbn = isbn;
    this->totalCopies = totalCopies;
    this->availableCopies = totalCopies;
    this->category = category;
}

string Book::getBookId() const {
    return bookId;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getIsbn() const {
    return isbn;
}

int Book::getTotalCopies() const {
    return totalCopies;
}

int Book::getAvailableCopies() const {
    return availableCopies;
}

string Book::getCategory() const {
    return category;
}

void Book::setTitle(string title) {
    this->title = title;
}

void Book::setAuthor(string author) {
    this->author = author;
}

void Book::setTotalCopies(int copies) {
    totalCopies = copies;
    if (availableCopies > totalCopies) {
        availableCopies = totalCopies;
    }
}

void Book::setCategory(string category) {
    this->category = category;
}

bool Book::isAvailable() const {
    return availableCopies > 0;
}

bool Book::issueBook() {
    if (availableCopies > 0) {
        availableCopies--;
        return true;
    }
    return false;
}

bool Book::returnBook() {
    if (availableCopies < totalCopies) {
        availableCopies++;
        return true;
    }
    return false;
}

void Book::displayInfo() const {
    cout << "Book ID: " << bookId << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Category: " << category << endl;
    cout << "Available Copies: " << availableCopies << "/" << totalCopies << endl;
}
