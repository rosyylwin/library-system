/*******************************************************
Name      :  Rosy Lwin
Class     :  CSC 2312 Section 002
PRoject   :  Project 1 Library Managment
Due Date  :  11/22/2025
*******************************************************/

#include <iostream>
#include <memory>
#include <limits>
#include "Library.h"
#include "Book.h"
#include "User.h"
#include "BorrowRecord.h"

using namespace std;

// Helper function
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() {
    cout << "Library System Menu" << std::endl;
    cout << "1. Add Book" << std::endl;
    cout << "2. Remove Book" << std::endl;
    cout << "3. Search Book" << std::endl;
    cout << "4. Add user" << std::endl;
    cout << "5. Remove User" << std::endl;
    cout << "6. Search User" << std::endl;
    cout << "7. Borrow Book" << std::endl;
    cout << "8. Return Book" << std::endl;
    cout << "9. Display All Books" << std::endl;
    cout << "10. Display All Users" << std::endl;
    cout << "11. Display All Records" << std::endl;
    cout << "12. Show Report" << std::endl;
    cout << "13. Save and Exit" << std::endl;
    cout << "Enter choice: ";
}

int main() {
    Library lib;

    // Load files
    lib.loadBooks("books.csv");
    lib.loadUsers("users.csv");
    lib.loadRecords("records.csv");

    cout << "Library System Initialized" << std::endl;

    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "invalid input. Try again" << std::endl;
            continue;
        }

        // EXIT
        if (choice == 13) {
            cout << "Saving data..." << std::endl;
            lib.saveBooks("books.csv");
            lib.saveUsers("users.csv");
            lib.saveRecords("records.csv");
            break;
        }
        switch(choice) {
            // Add Book
            case 1: {
                string isbn, title, author;
                int year, copies;

                clearInput();
                cout << "Enter ISBN: ";
                getline(cin, isbn);
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter publication year: ";
                cin >> year;
                cout << "Enter total copies: ";
                cin >> copies;

                Book b(isbn, title, author, year, copies);
                if (lib.addBook(b))
                    cout << "Book added successfully." << std::endl;
                else
                    cout << "A book with this ISBN already exists." << std::endl;
                break;
            }
            // Remove Book
            case 2: {
                clearInput();
                string isbn;
                cout << "Enter ISBN to remove: ";
                getline(cin, isbn);

                if (lib.removeBook(isbn))
                    cout << "Book removed." << std::endl;
                else
                    cout << "Book not found." << std::endl;
                break;
            }

            // Search Book
            case 3: {
                clearInput();
                string isbn;
                cout << "Enter ISBN to search: ";
                getline(cin, isbn);

                Book* b = lib.searchBook(isbn);
                if(b)
                    b->display(cout);
                else
                    cout << "Book not found." << std::endl;
                break;
            }

            // Add User
            case 4: {
                clearInput();
                string id, name;
                int type;

                cout << "Enter user ID: ";
                getline(cin, id);
                cout << "Enter name: ";
                getline(cin, name);

                cout << "User type (1=Student, 2=Teacher, 3=Other): ";
                cin >> type;

                unique_ptr<User> u;

                if (type == 1) {
                    clearInput();
                    string major;
                    cout << "Enter major: ";
                    getline(cin, major);
                    u = make_unique<Student> (id, name, major);
                }
                else if (type == 2) {
                    clearInput();
                    string dept;
                    cout << "Enter department: ";
                    getline(cin, dept);
                    u = make_unique<Teacher>(id, name, dept);
                }
                else {
                    u = make_unique<User>(id, name, UserType::OTHER);
                }

                if (lib.addUser(std::move(u)))
                    cout << "User added." << std::endl;
                else
                    cout << "User with this ID already exists." << std::endl;
                break;
            }
            // Remove User
            case 5: {
                clearInput();
                string id;
                cout << "Enter user ID to remove: ";
                getline(cin, id);

                if (lib.removeUser(id))
                    cout << "User removed." << std::endl;
                else
                    cout << "User not found." << std::endl;
                break;
            }
            // Search User
            case 6: {
                clearInput();
                string id;
                cout << "Enter user ID: ";
                getline(cin, id);

                User* u = lib.searchUser(id);
                if (u)
                    u->display(cout);
                else
                    cout << "User not found." << std::endl;
                break;
            }
            // Borrow Book
            case 7 : {
                clearInput();
                string id, isbn;
                int by, bm, bd, dy, dm, dd;

                cout << "Enter user ID: ";
                getline(cin, id);

                cout << "Enter book ISBN: ";
                getline(cin, isbn);

                cout << "Enter borrowed date (Y M D): ";
                cin >> by >> bm >> bd;

                cout << "Enter due date (Y M D): ";
                cin >> dy >> dm >> dd;

                if (lib.borrowBook(id, isbn, by, bm, bd, dy,dm, dd))
                    cout << "Borrow successful" << std::endl;
                else
                    cout << "Borrow failed." << std::endl;
                break;
            }
            // Return Book
            case 8: {
                clearInput();
                string recID;
                double fee;
                int ry, rm, rd;

                cout << "Enter record ID: ";
                getline(cin, recID);

                cout << "Enter return date (Y M D): ";
                cin >> ry >> rm >> rd;

                cout << "Late fee per day: ";
                cin >> fee;

                if (lib.returnBook(recID, ry, rm, rd, fee))
                    cout << "Return successful." << std::endl;
                else
                    cout << "Return failed" << std::endl;
                break;
            }
            // Display all books
            case 9:
                lib.displayAllBooks();
                break;

            // Display all users
            case 10:
                lib.displayAllUsers();
                break;

            // Display all records
            case 11:
                lib.displayAllRecords();
                break;

            // Reports
            case 12: {
                cout << "Total Books: " << lib.getTotalBooks() << std::endl;
                cout << "Total Users: " << lib.getTotalUsers() << std::endl;
                cout << "Borrowed Books: " << lib.getBorrowedCount() << std::endl;
                break;
            }
            default:
            cout << "Invalid choice." << std::endl;
        }
    }
    return 0;
}

