#include "../include/library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

//
// ==============================
// ||    BOOK'S FUNCTIONS      ||
// ==============================
//

void Library::addBook(const Book &book)
{
    bookbyId[book.getId()] = book;
    bookbyTitle[book.getTitle()] = book;
}

void Library::displayAllBooks() const
{
    cout << left // this is for top line when we display all book
         << setw(10) << "Id"
         << setw(35) << "Title"
         << setw(30) << "Author"
         << "Issued" << endl;
    cout << string(100, '=') << endl; // new line made by (====)

    for (const auto &pair : bookbyTitle)
    {
        pair.second.display();
    }
}

Book *Library::searchBookByIdMutable(int id)
{
    auto it = bookbyId.find(id);
    return (it != bookbyId.end()) ? &it->second : nullptr;
}

void Library::searchBookByTitle(const string &title) const
{
    auto it = bookbyTitle.find(title);
    if (it != bookbyTitle.end())
        it->second.display();
    else
        cout << "Book not found.\n";
}

void Library::issueBook(int bookId)
{
    auto it = bookbyId.find(bookId);
    if (it != bookbyId.end())
    {
        if (it->second.isIssued())
            cout << "Book is already issued.\n";
        else
        {
            int userId;
            string userName;
            cout << "Enter your Id :";
            cin >> userId;
            cin.ignore();
            cout << "Enter your Name :";
            getline(cin, userName);

            if (userbyId.find(userId) == userbyId.end()) // if user is new so creat new user
            {
                addUser(User(userId, userName));
            }

            it->second.issueBook();
            bookbyTitle[it->second.getTitle()] = it->second; // because (it) can only change
            bookIssuedByUser[bookId] = userId;
            cout << "Book issued successfully.\n";
        }
    }
    else
    {
        cout << "Book not found.\n";
    }
}

void Library::returnBook(int bookId)
{
    auto it = bookbyId.find(bookId);
    if (it != bookbyId.end())
    {
        if (it->second.isIssued())
        {

            int userId = bookIssuedByUser[bookId];
            it->second.returnBook();
            bookbyTitle[it->second.getTitle()] = it->second;
            bookIssuedByUser.erase(bookId);

            bool has_book_user = false;
            for (const auto &pair : bookIssuedByUser) // his is to chacke is user by userid has another book issued
            {
                if (pair.second == userId)
                {
                    has_book_user = true;
                    break;
                }
            }

            if (!has_book_user)
            {
                string name = userbyId[userId].getName(); // this is for erasing from bookByTitle
                bookbyId.erase(userId);
                bookbyTitle.erase(name);
            }

            cout << "Book returned successfully.\n";
        }
        else
        {
            cout << "Book was not issued.\n";
        }
    }
    else
    {
        cout << "Book not found.\n";
    }
}
void Library::displayIssuedBooksWithUser() const
{
    cout << left
         << setw(10) << "Book Id"
         << setw(35) << "Title"
         << setw(30) << "Name"
         << "Issued To [User Id | Name]" << endl;
    cout << string(100, '=') << endl;

    for (const auto &pair : bookIssuedByUser)
    {
        int bookid = pair.first;
        int userid = pair.second;

        const Book &b = bookbyId.at(bookid);
        const User &u = userbyId.at(userid);
        b.display();
        cout << u.getId() << " | " << u.getName();
    }

    if (bookIssuedByUser.empty())
        cout << "No book is corrently issued by user.\n";
}

//
// ===============================
// ||    USER'S FUNCTIONS       ||
// ===============================
//

void Library::addUser(const User &user)
{
    userbyId[user.getId()] = user;
    userbyName[user.getName()] = user;
}

void Library::displayAllUser() const
{
    cout << left
         << setw(5) << "Id"
         << setw(30) << "Name" << endl;
    cout << string(100, '=') << endl;
    for (const auto &pair : userbyName)
    {
        pair.second.display();
    }
}

const User *Library::searchUserById(int id) const
{
    auto it = userbyId.find(id);
    return (it != userbyId.end()) ? &it->second : nullptr;
}

User *Library::searchUserByIdMutable(int id)
{
    auto it = userbyId.find(id);
    return (it != userbyId.end()) ? &it->second : nullptr;
}

//
// ===============================
// ||   ADMIN'S FUNCTIONS       ||
// ===============================
//

