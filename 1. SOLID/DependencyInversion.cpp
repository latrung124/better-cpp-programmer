/*
* File: DependencyInversion.cpp
* Author: trung.la
* Date: 08-03-2025
* Description: This file is the implementation of Dependency Inversion Principle
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ==========================================
// WITHOUT DEPENDENCY INVERSION PRINCIPLE
// ==========================================

/**
 * @brief MySQL Database class
 * This class represents a MySQL database and provides methods to connect, disconnect, and execute queries.
 */
class MySQLDatabase
{
public:
    void connect() {
        std::cout << "MySQL Database connected!" << std::endl;
    }

    void disconnect() {
        std::cout << "MySQL Database disconnected!" << std::endl;
    }

    void execute(const std::string &query) {
        std::cout << "MySQL Database executed query: " << query << std::endl;
    }
};

/**
 * @brief MongoDB Database class
 * This class represents a MongoDB database and provides methods to connect, disconnect, and execute queries.
 */
class MongoDBDatabase
{
public:
    void connect() {
        std::cout << "MongoDB Database connected!" << std::endl;
    }

    void disconnect() {
        std::cout << "MongoDB Database disconnected!" << std::endl;
    }

    void execute(const std::string &query) {
        std::cout << "MongoDB Database executed query: " << query << std::endl;
    }
};

/**
 * @brief User Manager class
 * This class is responsible for managing user operations.
 * It uses the MySQLDatabase class to interact with the MySQL database.
 */
class MySQLUserManager
{
private:
    std::unique_ptr<MySQLDatabase> m_db;
public:
    MySQLUserManager() : m_db(std::make_unique<MySQLDatabase>()) {}
    ~MySQLUserManager() = default;

    void addUser(const std::string &userName, const std::string &email) {
        m_db->connect();
        m_db->execute("INSERT INTO users (username, email) VALUES ('" + userName + "', '" + email + "')");
        m_db->disconnect();
    }

    void deleteUser(const std::string &userName) {
        m_db->connect();
        m_db->execute("DELETE FROM users WHERE username = '" + userName + "'");
        m_db->disconnect();
    }
};

/**
 * @brief User Manager class
 * This class is responsible for managing user operations.
 * It uses the MongoDBDatabase class to interact with the MongoDB database.
 */
class MongoDBUserManager
{
private:
    std::unique_ptr<MongoDBDatabase> m_db;

public:
    MongoDBUserManager() : m_db(std::make_unique<MongoDBDatabase>()) {}
    ~MongoDBUserManager() = default;

    void addUser(const std::string &userName, const std::string &email) {
        m_db->connect();
        m_db->execute("db.users.insert({username: '" + userName + "', email: '" + email + "'})");
        m_db->disconnect();
    }

    void deleteUser(const std::string &userName) {
        m_db->connect();
        m_db->execute("db.users.remove({username: '" + userName + "'})");
        m_db->disconnect();
    }
};

// Demonstrate without DIP
void demonstrateWithoutDIP() {
    std::cout << "Demonstrating without Dependency Inversion Principle" << std::endl;

    MySQLUserManager mysqlUserManager;
    mysqlUserManager.addUser("Alice", "alice@gmail.com");
    mysqlUserManager.deleteUser("Alice");

    MongoDBUserManager mongoDBUserManager;
    mongoDBUserManager.addUser("Bob", "bob@gmail.com");
    mongoDBUserManager.deleteUser("Bob");

    /**
     * Without Dependency Inversion Principle, the MySQLUserManager and MongoDBUserManager classes
     * were tightly coupled to the MySQLDatabase and MongoDBDatabase classes, respectively.
     * This makes it difficult to switch between different database implementations.
     * If we wanted to switch from MySQL to MongoDB or vice versa, we would need to modify the User Manager classes.
     */
}

// ==========================================
// WITH DEPENDENCY INVERSION PRINCIPLE
// ==========================================

/**
 * @brief IDatabase interface
 * This interface defines the common methods that a database class should implement.
 */
class IDatabase
{
public:
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void execute(const std::string &query) = 0;
    virtual ~IDatabase() = default;
};

/**
 * @brief MySQL Database class
 * This class is a concrete implementation of the IDatabase interface for MySQL.
 */
class MySQLDatabaseDIP : public IDatabase
{
public:
    void connect() override {
        std::cout << "MySQL Database connected!" << std::endl;
    }

    void disconnect() override {
        std::cout << "MySQL Database disconnected!" << std::endl;
    }

    void execute(const std::string &query) override {
        std::cout << "MySQL Database executed query: " << query << std::endl;
    }
};

/**
 * @brief MongoDB Database class
 * This class is a concrete implementation of the IDatabase interface for MongoDB.
 */
class MongoDBDatabaseDIP : public IDatabase
{
public:
    void connect() override {
        std::cout << "MongoDB Database connected!" << std::endl;
    }

    void disconnect() override {
        std::cout << "MongoDB Database disconnected!" << std::endl;
    }

    void execute(const std::string &query) override {
        std::cout << "MongoDB Database executed query: " << query << std::endl;
    }
};

/**
 * @brief User Manager class
 * This class is responsible for managing user operations.
 * It uses the IDatabase interface to interact with the database.
 */
class UserManager
{
private:
    std::unique_ptr<IDatabase> m_db;

public:
    UserManager(std::unique_ptr<IDatabase> db) : m_db(std::move(db)) {}

    void addUser(const std::string &userName, const std::string &email) {
        m_db->connect();
        m_db->execute("INSERT INTO users (username, email) VALUES ('" + userName + "', '" + email + "')");
        m_db->disconnect();
    }

    void deleteUser(const std::string &userName) {
        m_db->connect();
        m_db->execute("DELETE FROM users WHERE username = '" + userName + "'");
        m_db->disconnect();
    }
};

// Demonstrate with DIP
void demonstrateWithDIP() {
    std::cout << "Demonstrating with Dependency Inversion Principle" << std::endl;

    std::unique_ptr<IDatabase> mysqlDatabase = std::make_unique<MySQLDatabaseDIP>();
    UserManager mysqlUserManager(std::move(mysqlDatabase));
    mysqlUserManager.addUser("Alice", "alice@gmail.com");
    mysqlUserManager.deleteUser("Alice");

    std::unique_ptr<IDatabase> mongoDBDatabase = std::make_unique<MongoDBDatabaseDIP>();
    UserManager mongoDBUserManager(std::move(mongoDBDatabase));
    mongoDBUserManager.addUser("Bob", "bob@gmail.com");
    mongoDBUserManager.deleteUser("Bob");

    /**
     * With Dependency Inversion Principle, the UserManager class is decoupled from the specific database
     * implementation (MySQLDatabaseDIP or MongoDBDatabaseDIP) by using the IDatabase interface.
     * This allows for easier switching between different database implementations without modifying the UserManager class.
     */
}

