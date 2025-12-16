#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "Book.h"
#include "User.h"
#include "BorrowRecord.h"

/*
 * Library.h
 * Declares the Library class, which manages all high-level operations of the library system.
 *
 * Responsibilities:
 *  - Book management (add, remove, search)
 *  - User management (add, remove, search)
 *  - Borrow/return system using BorrowRecord
 *  - Late fee processing
 *  - Reporting functions
 *
 * The Library class stores:
 *  - A list of Book objects
 *  - A list of polymorphic User objects
 *  - A list of BorrowRecord log enteries
*/

class Library {
private:
    std::vector<Book> books;
    std::vector<std::unique_ptr<User>> users;
    std::vector<BorrowRecord> records;

    Book* findBookByISBN(const std::string& isbn);
    User* findUserByID(const std::string& id);

public:
    Library();

    // Book Management
    bool addBook(const Book& book);
    bool removeBook(const std::string& isbn);
    Book* searchBook(const std::string& isbn);

    // User Management
    bool addUser(std::unique_ptr<User> user);
    bool removeUser(const std::string& id);
    User* searchUser(const std::string& id);

    // Borrow / Return
    bool borrowBook(const std::string& userID, const std::string& isbn, int by, int bm, int bd, int dy, int dm, int dd);
    bool returnBook(const std::string& recordID, int ry, int rm, int rd, double lateFeePerDay);

    // getters
    int getTotalBooks() const;
    int getTotalUsers() const;
    int getBorrowedCount() const;
    int getAvailableCopies(const std::string& isbn) const;

    // Reports
    void displayAllBooks() const;
    void displayAllUsers() const;
    void displayAllRecords() const;

    // File I/O
    bool loadBooks(const std::string& filename);
    bool saveBooks(const std::string& filename) const;

    bool loadUsers(const std::string& filename);
    bool saveUsers(const std::string& filename) const;

    bool loadRecords(const std::string& filename);
    bool saveRecords(const std::string& filename) const;
};

#endif