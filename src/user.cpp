#include "../include/User.h"
#include <iostream>
#include <iomanip>
using namespace std;
User::User() : id(0), name("Unknown") {}
User::User(int id, string name)
    : id(id), name(name) {}

int User::getId() const
{
    return id;
};

string User::getName() const
{
    return name;
};

void User::display() const
{
    cout << setw(5)<< id
         << setw(30)<< name << endl;
};