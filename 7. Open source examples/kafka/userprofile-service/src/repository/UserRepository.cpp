/*
* File: UserRepository.cpp
* Author: trung.la
* Date: 06-13-2025
* Descriptions: This is implementation of UserRepository.
*/

#include "UserRepository.h"
#include "User.h"
#include "connection/SQLiteConnection.h"

namespace
{
    using ConnectionType = user_profile::utils::database::ConnectionType;
}

UserRepository::UserRepository()
{
    m_connections[ConnectionType::eSQLite] = std::make_shared<SQLiteConnection>(""); //TODO: add db path
}

UserRepository::~UserRepository()
{
}

void UserRepository::selectConnection(ConnectionType type)
{
    if (type == m_currentConnectionType) {
        return;
    }

    if (m_connections.find(type) == m_connections.end()) {
        //TODO: add log later
        return;
    }

    m_currentConnectionType = type;
    m_currentConnection = m_connections[type];
}

ConnectionType UserRepository::getCurrentConnectionType() const
{
    return m_currentConnectionType;
}

void UserRepository::createTable()
{
    if (auto const connection = m_currentConnection.lock(); connection) {
        //TODO: build a helper create sql query by object
        const std::string sql = 
            "CREATE TABLE IF NOT EXISTS Users ("
            "user_id TEXT PRIMARY KEY, "
            "email TEXT UNIQUE, "
            "username TEXT UNIQUE NOT NULL, "
            "created_at TEXT DEFAULT CURRENT_TIMESTAMP, "
            "updated_at TEXT DEFAULT CURRENT_TIMESTAMP"
            ")";
        connection->transaction(sql);
    } else {
        //TODO: add log
    }
}

void UserRepository::insert(const User& user)
{
    if (auto const connection = m_currentConnection.lock(); connection) {
        const std::string sql =
            "INSERT INTO Users (user_id, email, username, created_at, updated_at) "
            "VALUES ('" + user.getUserId() + "', '" + user.getEmail() + "', '"
            + user.getUserName() + "', '" + user.getCreateAt() + "', '"
            + user.getUpdateAt() + "')";
        connection->transaction(sql);
    } else {
        //TODO: add log
    }
}

void UserRepository::update(const User& user)
{
    if (auto const connection = m_currentConnection.lock(); connection) {
        const std::string sql =
            "UPDATE Users SET "
            "email = '" + user.getEmail() + "', "
            "username = '" + user.getUserName() + "', "
            "updated_at = '" + user.getUpdateAt() + "' "
            "WHERE user_id = '" + user.getUserId() + "'";
        connection->transaction(sql);
    } else {
        //TODO: add log
    }
}

void UserRepository::remove(const User& user)
{
}

std::vector<User> UserRepository::getAll()
{
    return std::vector<User>();
}

std::optional<User> UserRepository::findById(const std::string& userId)
{
    auto const connection = m_currentConnection.lock();
    if (!connection)
    {
        return std::nullopt;
    }
    
    const std::string sql = "SELECT * FROM Users WHERE user_id = '" + userId + "'";
    SQLite::Statement query(*connection->connection(), sql);
    if (query.executeStep())
    {
        return User{ query.getColumn(0).getText(), query.getColumn(1).getText(),
            query.getColumn(2).getText(), query.getColumn(3).getText(), query.getColumn(4).getText()};
    }

    return std::nullopt;
}

std::optional<User> UserRepository::findByUserName(const std::string& userName)
{
    auto const connection = m_currentConnection.lock();
    if (!connection)
    {
        return std::nullopt;
    }
    
    const std::string sql = "SELECT * FROM Users WHERE username = '" + userName + "'";
    SQLite::Statement query(*connection->connection(), sql);
    if (query.executeStep())
    {
        return User{ query.getColumn(0).getText(), query.getColumn(1).getText(),
            query.getColumn(2).getText(), query.getColumn(3).getText(), query.getColumn(4).getText()};
    }

    return std::nullopt;
}

std::optional<User> UserRepository::findByEmail(const std::string& email)
{
    auto const connection = m_currentConnection.lock();
    if (!connection)
    {
        return std::nullopt;
    }
    
    const std::string sql = "SELECT * FROM Users WHERE email = '" + email + "'";
    SQLite::Statement query(*connection->connection(), sql);
    if (query.executeStep())
    {
        return User{ query.getColumn(0).getText(), query.getColumn(1).getText(),
            query.getColumn(2).getText(), query.getColumn(3).getText(), query.getColumn(4).getText()};
    }

    return std::nullopt;
}
