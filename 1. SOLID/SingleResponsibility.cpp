/*
* File: SingleResponsibility.cpp
* Author: trung.la
* Date: 06-03-2025
* Description: This file is the implementation of Single Responsibility Principle
*/

#include <iostream>
#include <memory>
#include <string>

// Without Single Responsibility Principle
class DatabaseConnection
{
public:
    void execute(const std::string& query,
                const std::string& username,
                const std::string& email,
                const std::string& password) {
        std::cout << "Database Connection executed!" << std::endl;
    }

    void commit() {
        std::cout << "Database Connection commited!" << std::endl;
    }
}; 

// Without Single Responsibility Principle
// UserManager class has multiple responsibilities
// 1. Hashing password
// 2. Sending email
// 3. Database operations
// 4. User creation
class UserManager
{
private:
    std::string hashPassword(const std::string& password) {
        std::string hashed = password + "_hashed";
        return hashed;
    }

    void sendEmail(const std::string& email, const std::string& message) {
        std::cout << "Email sent to " << email << " with message: " << message << std::endl;
    }

    std::shared_ptr<DatabaseConnection> m_dbConnection;

public:
    UserManager(const std::shared_ptr<DatabaseConnection> &dbConnection) : m_dbConnection(dbConnection) {}

    bool createUser(const std::string& userName, const std::string &email, const std::string &password) {
        // Input Validation
        if (userName.empty() || email.empty() || password.empty()) {
            throw std::invalid_argument("Invalid input");
        }

        if (email.find("@") == std::string::npos) {
            throw std::invalid_argument("Invalid email");
        }

        if (password.size() < 8) {
            throw std::invalid_argument("Password must be at least 8 characters");
        }

        std::string hashedPw = hashPassword(password);

        // ... create user with email and hashedPw
 
        sendEmail(email, "Welcome to our system!");        
        return true;
    }
};

// With Single Responsibility Principle
// Each class has one responsibility

/**
 * @brief User Validator class
 * 
 * This class is responsible for validating user data input.
 */
class UserValidator
{
public:
    static bool validate(const std::string& userName, const std::string &email, const std::string &password) {
        // Input Validation
        if (userName.empty() || email.empty() || password.empty()) {
            throw std::invalid_argument("Invalid input");
        }

        if (email.find("@") == std::string::npos) {
            throw std::invalid_argument("Invalid email");
        }

        if (password.size() < 8) {
            throw std::invalid_argument("Password must be at least 8 characters");
        }

        return true;
    }
};

/**
 * @brief Email Service class
 * 
 * This class is responsible for sending emails to users.
 */
class EmailService
{
public:
    static void sendEmail(const std::string& email, const std::string& message) {
        std::cout << "Email sent to " << email << " with message: " << message << std::endl;
    }
};

/**
 * @brief Password Service class
 * 
 * This class is responsible for hashing passwords.
 */
class PasswordService
{
public:
    static std::string hashPassword(const std::string& password) {
        std::string hashed = password + "_hashed";
        return hashed;
    }
};

/**
 * @brief Database Connection class
 * 
 * This class is responsible for establishing a connection to the database and executing queries.
 */
class DatabaseConnection
{
public:
    void execute(const std::string& query) {
        std::cout << "Database Connection executed!" << std::endl;
    }

    void commit() {
        std::cout << "Database Connection commited!" << std::endl;
    }
};

/**
 * @brief User Repository class
 * 
 * This class is responsible for database operations related to users.
 */
class UserRepository
{
private:
    std::shared_ptr<DatabaseConnection> m_dbConnection;

public:
    UserRepository(const std::shared_ptr<DatabaseConnection> &dbConnection) : m_dbConnection(dbConnection) {}

    bool saveUser(const std::string& userName, const std::string &email, const std::string &hashedPassword) {
        std::string query = "INSERT INTO users (username, email, password) VALUES ('" + userName + "', '" + email + "', '" + hashedPassword + "')";
        m_dbConnection->execute(query);
        m_dbConnection->commit();
        return true;
    }
};

/**
 * @brief User Service class
 * 
 * This class utilizes the Single Responsibility Principle by separating the concerns of the UserManager class
 * into separate classes. The UserManager class is now responsible for managing the user creation process
 * and delegating the validation, hashing, database operations, and email sending to other classes.
 */
class UserService
{
private:
    std::unique_ptr<UserRepository> m_userRepository;

public:
    UserService(const std::shared_ptr<DatabaseConnection> &dbConnection) {
        m_userRepository = std::make_unique<UserRepository>(dbConnection);
    }

    bool createUser(const std::string &userName, const std::string &email, const std::string &password) {
        if (!UserValidator::validate(userName, email, password)) {
            return false;
        }

        std::string hashedPw = PasswordService::hashPassword(password);

        m_userRepository->saveUser(userName, email, hashedPw);

        EmailService::sendEmail(email, "Welcome to our system!");

        return true;
    }
};