#pragma once

#include "interfaceStorage.h"

#include <string>
#include <iostream>
#include <sqlite3.h>

class Database : public InterfaceStorage
{
public:
    Database();
    ~Database();

    void write(int const& key, std::string const& value) override;
    std::string read(int const& key) override;
    void listAll() override;

    void corruptor(int const& key, std::string const& value);

private:
    void createTable();
    size_t checksum(std::string const& data);

    std::string const m_dbPath = "Storage.db";
    sqlite3* m_db;
};