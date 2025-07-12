#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User
{
private:
    int id;
    string name;

public:
    User();
    User(int id, string name);

    int getId() const;
    string getName() const;

    void display() const;

    bool operator<(const User &other) const
    {
        return id < other.id;
    }
};

#endif
