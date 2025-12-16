#include "Book.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>

/*
 * Book.cpp
 * Implements the Book class declared in Book.h.
 * Contains logic for:
 *  - Book construction
 *  - Safe inventory updates (borrow/return)
 *  - CSV converstion functions
 *  - display formatting
 */

// constructors
Book::Book() : isbn(""), title(""), author(""), year(0), copiesTotal(0), copiesAvailable(0) {}
Book::Book(const std::string& isbn, const std::string& title, const std::string& author, unsigned int year, unsigned int copiesTotal)
    : isbn(isbn), title(title), author(author), year(year), copiesTotal(copiesTotal), copiesAvailable(copiesTotal) {}

// gettters
const std::string& Book::getISBN() const {
    return isbn;
}
const std::string& Book::getTitle() const {
    return title;
}
const std::string& Book::getAuthor() const {
    return author;
}
unsigned int Book::getYear() const {
    return year;
}
unsigned int Book::getCopiesTotal() const {
    return copiesTotal;
}
unsigned int Book::getCopiesAvailable() const {
    return copiesAvailable;
}

// setters
void Book::setTitle(const std::string& t) {
    title = t;
}
void Book::setAuthor(const std::string& a) {
    author = a;
}
void Book::setYear(unsigned int y) {
    year = y;
}

// Inventory operators
void Book::addCopies(unsigned int n) {
    // Increases both total and available copies
    copiesTotal +=n;
    copiesAvailable +=n;
}
bool Book::borrowOne() {
    if (copiesAvailable == 0)
        return false;
    copiesAvailable--;
    return true;
}

bool Book::returnOne() {
    // Attempts to decrement available copies
    if(copiesAvailable < copiesTotal) {
        copiesAvailable++;
        // true if copy was borrowed successfully
        return true;
    }
    // flase if no copies are available
    return false;
}

// CSV serialization
// Converts all book data into string. This is used by Library I/O for saving book inventory
std::string Book::serializeCSV() const {
    std::ostringstream ss;
    ss << isbn << "," << title << "," << author << "," << year << "," << copiesTotal << "," << copiesAvailable;
    return ss.str();
}
// CSV deserialization
// Reconstructs a Book object from a CSV line, uses stringstream and getline to extract fields
Book Book::deserializeCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string item;

    std::string isbn, title, author;
    unsigned int year = 0, total = 0, available = 0;

    // Extract string fields (up to the comma)
    std::getline(ss, isbn, ',');
    std::getline(ss, title, ',');
    std::getline(ss, author, ',');

    // Extract the numeric fields
    ss >> year; ss.ignore(1);
    ss >> total; ss.ignore(1);
    ss >> available;

    // Construct book using the extracted values
    Book b(isbn, title, author, year, total);
    b.copiesAvailable = available;

    return b;
}

// display
void Book::display(std::ostream& os) const {
    os << "ISBN: " << isbn << std::endl;
    os << "Title: " << title << std::endl;
    os << "Author: " << author << std::endl;
    os << "Year: " << year << std::endl;
    os << "Total Copies: " << copiesTotal << std::endl;
    os << "Available Copies: " << copiesAvailable << std::endl;
}