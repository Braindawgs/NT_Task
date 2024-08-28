#pragma once

#include "interfaceStorage.h"

#include <string>
#include <iostream>
#include <sqlite3.h>

/**
 * @brief Database storage class, sqlite3
 * 
 */
class Database : public InterfaceStorage
{
public:
    Database();
    ~Database();

    /**
     * @brief Writes key value pair to database.
     * 
     * @param key identifier in database.
     * @param value value to be written.
     */
    void write(int const& key, std::string const& value) override;

    /**
     * @brief Reads value from key identifier.
     * 
     * @param key identifier in database.
     * @return std::string string on with key identfier.
     */
    std::string read(int const& key) override;

    /**
     * @brief List all entries in the database.
     * 
     */
    void listAll() override;

private:

    /**
     * @brief Creates a sqlite3 database file.
     * 
     */
    void createTable();

    /**
     * @brief Throws and finalizes sql stmt.
     * @note  No need to check validity of stmt ptr:
     * Invoking sqlite3_finalize() on a NULL pointer is a harmless no-op.
     * https://www.sqlite.org/c3ref/finalize.html
     * 
     * @param stmt SQL statement.
     */
    void throwAndFinalize(sqlite3_stmt* stmt, std::string const& err);

    std::string const m_dbPath = "Storage.db";
    sqlite3* m_db;
};