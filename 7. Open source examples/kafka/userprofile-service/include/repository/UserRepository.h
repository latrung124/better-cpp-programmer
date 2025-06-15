/*
* File: UserRepository.h
* Author: trung.la
* Date: 06-13-2025
* Descriptions: This is declaration of User Repository class which represent connection with database
*/

#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <memory>
#include <optional>
#include <vector>
#include <unordered_map>

#include "connection/IDatabaseConnection.h"
#include "utils.h"

class User;

class UserRepository
{
public:
    using ConnectionType = user_profile::utils::database::ConnectionType;
    using DatabaseConnectionPtr = std::shared_ptr<IDatabaseConnection>;
    using DatabaseConnectionWPtr = std::weak_ptr<IDatabaseConnection>;

    UserRepository();
    ~UserRepository();

    void selectConnection(ConnectionType type);
    ConnectionType getCurrentConnectionType() const;

    void createTable();
    void insert(const User& user);
    void update(const User& user);
    void remove(const User& user);
    std::vector<User> getAll();
    std::optional<User> findById(const std::string& userId);
    std::optional<User> findByUserName(const std::string& userName);
    std::optional<User> findByEmail(const std::string& email);

private:
    std::unordered_map<ConnectionType, DatabaseConnectionPtr> m_connections;
    DatabaseConnectionWPtr m_currentConnection;
    ConnectionType m_currentConnectionType;
};

#endif // USER_REPOSITORY_H