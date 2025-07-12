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

void Library::addBook(const Book &book) {
    bookbyId[book.getId()] = book;
    bookbyTitle[book.getTitle()] = book;
}

void Library::displayAllBooks() const {
    cout<<left//this is for top line when we display all book
        <<setw(5)<<"Id"
        <<setw(40)<<"Title"
        <<setw(30)<<"Author"
        <<"Issued"<<endl;
    cout<<string(100,'=')<<endl;// new line made by (====)

    for (const auto &pair : bookbyTitle) {
        pair.second.display();
    }
}

Book *Library::searchBookByIdMutable(int id) {
    auto it = bookbyId.find(id);
    return (it != bookbyId.end()) ? &it->second : nullptr;
}

void Library::searchBookByTitle(const string &title) const {
    auto it = bookbyTitle.find(title);
    if (it != bookbyTitle.end())
        it->second.display();
    else
        cout << "Book not found.\n";
}

void Library::issueBook(int bookId) {
    auto it = bookbyId.find(bookId);
    if (it != bookbyId.end()) {
        if (it->second.isIssued())
            cout << "Book is already issued.\n";
        else {
            int userId;
            string userName;
            cout<<"Enter your Id :";
            cin>>userId;
            cin.ignore();
            cout<<"Enter your Name :";
            getline(cin,userName);

            if(userbyId.find(userId) == userbyId.end())//if user is new so creat new user
            {
                addUser(User(userId,userName));
            }

            it->second.issueBook();
            bookbyTitle[it->second.getTitle()] = it->second;
            bookIssuedByUser[bookId] = userId;
            cout << "Book issued successfully.\n";
        }
    } else {
        cout << "Book not found.\n";
    }
}

void Library::returnBook(int bookId) {
    auto it = bookbyId.find(bookId);
    if (it != bookbyId.end()) {
        if (it->second.isIssued()) {

            int userId = bookIssuedByUser[bookId];
            it->second.returnBook();
            bookbyTitle[it->second.getTitle()] = it->second;
            bookIssuedByUser.erase(bookId);

            bool has_book_user = false;
            for(const auto& pair : bookIssuedByUser)// his is to chacke is user by userid has another book issued
            {
                if(pair.second == userId)
                {
                    has_book_user = true;
                    break;
                }
            }

            if(!has_book_user)
            {
                string name = userbyId[userId].getName();//this is for erasing from bookByTitle
                bookbyId.erase(userId);
                bookbyTitle.erase(name);

            }

            cout << "Book returned successfully.\n";
        } else {
            cout << "Book was not issued.\n";
        }
    } else {
        cout << "Book not found.\n";
    }
}

//
// ===============================
// ||    USER'S FUNCTIONS       ||
// ===============================
//

void Library::addUser(const User &user) {
    userbyId[user.getId()] = user;
    userbyTitle[user.getName()] = user;
}

void Library::displayAllUser() const {
    cout<<left
        <<setw(5)<<"Id"
        <<setw(30)<<"Name"<<endl;
    cout<<string(100,'=')<<endl;
    for (const auto &pair : userbyTitle) {
        pair.second.display();
    }
}

const User *Library::searchUserById(int id) const {
    auto it = userbyId.find(id);
    return (it != userbyId.end()) ? &it->second : nullptr;
}

User *Library::searchUserByIdMutable(int id) {
    auto it = userbyId.find(id);
    return (it != userbyId.end()) ? &it->second : nullptr;
}

//
// ===============================
// ||   ADMIN'S FUNCTIONS       ||
// ===============================
//

void Library::addAdmin(const Admin &admin) {
    admins[admin.getId()] = admin;
}

bool Library::authenticateAdmin(const string &id, const string &password) {
    auto it = admins.find(id);
    return (it != admins.end() && it->second.getPassword() == password);
}

string Library::searchAdminNameById(const string &id) const {
    auto it = admins.find(id);
    return (it != admins.end()) ? it->second.getName() : "admin_does_not_exist";
}
void Library::loadAdminFromFile(const string &filename) {
    fstream ln(filename);
    if (!ln) {
        cout << "No Admin file found.\n";
        return;
    }

    string line;
    while (getline(ln, line)) {
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
void Library::saveAdminsToFile(const string &filename) const {
    ofstream ln(filename);
    if (!ln) {
        cout << "Can't open book file for writing.\n";
        return;
    }

    for (const auto &pair : admins) {
        ln << pair.second.getId() << ","
           << pair.second.getName() << ","
           << pair.second.getPassword() << ",\n";
    }

    ln.close();
}



//
// ================================
// || FILE I/O FUNCTIONS (BOOKS) ||
// ================================
//

void Library::loadBooksFromFile(const string &filename) {
    fstream ln(filename);
    if (!ln) {
        cout << "No book file found.\n";
        return;
    }

    string line;
    while (getline(ln, line)) {
        string sid, title, author, issueds;
        stringstream str(line);
        //take input from file and then store in strings
        getline(str, sid, ',');
        getline(str, title, ',');
        getline(str, author, ',');
        getline(str, issueds, ',');

        int id = stoi(sid);//conver string to int
        bool issued = (issueds == "1");

        Book book(id, title, author, issued);//create new book object 
        addBook(book);
    }
    ln.close();
}

void Library::saveBooksToFile(const string &filename) const {
    ofstream ln(filename);
    if (!ln) {
        cout << "Can't open book file for writing.\n";
        return;
    }

    for (const auto &pair : bookbyId) {
        ln << pair.second.getId() << ","
           << pair.second.getTitle() << ","
           << pair.second.getAuthor() << ","
           << pair.second.isIssued() << ",\n";
    }

    ln.close();
}
