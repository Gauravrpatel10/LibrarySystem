#include "include/library.h"
#include <iostream>
using namespace std;

int main()
{
    Library library;
    library.loadBooksFromFile("books.txt");
    library.loadAdminFromFile("admins.txt");

    // Add sample admins
    library.addAdmin(Admin("202301197", "Gaurav", "gaurav@10"));

    int mainChoice;

    while (true)
    {
        cout << "\n==== Welcome to Library System ====\n";
        cout << "1. Admin Login\n";
        cout << "2. User Access\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (mainChoice == 3)
        {
            cout << "Exiting library system. Goodbye!\n";
            break;
        }

        switch (mainChoice)
        {
        case 1: // Admin Menu
        {
            string id, pass;
            cout << "Enter admin ID: ";
            cin >> id;
            cout << "Enter password: ";
            cin >> pass;

            if (library.authenticateAdmin(id, pass))
            {
                string AName = library.searchAdminNameById(id);
                cout << "Admin login successful. Welcome, " <<AName<< "\n";

                int adminChoice;
                while (true)
                {
                    cout << "\n--- Admin Menu ---\n";
                    cout << "1. Add Book\n";
                    cout << "2. Add User\n";
                    cout << "3. Add Admin\n";
                    cout << "4. Issue Book\n";
                    cout << "5. Return Book\n";
                    cout << "6. Search Book by Title\n";
                    cout << "7. Search User by ID\n";
                    cout << "8. Display All Books\n";
                    cout << "9. Display All Users\n";
                    cout << "10. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    if (adminChoice == 10)//10. Logout
                    {
                        cout << "Logging out from admin account sucssefully.\n";
                        break;
                    }

                    switch (adminChoice)
                    {
                    case 1://1. Add Book
                    {
                        int id;
                        string title, author;
                        cout << "Enter Book ID, Title, and Author:\n";
                        cin >> id;
                        cin.ignore();
                        getline(cin, title);
                        getline(cin, author);
                        library.addBook(Book(id, title, author));
                        break;
                    }
                    case 2://2. Add User
                    {
                        int id;
                        string name;
                        cout << "Enter User ID and Name:\n";
                        cin >> id;
                        cin.ignore();
                        getline(cin, name);
                        library.addUser(User(id, name));
                        break;
                    }
                    case 3://3. Add admin
                    {
                        string id;
                        string name;
                        string password;
                        cout << "Enter admin ID Name and password:\n";
                        cin >> id;
                        cin.ignore();
                        getline(cin, name);
                        getline(cin, password);
                        library.addAdmin(Admin(id, name,password));
                        cout<<"admin added sucssesfully.\n";
                        break;
                    }
                    case 4://4. Issue Book
                    {
                        int id;
                        cout << "Enter Book ID to issue: ";
                        cin >> id;
                        library.issueBook(id);
                        break;
                    }
                    case 5://5. Return Book
                    {
                        int id;
                        cout << "Enter Book ID to return: ";
                        cin >> id;
                        library.returnBook(id);
                        break;
                    }
                    case 6://6. Search Book by Title
                    {
                        string title;
                        cout << "Enter Book Title to search: ";
                        cin.ignore();
                        getline(cin, title);
                        library.searchBookByTitle(title);
                        break;
                    }
                    case 7://7. Search User by ID
                    {
                        int id;
                        cout << "Enter User ID to search: ";
                        cin >> id;
                        const User *u = library.searchUserById(id);
                        if (u)
                            u->display();
                        else
                            cout << "User not found.\n";
                        break;
                    }
                    case 8://8. Display All Books
                        library.displayAllBooks();
                        break;
                    case 9://9. Display All Users
                        library.displayAllUser();
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                }
            }
            else
            {
                cout << "Access denied. Invalid admin id or password.\n";
            }
            break;
        }

        case 2: // User Menu
        {
            int userChoice;
            while (true)
            {
                cout << "\n--- User Menu ---\n";
                cout << "1. Search Book by Title\n";
                cout << "2. Issue Book by ID\n";
                cout << "3. Return Book by ID\n";
                cout << "4. Display All Books\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> userChoice;

                if (userChoice == 5)
                {
                    cout << "Returning to main menu.\n";
                    break;
                }

                switch (userChoice)
                {
                case 1:
                {
                    string title;
                    cout << "Enter Book Title to search: ";
                    cin.ignore();
                    getline(cin, title);
                    library.searchBookByTitle(title);
                    break;
                }
                case 2:
                {
                    int id;
                    cout << "Enter Book ID to issue: ";
                    cin >> id;
                    library.issueBook(id);
                    break;
                }
                case 3:
                {
                    int id;
                    cout << "Enter Book ID to return: ";
                    cin >> id;
                    library.returnBook(id);
                    break;
                }
                case 4:
                    library.displayAllBooks();
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            }
            break;
        }

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    library.saveAdminsToFile("admins.txt");
    library.saveBooksToFile("books.txt");
    return 0;
}
