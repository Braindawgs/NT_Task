#pragma once

#include <string>

/**
 * @brief Interface for storages.
 * 
 */
class InterfaceStorage
{
public:
    virtual ~InterfaceStorage() = default;

    virtual void write(int const& key, std::string const& val) = 0;
    virtual std::string read(int const& key) = 0;
    virtual void listAll() = 0;
};