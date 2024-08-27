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

    /**
     * @brief Dummy function that "corrupts" specific part of the db. 
     * 
     * @param key identifier in database.
     * @param value value to be written.
     */
    void corruptor(int const& key, std::string const& value);

private:

    /**
     * @brief Creates a sqlite3 database file.
     * 
     */
    void createTable();

    /**
     * @brief Hashing algorithm.
     * 
     * @param data Input data.
     * @return size_t hash.
     */
    size_t checksum(std::string const& data);

    std::string const m_dbPath = "Storage.db";
    sqlite3* m_db;
};