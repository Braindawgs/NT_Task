#pragma once

#include "interfaceStorage.h"

#include <mutex>
#include <string>
#include <iostream>
#include <memory>

class SmartStorage
{
public:
    SmartStorage(std::unique_ptr<InterfaceStorage> storage) : m_storage(std::move(storage)) {};
    ~SmartStorage() = default;

    void write(int const& key, std::string const& val);
    std::string read(int const& key);

    void corruptor(int const& key, std::string const& value);

private:
    std::mutex m_mtx;
    std::unique_ptr<InterfaceStorage> m_storage;
};