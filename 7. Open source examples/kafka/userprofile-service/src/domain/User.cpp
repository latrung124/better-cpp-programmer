/*
* File: User.cpp
* Author: trung.la
* Date: 06-15-2025
* Description: This file is definition of User model's attributes and methods
*/

#include "User.h"

User::User()
{
}

User::User(const std::string& userId, const std::string& userName,
    const std::string& email, const std::string& createAt, const std::string& updateAt)
    : m_userId(userId), m_userName(userName), m_email(email), m_createAt(createAt), m_updateAt(updateAt)
{
}

User::~User()
{
}

std::string User::toJson()
{
    return "";
}

User User::fromJson(std::string const &jsonStr)
{
    return User();
}

bool User::isValid()
{
    return true;
}

std::string User::getUserId() const
{
    return m_userId;
}

void User::setUserId(const std::string& userId)
{
    if (m_userId.compare(userId) != 0)
    {
        m_userId = userId;
    }
}

std::string User::getUserName() const
{
    return m_userName;
}

void User::setUserName(const std::string& userName)
{
    if (m_userName.compare(userName) != 0)
    {
        m_userName = userName;
    }
}

std::string User::getEmail() const
{
    return m_email;
}

void User::setEmail(const std::string& email)
{
    if (m_email.compare(email) != 0)
    {
        m_email = email;
    }
}

std::string User::getCreateAt() const
{
    return m_createAt;
}

void User::setCreateAt(const std::string& createAt)
{
    if (m_createAt.compare(createAt) != 0)
    {
        m_createAt = createAt;
    }
}

std::string User::getUpdateAt() const
{
    return m_updateAt;
}

void User::setUpdateAt(const std::string& updateAt)
{
    if (m_updateAt.compare(updateAt) != 0)
    {
        m_updateAt = updateAt;
    }
}