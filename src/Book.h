#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <sstream>

/*
 * Book.h
 * Defines the Book class, which represents a signle book in the library system.
 * Each Book stores:
 *  - ISBN
 *  - Title
 *  - Author
 *  - Publication year
 *  - Total number of copies
 *  - Number of available copies
 *
 * The Book class provides:
 *  - Accessors and mutators for core book date
 *  - Inventory operations (borrow/return/add copies)
 *  - CSV serialization and deserialization for file storage
 *  - A formatted display function
 */

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    unsigned int year;
    unsigned int copiesTotal;
    unsigned int copiesAvailable;

public:
// Constructor
Book();
Book(const std::string& isbn, const std::string& title, const std::string& author, unsigned int year, unsigned int copiesTotal);

// Getters
const std::string& getISBN() const;
const std::string& getTitle() const;
const std::string& getAuthor() const;
unsigned int getYear() const;
unsigned int getCopiesTotal() const;
unsigned int getCopiesAvailable() const;

// Setters
void setTitle(const std::string& t);
void setAuthor(const std::string& a);
void setYear(unsigned int y);

// Inventory operators
void addCopies(unsigned int n);
bool borrowOne();
bool returnOne();

// file I/O
std::string serializeCSV() const; // convert to CSV row
static Book deserializeCSV(const std::string& line); // create from CSV row

// display
void display(std::ostream& os) const;
};

#endif