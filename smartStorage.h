#pragma once

#include "interfaceStorage.h"

#include <mutex>
#include <string>
#include <iostream>
#include <memory>

/**
 * @brief Smart storage class. Used to write and read to a specific file.
 * 
 */
class SmartStorage
{
public:
    SmartStorage(std::unique_ptr<InterfaceStorage> storage) : m_storage(std::move(storage)) {};
    ~SmartStorage() = default;

    /**
     * @brief 
     * 
     * @param key Position for the value to be written to.
     * @param val value to be written.
     */
    void write(int const& key, std::string const& val);

    /**
     * @brief Reads value from a key position.
     * 
     * @param key Position in the file.
     * @return std::string string saved on that position.
     */
    std::string read(int const& key);

    /**
     * @brief List all entries in the file.
     * 
     */
    void listAll();

    /**
     * @brief Corrupts the file.
     * 
     * @param key Position where corruption should be.
     * @param value value to write.
     */
    void corruptor(int const& key, std::string const& value);

private:
    std::mutex m_mtx;
    std::unique_ptr<InterfaceStorage> m_storage;
};