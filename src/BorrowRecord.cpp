#include "BorrowRecord.h"
#include <sstream>
#include <iomanip>

/*
 * BorrowRecord.cpp
 * Implements the BorrowRecord class declared in BorrowRecord.h.
 *
 * Includes:
 *  - Full constructor definitions
 *  - Logic for making a record returned
 *  - Late-day calculation using approximate date conversion
 *  - CSV serialization/deserialization operations
 *  - A formatted display method for human-readable output
 */

// Helper: Convert a date (y, m, d) into an integer
static int toDays(int y, int m, int d) {
    return y * 365 + m * 30 + d;
}

// Constructors
BorrowRecord::BorrowRecord()
    : recordID(""), userID(""), isbn(""),
    borrowedYear(0), borrowedMonth(0), borrowedDay(0),
    dueYear(0), dueMonth(0), dueDay(0),
    returned(false), returnYear(0), returnMonth(0), returnDay(0) {}

BorrowRecord::BorrowRecord(std::string r, std::string u, std::string i, int by, int bm, int bd, int dy, int dm, int dd)
    : recordID(r), userID(u), isbn(i),
    borrowedYear(by), borrowedMonth(bm), borrowedDay(bd),
    dueYear(dy), dueMonth(dm), dueDay(dd),
    returned(false), returnYear(0), returnMonth(0), returnDay(0) {}

// Getters
const std::string& BorrowRecord::getRecordID() const {
    return recordID;
}

const std::string& BorrowRecord::getUserID() const {
    return userID;
}

const std::string& BorrowRecord::getISBN() const {
    return isbn;
}

bool BorrowRecord::isReturned() const {
    return returned;
}

// Mark the record as returned on the given date
void BorrowRecord::markReturned(int y, int m, int d) {
    returned = true;
    returnYear = y;
    returnMonth = m;
    returnDay = d;
}

// Calculate how many days late the return was
int BorrowRecord::daysLate() const {
    if (!returned)
        return 0;

    int due = toDays(dueYear, dueMonth, dueDay);
    int ret = toDays(returnYear, returnMonth, returnDay);

    int diff = ret - due;
    return (diff > 0 ? diff : 0);
}

// Serialize the record into a CSV format
std::string BorrowRecord::serialize() const {
    std::ostringstream ss;

    ss << recordID << ","
        << userID << ","
        << isbn << ","
        << borrowedYear << "-" << borrowedMonth << "-" << borrowedDay << ","
        << dueYear << "-" << dueMonth << "-" << dueDay << ",";

    if (returned) {
        ss << "RETURNED,"
            << returnYear << "-" << returnMonth << "-" << returnDay;
    }
    else {
        ss << "NOT_RETURNED";
    }
    return ss.str();
}

// Helper: Parse a YYYY-MM-DD formatted string into integers
static void parseDate(const std::string& s, int& y, int& m, int& d) {
    char dash;
    std::stringstream ss(s);
    ss >> y >> dash >> m >> dash >> d;
}

// Deserialize a CSV string back into a BorrowRecord
BorrowRecord BorrowRecord::deserialize(const std::string& line) {
    std::stringstream ss(line);

    std::string recordID, userID, isbn;
    std::string borrowedStr, dueStr;
    std::string returnFlag, returnDateStr;

    std::getline(ss, recordID, ',');
    std::getline(ss, userID, ',');
    std::getline(ss, isbn, ',');
    std::getline(ss, borrowedStr, ',');
    std::getline(ss, dueStr, ',');
    std::getline(ss, returnFlag, ',');

    int by, bm, bd;
    int dy, dm, dd;

    parseDate(borrowedStr, by, bm, bd);
    parseDate(dueStr, dy, dm, dd);

    // Create base record
    BorrowRecord rec(recordID, userID, isbn, by, bm, bd, dy, dm, dd);

    // If returned, read one more date
    if (returnFlag == "RETURNED") {
        std::getline(ss, returnDateStr, ',');
        int ry, rm, rd;
        parseDate(returnDateStr, ry, rm, rd);
        rec.markReturned(ry, rm, rd);
    }

    return rec;
}

// Display
    void BorrowRecord::display(std::ostream& os) const {
    os << "----------------------------------------------------" << std::endl;
    os << "                  BORROW RECORD                     " << std::endl;
    os << "----------------------------------------------------" << std::endl;

    os << std::left << std::setw(18) << "Record ID:"    << recordID << std::endl;
    os << std::left << std::setw(18) << "User ID:"      << userID << std::endl;
    os << std::left << std::setw(18) << "ISBN:"         << isbn << std::endl;

    os << std::left << std::setw(18) << "Borrowed Date:"
       << borrowedYear << "-"
       << std::setw(2) << std::setfill('0') << borrowedMonth << "-"
       << std::setw(2) << std::setfill('0') << borrowedDay << std::endl;
    os << std::setfill(' ');

    os << std::left << std::setw(18) << "Due Date:"
       << dueYear << "-"
       << std::setw(2) << std::setfill('0') << dueMonth << "-"
       << std::setw(2) << std::setfill('0') << dueDay << std::endl;
    os << std::setfill(' ');

    if (returned) {
        os << std::left << std::setw(18) << "Returned:" << "YES" << std::endl;

        os << std::left << std::setw(18) << "Return Date:"
           << returnYear << "-"
           << std::setw(2) << std::setfill('0') << returnMonth << "-"
           << std::setw(2) << std::setfill('0') << returnDay << std::endl;
        os << std::setfill(' ');

        os << std::left << std::setw(18) << "Days Late:" << daysLate() << std::endl;
    } else {
        os << std::left << std::setw(18) << "Returned:" << "NO" << std::endl;
        os << std::left << std::setw(18) << "Return Date:" << "N/A" << std::endl;
        os << std::left << std::setw(18) << "Days Late:" << "0" << std::endl;
    }

    os << "----------------------------------------------------" << std::endl;
}