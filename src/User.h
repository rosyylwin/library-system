#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <memory>

/*
 * User.h
 * Declares the User class hierachy used by the library system.
 *
 * Base Class: User
 *  - Stores ID, name, user type, (Student/Teacher/Other), and outstanding fees.
 *  - Defines polymorphic behavior through virtual display() and serializeCSV().
 *  - Supports safe fee updates and CSV-based loading.
 *
 * Derived Classes:
 *  - Student: Adds major field.
 *  - Teacher: Adds department field.
 *
 * The User hierarchy demonstrates:
 *  - Inheritance
 *  - Polymorphism
 *  - Encapusulation
 *  - Dynamic allocation vid std::unique_ptr for library storage
 */

// Enumerates the types of users in the system
enum class UserType { STUDENT, TEACHER, OTHER};

class User {
protected:
    std::string id;
    std::string name;
    UserType type;
    double feesDue;

public:
    // Constructors
    User();
    User(std::string id, std::string name, UserType t);

    // Virtual destructor
    virtual ~User() = default;

    // Display
    virtual void display(std::ostream& os) const;

    // Getters
    const std::string& getID() const;
    const std::string& getName() const;
    UserType getUserType() const;
    double getFeesDue() const;

    // Fee operators
    void addFees(double amt);
    void payFees(double amt);

    // Serialization
    virtual std::string serializeCSV() const;

    // Factory function
    static std::unique_ptr<User> deserializeCSV(const std::string& line);
};

class Student : public User {
private:
    std::string major;

public:
    Student(std::string id, std::string name, std::string major);

    void display(std::ostream& os) const override;
    std::string serializeCSV() const override;
};

class Teacher : public User {
private:
    std::string department;

public:
    Teacher(std::string id, std::string name, std::string department);

    void display(std::ostream& os) const override;
    std::string serializeCSV() const override;
};

#endif