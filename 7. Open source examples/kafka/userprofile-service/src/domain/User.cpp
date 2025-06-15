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