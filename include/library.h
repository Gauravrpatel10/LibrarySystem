#ifndef LIBRARY_H
#define LIBRARY_H

// #include <vector>
// #include "../data_structures/bst.h"
#include <string>
#include "admin.h"
#include "Book.h"
#include "User.h"
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

class Library
{
private:
    // vector<Book> books;
    // vector<User> users;
    // BST<Book> books;
    // BST<User> users;
    unordered_map<string, Admin> admins;      // to store addmin's data
    unordered_map<int, Book> bookbyId;        // to store book data for searching book by id
    unordered_map<int, User> userbyId;        // to store user data for searching user by id
    unordered_map<int, int> bookIssuedByUser; // to store user and book id when user issued book

    map<string, Book> bookbyTitle;
    map<string, User> userbyName;

public:
    // for books
    void addBook(const Book &book);
    void displayAllBooks() const;
    Book *searchBookByIdMutable(int id);
    void searchBookByTitle(const string &title) const;
    void issueBook(int bookid);
    void returnBook(int bookid);
    void displayIssuedBooksWithUser() const;
    // for users
    void addUser(const User &user);
    void displayAllUser() const;
    User *searchUserByIdMutable(int id);
    const User *searchUserById(int id) const;
    // for admins
    bool authenticateAdmin(const string &id, const string &password);
    void addAdmin(const Admin &admin);
    string searchAdminNameById(const string &id) const;
    // for file i/0
    void loadBooksFromFile(const string &filename);
    void saveBooksToFile(const string &filename) const;

    void loadAdminFromFile(const string &filename);
    void saveAdminsToFile(const string &filename) const;

    void loadIssuedFromFile(const string &fname);
    void saveIssuedToFile(const string &fname) const;

    void loadUsersFromFile(const string &filename);
    void saveUsersToFile(const string &filename) const;
    
};

#endif // LIBRARY_H
