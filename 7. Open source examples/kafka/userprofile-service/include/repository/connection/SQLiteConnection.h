/*
* File: SqlLiteConnection.h
* Author: trung.la
* Date: 06-15-2025
* Description: This file contains the interface for database connection
*/

/*
* File: SQLiteConnection.h
* Author: trung.la
* Date: 03-22-2025
* Description: This file contains the declarations for SQLite connection
*/

#ifndef SQLITECONNECTION_H_
#define SQLITECONNECTION_H_

#include "connection/IDatabaseConnection.h"

class SQLiteConnection : public IDatabaseConnection
{
public:
    using SQLiteDatabaseUPtr = std::unique_ptr<SQLite::Database>;
    SQLiteConnection() = delete;
    SQLiteConnection(const std::string &dbPath);

    ~SQLiteConnection() override = default;

    void query(const std::string &query) override;
    void transaction(const std::string &query) override;
    SQLite::Database *connection() override;

private:
    SQLiteDatabaseUPtr m_db;
    std::string m_dbPath; 
};

#endif // SQLITECONNECTION_H_