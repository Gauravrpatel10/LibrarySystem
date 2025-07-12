#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
class Admin
{
private:
    string id;
    string name;
    string password;

public:
    Admin() : id("0"), name("") , password("") {};
    Admin(string id, string name, string password) : id(id), name(name), password(password) {}

    string getId() const { return id; };
    string getName() const { return name; };
    string getPassword() const { return password; };
    void display() const
    {
        cout << setw(5) << id 
             << setw(30) << name << endl;
    }
};
#endif