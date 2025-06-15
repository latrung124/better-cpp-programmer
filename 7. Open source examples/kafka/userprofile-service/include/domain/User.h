/*
* File: User.h
* Author: trung.la
* Date: 06-15-2025
* Description: This file is declaration of User model's attribute and method
*/

#ifndef USER_H
#define USER_H

#include <string>

#include <nlohmann/json.hpp>

class User
{
public:
    using json = nlohmann::json;
    User();
    User(const std::string& userId, const std::string& userName, const std::string& email, const std::string& createAt, const std::string& updateAt);

    ~User();

    std::string toJson();
    User fromJson(std::string const &jsonStr);
    bool isValid();

    std::string getUserId() const;
    void setUserId(const std::string& userId);

    std::string getUserName() const;
    void setUserName(const std::string& userName);

    std::string getEmail() const;
    void setEmail(const std::string& email);

    std::string getCreateAt() const;
    void setCreateAt(const std::string& createAt);

    std::string getUpdateAt() const;
    void setUpdateAt(const std::string& updateAt);

private:
    std::string m_userId;
    std::string m_email;
    std::string m_userName;
    std::string m_avatar;
    std::string m_createAt;
    std::string m_updateAt;
};

#endif // USER_H