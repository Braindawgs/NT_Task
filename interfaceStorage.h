#pragma once

#include <string>

class InterfaceStorage
{
public:
    virtual ~InterfaceStorage() = default;

    virtual void write(int const& key, std::string const& val) = 0;
    virtual std::string read(int const& key) = 0;
    virtual void corruptor(int const& key, std::string const& value) = 0;
};