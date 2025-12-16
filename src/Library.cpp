#include "Library.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>

/*
 * Library.cpp
 * Implements the Library class from Library.h
 *
 * Contains logic for:
 *  - Searching, adding, and removing books
 *  - Managing users through polymorphic unique_ptr<User>
 *  - Creating and updating BorrowRecord objects
 *  - Safe borrowing and returning of books
 *  - Late fee calculations and reporting
 *
 * Ensures the system maintains consistent state and prevents invalid operations.
 */

// Private  helpers
Book* Library::findBookByISBN(const std::string& isbn) {
    for (auto& b : books) {
        if (b.getISBN() == isbn)
            return &b;
    }
    return nullptr;
}

User* Library::findUserByID(const std::string& id) {
    for (auto& u : users) {
        if (u->getID() == id)
            return u.get();
    }
    return nullptr;
}


// Constructor
Library::Library()
    : books(), users(), records() {}


// Book management
bool Library::addBook(const Book& book) {
    if (findBookByISBN(book.getISBN()))
        return false;

    books.push_back(book);
    return true;
}

bool Library::removeBook(const std::string& isbn) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getISBN() == isbn) {
            books.erase(it);
            return true;
        }
    }
    return false;
}

Book* Library::searchBook(const std::string& isbn) {
    return findBookByISBN(isbn);
}

// User management
bool Library::addUser(std::unique_ptr<User> user) {
    if (findUserByID(user->getID()))
        return false;

    users.push_back(std::move(user));
    return true;
}

bool Library::removeUser(const std::string& id) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getID() == id) {
            users.erase(it);
            return true;
        }
    }
    return false;
}

User* Library::searchUser(const std::string& id) {
    return findUserByID(id);
}

// Borrow a book
bool Library::borrowBook(const std::string& userID, const std::string& isbn,
                         int by, int bm, int bd, int dy, int dm, int dd)
{
    User* user = findUserByID(userID);
    if (!user) return false;

    Book* book = findBookByISBN(isbn);
    if (!book) return false;

    if (!book->borrowOne()) return false;

    // Create borrow record ID
    std::string recID = "REC" + std::to_string(records.size() + 1);

    BorrowRecord rec(recID, userID, isbn, by, bm, bd, dy, dm, dd);
    records.push_back(rec);
    return true;
}

// Return a book
bool Library::returnBook(const std::string& recordID,
                         int ry, int rm, int rd,
                         double lateFeePerDay)
{
    for (auto& rec : records) {
        if (rec.getRecordID() == recordID) {

            if (rec.isReturned())
                return false;

            rec.markReturned(ry, rm, rd);

            Book* b = findBookByISBN(rec.getISBN());
            if (b)
                b->returnOne();

            // Late fees
            int late = rec.daysLate();
            if (late > 0) {
                User* u = findUserByID(rec.getUserID());
                if (u)
                    u->addFees(late * lateFeePerDay);
            }

            return true;
        }
    }
    return false;
}

// Reporting
int Library::getTotalBooks() const {
    return books.size();
}

int Library::getTotalUsers() const {
    return users.size();
}

int Library::getBorrowedCount() const {
    int count = 0;
    for (const auto& r : records)
        if (!r.isReturned())
            count++;
    return count;
}

int Library::getAvailableCopies(const std::string& isbn) const {
    for (const auto& b : books)
        if (b.getISBN() == isbn)
            return b.getCopiesAvailable();
    return -1;
}

// Display
void Library::displayAllBooks() const {
    for (const auto& b : books)
        b.display(std::cout);
}

void Library::displayAllUsers() const {
    for (const auto& u : users)
        u->display(std::cout);
}

void Library::displayAllRecords() const {
    for (const auto& r : records)
        r.display(std::cout);
}

// Book file loading
bool Library::loadBooks(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open())
        return false;

    books.clear();
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        try {
            books.push_back(Book::deserializeCSV(line));
        }
        catch (...) {
            std::cerr << "Error parsing book line: " << line << std::endl;
        }
    }
    return true;
}

bool Library::saveBooks(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open())
        return false;

    for (const auto& b : books)
        fout << b.serializeCSV() << "\n";

    return true;
}

// User File Loading
bool Library::loadUsers(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open())
        return false;

    users.clear();
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        try {
            std::unique_ptr<User> u = User::deserializeCSV(line);
            users.push_back(std::move(u));
        } catch (...) {
            std::cerr << "Error parsing user line: " << line << std::endl;
        }
    }
    return true;
}

bool Library::saveUsers(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open())
        return false;

    for (const auto& u : users) {
        fout << u ->serializeCSV() << std::endl;
    }
    return true;
}

// Borrow record file loading
bool Library::loadRecords(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open())
        return false;

    records.clear();
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        try {
            BorrowRecord r = BorrowRecord::deserialize(line);
            records.push_back(r);
        }
        catch (...) {
            std::cerr << "Error parsing record line: " << line << std::endl;
        }
    }
    return true;
}

bool Library::saveRecords(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open())
        return false;

    for (const auto& r : records)
        fout << r.serialize() << "\n";

    return true;
}