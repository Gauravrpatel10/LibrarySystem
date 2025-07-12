#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
using namespace std;

class Book
{
private:
    int id;
    string title;
    string author;
    bool issued;

public:
    Book();
    Book(int id, string title, string author);
    Book(int id, string title, string author,bool issued);

    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    bool isIssued() const;

    void issueBook();
    void returnBook();
    void display() const;

    bool operator<(const Book &other) const
    {
        return id < other.id;
    }
};

#endif
