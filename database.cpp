#include "database.h"


Database::Database()
{
    if (SQLITE_OK != sqlite3_open(m_dbPath.c_str(), &m_db))
    {
        throw std::runtime_error("Failed to open DB");
    }

    createTable();
}

Database::~Database()
{
    sqlite3_close(m_db);
}

void Database::createTable()
{
    const char* sql = "CREATE TABLE IF NOT EXISTS storage ("
                      "key TEXT PRIMARY KEY, "
                      "value TEXT NOT NULL, "
                      "checksum TEXT NOT NULL);";

    char* err = nullptr;
    if (SQLITE_OK != sqlite3_exec(m_db, sql, nullptr, nullptr, &err))
    {
        sqlite3_free(err);
        throw std::runtime_error(err);
    }
}

size_t Database::checksum(std::string const& data)
{
    return std::hash<std::string>{}(data);
}

void Database::write(std::string const& key, std::string const& value)
{
    size_t csum = checksum(value);
    sqlite3_stmt* stmt;
    const char* sql = "REPLACE INTO storage (key, value, checksum) VALUES (?, ?, ?);";

    if (SQLITE_OK != sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr)) 
    {
        throw std::runtime_error("Write OP: Failed to prepare statement");
    }

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, static_cast<sqlite3_int64>(csum));

    if (SQLITE_DONE != sqlite3_step(stmt)) 
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute statement");
    }

    sqlite3_finalize(stmt);
}

std::string Database::read(std::string const& key)
{
    sqlite3_stmt* stmt;
    const char* sql = "SELECT value, checksum FROM storage WHERE key = ?;";

    if (SQLITE_OK != sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr)) 
    {
        throw std::runtime_error("Read OP: Failed to prepare statement");
    }

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_STATIC);

    std::string value;
    size_t csum;

    if (SQLITE_ROW == sqlite3_step(stmt)) 
    {
        value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        csum = static_cast<size_t>(sqlite3_column_int64(stmt, 1));
    } 
    else
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Key not found");
    }

    sqlite3_finalize(stmt);

    if (csum != checksum(value)) 
    {
        throw std::runtime_error("Data corruption detected");
    }

    return value;
}


void Database::corruptor(std::string const& key, std::string const& value)
{
    
    sqlite3_stmt* stmt;
    const char* sql = "REPLACE INTO storage (key, value, checksum) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK) 
    {
        throw std::runtime_error("Write OP: Failed to prepare statement");
    }

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, static_cast<sqlite3_int64>(12345));

    if (SQLITE_DONE != sqlite3_step(stmt)) 
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute statement");
    }

    sqlite3_finalize(stmt);
}