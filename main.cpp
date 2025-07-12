#include "include/library.h"
#include <iostream>
using namespace std;
void handleBookIssue(Library &l);
void handleBookReturn(Library &l);
void handleSearchBookByTitle(Library &l);
void handleShow_issued_book(Library &l);



int main()
{
    Library library;
    library.loadBooksFromFile("books.txt");
    library.loadUsersFromFile("users.txt");
    library.loadAdminFromFile("admins.txt");
    library.loadIssuedFromFile("issued.txt");

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
                cout << "Admin login successful. Welcome, " << AName << "\n";

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
                    cout << "10. Show Issued Books whith user\n";
                    cout << "11. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    if (adminChoice == 11) // 10. Logout
                    {
                        cout << "Logging out from admin account sucssefully.\n";
                        break;
                    }

                    switch (adminChoice)
                    {
                    case 1: // 1. Add Book
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
                    case 2: // 2. Add User
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
                    case 3: // 3. To issue book
                        handleBookIssue(library);
                        break;
                    case 4: // 4. To return book
                        handleBookReturn(library);
                        break;
                    case 5: // 5. Search book by title
                        handleSearchBookByTitle(library);
                        break;
                    case 6: // 6. Search Book by Title
                    {
                        string title;
                        cout << "Enter Book Title to search: ";
                        cin.ignore();
                        getline(cin, title);
                        library.searchBookByTitle(title);
                        break;
                    }
                    case 7: // 7. Search User by ID
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
                    case 8: // 8. Display All Books
                        library.displayAllBooks();
                        break;
                    case 9: // 9. Display All Users
                        library.displayAllUser();
                        break;
                    case 10: // 9. Display All issued book by whom they are issued to
                        library.displayIssuedBooksWithUser();
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
                    handleSearchBookByTitle(library);
                    break;

                case 2:
                    handleBookIssue(library);
                    break;

                case 3:
                    handleBookReturn(library);
                    break;
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
    library.saveUsersToFile("users.txt");
    library.saveAdminsToFile("admins.txt");
    library.saveBooksToFile("books.txt");
    library.saveIssuedToFile("issued.txt");
    return 0;
} // end main
//=======================================================================================================================================
// Deaclaration of handler function
void handleBookIssue(Library &l)
{
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;
    l.issueBook(id);
};
void handleBookReturn(Library &l)
{
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;
    l.returnBook(id);
};
void handleSearchBookByTitle(Library &l)
{
    string title;
    cout << "Enter Book Title to search: ";
    cin.ignore();
    getline(cin, title);
    l.searchBookByTitle(title);
};