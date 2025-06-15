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
    ~User();

    std::string toJson();
    User fromJson(std::string const &jsonStr);
    bool isValid();

private:
    std::string m_id;
    std::string m_email;
    std::string m_userName;
    std::string m_avatar;
    std::string m_createdAt;
    std::string m_updatedAt;
};

#endif // USER_H