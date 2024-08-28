#include "smartStorage.h"

void SmartStorage::write(int const& key, std::string const& val)
{
    std::lock_guard<std::mutex> lock(m_mtx); 

    auto cs = checksum(val);
    m_storage->write(key, val + ":" + std::to_string(cs));
}

std::string SmartStorage::read(int const& key)
{
    std::lock_guard<std::mutex> lock(m_mtx); 
    std::string value = m_storage->read(key);

    return validateData(value);
}

void SmartStorage::listAll()
{
    std::lock_guard<std::mutex> lock(m_mtx); 
    return m_storage->listAll();
}

void SmartStorage::corruptor(int const& key, std::string const& value)
{
    std::lock_guard<std::mutex> lock(m_mtx); 
    return m_storage->write(key, value);
}

size_t SmartStorage::checksum(std::string const& data)
{
    return std::hash<std::string>{}(data);
}

std::string SmartStorage::validateData(std::string& data)
{
    size_t pos = data.find_last_of(':');

    if (std::string::npos == pos)
    {
        throw std::runtime_error("Corruption: checksum missing");
    }

    std::string retStr = data.substr(0, pos);
    std::string csum = data.substr(pos + 1);

    if (csum != std::to_string(checksum(retStr)))
    {
        throw std::runtime_error("Data corruption detected");
    }

    return retStr;
}