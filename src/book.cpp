#include "../include/Book.h"
#include <iostream>
#include <iomanip>
using namespace std;

Book::Book() : id(0), title(""), author(""), issued(false) {}
Book::Book(int id, string title, string author)
    : id(id), title(title), author(author), issued(false) {}
Book::Book(int id, string title, string author, bool issued)
    : id(id), title(title), author(author), issued(issued) {}

int Book::getId() const
{
    return id;
};

string Book::getTitle() const
{
    return title;
};

string Book::getAuthor() const
{
    return author;
};

bool Book::isIssued() const
{
    return issued;
};

void Book::issueBook()
{
    issued = true;
};

void Book::returnBook()
{
    issued = false;
};

void Book::display() const
{
    cout << left
         << setw(10) << id
         << setw(35) << title
         << setw(30) << author
         << (issued ? "Yes" : "No") << endl;
};