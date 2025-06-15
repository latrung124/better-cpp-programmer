/*
* File: UserRepository.cpp
* Author: trung.la
* Date: 06-13-2025
* Descriptions: This is implementation of UserRepository.
*/

#include "UserRepository.h"
#include "User.h"

namespace
{
    using ConnectionType = user_profile::utils::database::ConnectionType;
}

UserRepository::UserRepository()
{
}

UserRepository::~UserRepository()
{
}

void UserRepository::selectConnection(ConnectionType type)
{
    m_currentConnectionType = type;
    // TODO set the connection
}

ConnectionType UserRepository::getCurrentConnectionType() const
{
    return m_currentConnectionType;
}

void UserRepository::createTable()
{
}

void UserRepository::insert(const User& user)
{
}

void UserRepository::update(const User& user)
{
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
    return std::nullopt;
}

std::optional<User> UserRepository::findByUserName(const std::string& userName)
{
    return std::nullopt;
}

std::optional<User> UserRepository::findByEmail(const std::string& email)
{
    return std::nullopt;
}