void Library::addAdmin(const Admin &admin)
{
    admins[admin.getId()] = admin;
}

bool Library::authenticateAdmin(const string &id, const string &password)
{
    auto it = admins.find(id);
    return (it != admins.end() && it->second.getPassword() == password);
}

string Library::searchAdminNameById(const string &id) const
{
    auto it = admins.find(id);
    return (it != admins.end()) ? it->second.getName() : "admin_does_not_exist";
}

//
// ================================
// || FILE I/O FUNCTIONS (BOOKS) ||
// ================================
//

void Library::loadBooksFromFile(const string &filename)
{
    fstream ln(filename);
    if (!ln)
    {
        cout << "No book file found.\n";
        return;
    }

    string line;
    while (getline(ln, line))
    {
        string sid, title, author, issueds;
        stringstream str(line);
        // take input from file and then store in strings
        getline(str, sid, ',');
        getline(str, title, ',');
        getline(str, author, ',');
        getline(str, issueds, ',');

        int id = stoi(sid); // conver string to int
        bool issued = (issueds == "1");

        Book book(id, title, author, issued); // create new book object
        addBook(book);
    }
    ln.close();
}

void Library::saveBooksToFile(const string &filename) const
{
    ofstream ln(filename);
    if (!ln)
    {
        cout << "Can't open book file for writing.\n";
        return;
    }

    for (const auto &pair : bookbyId)
    {
        ln << pair.second.getId() << ","
           << pair.second.getTitle() << ","
           << pair.second.getAuthor() << ","
           << pair.second.isIssued() << ",\n";
    }

    ln.close();
}
void Library::loadAdminFromFile(const string &filename)
{
    fstream ln(filename);
    if (!ln)
    {
        cout << "No Admin data in file found.\n";
        return;
    }

    string line;
    while (getline(ln, line))
    {
        string id, name, password;
        stringstream str(line);

        getline(str, id, ',');
        getline(str, name, ',');
        getline(str, password, ',');

        Admin Admin(id, name, password);
        addAdmin(Admin);
    }
    ln.close();
}
void Library::saveAdminsToFile(const string &filename) const
{
    ofstream ln(filename);
    if (!ln)
    {
        cout << "Can't open file for writing.\n";
        return;
    }

    for (const auto &pair : admins)
    {
        ln << pair.second.getId() << ","
           << pair.second.getName() << ","
           << pair.second.getPassword() << ",\n";
    }

    ln.close();
}
void Library::loadIssuedFromFile(const string &fname)
{
    fstream ln(fname);
    if (!ln)
    {
        cout << "No book data in file found.\n";
        return;
    }
    string line;
    while (getline(ln, line))
    {
        stringstream str(line);
        string sbid, suid;
        getline(str, sbid, ',');
        getline(str, suid, ',');
        int bookid = stoi(sbid);
        int userid = stoi(suid);

        auto bit = bookbyId.find(bookid);
        auto uit = userbyId.find(userid);

        if (bit != bookbyId.end())
        {
            bit->second.issueBook();
            bookbyTitle[bit->second.getTitle()] = bit->second;
            if (uit != userbyId.end())
            {
                userbyName[uit->second.getName()] = uit->second;
            }
        }
    }
}
void Library::saveIssuedToFile(const string &fname) const
{
    ofstream ln(fname);
    if (!ln)
    {
        cout << "file can't open file for writing.\n";
        return;
    }

    for (const auto &pair : bookIssuedByUser)
    {
        ln << pair.first << "," << pair.second << ",\n";
    }
    ln.close();
}
void Library::loadUsersFromFile(const string &filename)
{
    fstream ln(filename);
    if (!ln)
    {
        cout << "No book file found.\n";
        return;
    }

    string line;
    while (getline(ln, line))
    {
        string sid, name;
        stringstream str(line);
        // take input from file and then store in strings
        getline(str, sid, ',');
        getline(str, name, ',');

        int id = stoi(sid); // conver string to int

        User user(id, name); // create new user object
        addUser(user);
    }
    ln.close();
}
void Library::saveUsersToFile(const string &filename) const
{
    ofstream ln(filename);
    if (!ln)
    {
        cout << "Can't open book file for writing.\n";
        return;
    }

    for (const auto &pair : userbyId)
    {
        ln << pair.second.getId() << ","
           << pair.second.getName() << ",\n";
    }

    ln.close();
}
