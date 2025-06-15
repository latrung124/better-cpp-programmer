/*
* File: utils.h
* Author: trung.la
* Date: 06-15-2025
* Description: This file defines common utilities which used widely in other classes.
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

namespace user_profile
{
namespace utils
{

namespace database
{

enum class ConnectionType : uint16_t
{
    eSQLite = 0,
    ePostgresql = 1
};

} // user_profile::utils

} // user_profile::utils

} // user_profile

#endif // UTILS_H