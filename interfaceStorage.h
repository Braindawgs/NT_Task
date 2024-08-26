#pragma once

#include <string>

class InterfaceStorage
{
public:
    virtual ~InterfaceStorage() = default;

    virtual void write(std::string const& key, std::string const& val) = 0;
    virtual std::string read(std::string const& key) = 0;
    virtual void corruptor(std::string const& key, std::string const& value) = 0;
};