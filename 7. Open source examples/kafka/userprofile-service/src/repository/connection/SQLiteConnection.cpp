/*
* File: SqlLiteConnection.cpp
* Author: trung.la
* Date: 06-15-2025
* Description: This file contains the definitions for SQLite connection
*/

#include "connection/SQLiteConnection.h"

#include <iostream>

SQLiteConnection::SQLiteConnection(const std::string &dbPath)
    : m_dbPath(dbPath),
    m_db(std::make_unique<SQLite::Database>(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE))
{
}

void SQLiteConnection::query(const std::string &query)
{
    try {
        m_db->exec(query);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void SQLiteConnection::transaction(const std::string &query)
{
    try {
        SQLite::Transaction transaction(*m_db.get());
        m_db->exec(query);
        transaction.commit();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

SQLite::Database *SQLiteConnection::connection()
{
    return m_db.get();
}