#include "User.h"
#include <sstream>
#include <iomanip>

/*
 * User.cpp
 * Implements the base User class along with Student and Teacher subclasses.
 *
 * Provides:
 *  - Constructors for each type of user
 *  - Fee modication with error handling
 *  - Polymorphic CSV serialization
 *  - Polymorphic display functionality
 *  - A factory-style static deserializeCSV() that returns the correct user type.
 */

// Constructors
User::User()
    : id(""), name(""), type(UserType::OTHER), feesDue(0.0) {}

User::User(std::string id, std::string name, UserType t)
    : id(id), name(name), type(t), feesDue(0.0) {}

// getters
const std::string& User::getID() const {
    return id;
}
const std::string& User::getName() const {
    return name;
}
UserType User::getUserType() const {
    return type;
}
double User::getFeesDue() const {
    return feesDue;
}

// fee handling
// adds a fee to the user account
void User::addFees(double amt) {
    feesDue += amt;
}

// attempts to subtract a payment from user's balance, throws if the amount is more than they owe
void User::payFees(double amt) {
    if (amt > feesDue)
        throw std::runtime_error("Payment exceeds amount owed.");
    feesDue -= amt;
}

// display
// prints base information common to all user types
void User::display(std::ostream& os) const {
    os << "----------------------- USER ----------------------" << std::endl;
    os << "User ID: " << id << std::endl
        << "Name: " << name << std::endl
        << "Type: ";

    // convert enum to readable text
    switch (type) {
        case UserType::STUDENT: os << "Student";
            break;
        case UserType::TEACHER: os << "Teacher";
            break;
        default: os << "Other";
            break;
    }
    os << "\nFees Due: $" << std::fixed << std::setprecision(2) << feesDue << std::endl;
}

// CSV serialization for base user (student and teacher override this)
std::string User::serializeCSV() const {
    std::ostringstream ss;
    ss << "USER," << id << "," << name << ",";

    switch (type) {
        case UserType::STUDENT: ss << "STUDENT";
            break;
        case UserType::TEACHER: ss << "TEACHER";
            break;
        default: ss << "OTHER"; break;
    }

    ss << "," << feesDue;
    return ss.str();
}

// Derialization
// creates Student, Teacher, or User depending on CSV tag
std::unique_ptr<User> User::deserializeCSV(const std::string& line) {
    std::stringstream ss(line);

    std::string tag;
    std::getline(ss, tag, ',');

    // Construct a student
    if (tag == "STUDENT") {
        std::string id, name, major;
        double fees;

        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, major, ',');
        ss >> fees;

        auto s = std::make_unique<Student>(id, name, major);
        s->addFees(fees);
        return s;
    }

    // Construct a Teacher
    if (tag == "TEACHER") {
        std::string id, name, department;
        double fees;

        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, department, ',');
        ss >> fees;

        auto t = std::make_unique<Teacher>(id, name, department);
        t->addFees(fees);
        return t;
    }

    // Construct a base user
    if (tag == "USER") {
        std::string id, name, typeStr;
        double fees;

        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, typeStr, ',');
        ss >> fees;

        UserType t;
        if (typeStr == "STUDENT") t = UserType::STUDENT;
        else if (typeStr == "TEACHER") t = UserType::TEACHER;
        else t = UserType::OTHER;

        auto u = std::make_unique<User>(id, name, t);
        u->addFees(fees);
        return u;
    }

    throw std::runtime_error("Invalid CSV line for User: " + line);
}

// Student Class Implementation
Student::Student(std::string id, std::string name, std::string major)
    : User(id, name, UserType::STUDENT), major(major) {}

// displays base info then adds major
void Student::display(std::ostream& os) const {
    User::display(os);
    os << "Major: " << major << std::endl;
    os << "--------------------------------------------------" << std::endl;
}

std::string Student::serializeCSV() const {
    std::ostringstream ss;
    ss << "STUDENT," << id << "," << name << ","
        << major << "," << feesDue;
    return ss.str();
}

// Teacher Class Implementation
Teacher::Teacher(std::string id, std::string name, std::string department)
    : User(id, name, UserType::TEACHER), department(department) {}

void Teacher::display(std::ostream& os) const {
    User::display(os);
    os << "Department: " << department << std::endl;
    os << "--------------------------------------------------" << std::endl;
}

std::string Teacher::serializeCSV() const {
    std::ostringstream ss;
    ss << "TEACHER," << id << "," << name << ","
        << department << "," << feesDue;
    return ss.str();
}