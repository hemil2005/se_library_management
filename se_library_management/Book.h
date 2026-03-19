#pragma once
#include <string>
using namespace std;

class Book {
private:
    string bookId;
    string title;
    string author;
    string isbn;
    int totalCopies;
    int availableCopies;
    string category;

public:
    Book();
    Book(string bookId, string title, string author, string isbn, int totalCopies, string category);
    
    string getBookId() const;
    string getTitle() const;
    string getAuthor() const;
    string getIsbn() const;
    int getTotalCopies() const;
    int getAvailableCopies() const;
    string getCategory() const;
    
    void setTitle(string title);
    void setAuthor(string author);
    void setTotalCopies(int copies);
    void setCategory(string category);
    
    bool isAvailable() const;
    bool issueBook();
    bool returnBook();
    
    void displayInfo() const;
};
