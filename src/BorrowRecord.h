#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H

#include <string>
#include <iostream>

/*
 * BorrowRecord.h
 * BorrowRecord stores the information about a single instance of a book being borrowed by a user.
 * Stores:
 *  - Record ID
 *  - User ID
 *  - Book ISBN
 *  - Borrowed date
 *  - Due date
 *  - Return date
 *  - Late fee calculation
 *
 * Include:
 *  - Marking a record as returned
 *  - Computing days late using simplified date math
 *  - CSV serialization and parsing
 *  - formatted display function
 */

class BorrowRecord {
private:
    std::string recordID;
    std::string userID;
    std::string isbn;

    // Borrowed date (YYYY-MM-DD)
    int borrowedYear;
    int borrowedMonth;
    int borrowedDay;

    //  Due date (YYYY-MM-DD)
    int dueYear;
    int dueMonth;
    int dueDay;

    // Return information
    bool returned;
    int returnYear;
    int returnMonth;
    int returnDay;

public:
    // Constructors
    BorrowRecord();

    BorrowRecord(std::string r, std::string u, std::string i, int by, int bm, int bd, int dy, int dm, int dd);

    // Getters
    const std::string& getRecordID() const;
    const std::string& getUserID() const;
    const std::string& getISBN() const;

    bool isReturned() const;

    // Mark the record as returned
    void markReturned(int y, int m, int d);

    // Calculate how many days late
    int daysLate() const;

    // Serialization
    std::string serialize() const;
    static BorrowRecord deserialize(const std::string& line);

    // Display
    void display(std::ostream& os = std::cout) const;
};

#endif