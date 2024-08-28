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
                      "key INTEGER PRIMARY KEY, "
                      "value TEXT NOT NULL);";

    char* err = nullptr;
    if (SQLITE_OK != sqlite3_exec(m_db, sql, nullptr, nullptr, &err))
    {
        sqlite3_free(err);
        throw std::runtime_error(err);
    }
}

void Database::write(int const& key, std::string const& value)
{
    sqlite3_stmt* stmt;
    const char* sql = "REPLACE INTO storage (key, value) VALUES (?, ?);";

    if (SQLITE_OK != sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr)) 
    {
        throwAndFinalize(stmt, "Write OP: Failed to prepare statement");
    }

    if (SQLITE_OK != sqlite3_bind_int(stmt, 1, key))
    {
        throwAndFinalize(stmt, "Write OP: Failed to bind key");
    }

    if (SQLITE_OK != sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_STATIC))
    {
        throwAndFinalize(stmt, "Write OP: Failed to bind value");
    }

    if (SQLITE_DONE != sqlite3_step(stmt)) 
    {
        throwAndFinalize(stmt, "Failed to execute statement");
    }

    sqlite3_finalize(stmt);
}

std::string Database::read(int const& key)
{
    sqlite3_stmt* stmt;
    const char* sql = "SELECT value FROM storage WHERE key = ?;";

    if (SQLITE_OK != sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr)) 
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Read OP: Failed to prepare statement");
    }

    if (SQLITE_OK != sqlite3_bind_int(stmt, 1, key))
    {
        throwAndFinalize(stmt, "Read OP: Failed to bind key");
    }

    std::string value;

    if (SQLITE_ROW == sqlite3_step(stmt)) 
    {
        value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    } 
    else
    {
        throwAndFinalize(stmt, "Read OP: Key not found");
    }

    sqlite3_finalize(stmt);

    return value;
}

void Database::listAll()
{
    sqlite3_stmt* stmt;
    const char* sql = "SELECT key, value FROM storage;";

    if (SQLITE_OK != sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr)) 
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("List OP: Failed to prepare statement");
    }

    std::cout << "Listing entries:" << std::endl;
    while (SQLITE_ROW == sqlite3_step(stmt)) 
    {
        int key = sqlite3_column_int(stmt, 0);
        const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Database::corruptor(int const& key, std::string const& value)
{
    
    sqlite3_stmt* stmt;
    const char* sql = "REPLACE INTO storage (key, value) VALUES (?, ?);";

    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK) 
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Write OP: Failed to prepare statement");
    }

    sqlite3_bind_int(stmt, 1, key);
    sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_STATIC);

    if (SQLITE_DONE != sqlite3_step(stmt)) 
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute statement");
    }

    sqlite3_finalize(stmt);
}