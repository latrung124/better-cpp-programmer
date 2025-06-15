/*
* File: IDatabaseConnection.h
* Author: trung.la
* Date: 06-15-2025
* Description: This file contains the interface for database connection
*/

#ifndef DATABASE_IDATABASECONNECTION_H_
#define DATABASE_IDATABASECONNECTION_H_

#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

class IDatabaseConnection
{
public:
    virtual ~IDatabaseConnection() = default;

    /**
     * @brief Query data from database
     * 
     * @param query The query string
     * @return void
     */
    virtual void query(const std::string &query) = 0;
    
    /**
     * @brief Execute a transaction
     * A transaction is a way to group multiple SQL statements into an atomic operation
     * 
     * @param query The query string
     * @return void
     */
    virtual void transaction(const std::string &query) = 0;

    /**
     * @brief Get the connection object
     * 
     * @return SQLite::Database* The connection object
     */
    virtual SQLite::Database *connection() = 0;
};

#endif // DATABASE_IDATABASECONNECTION_H_