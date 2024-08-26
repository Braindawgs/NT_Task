#include "smartStorage.h"

void SmartStorage::write(std::string const& key, std::string const& val)
{
    std::lock_guard<std::mutex> lock(m_mtx); 
    m_storage->write(key, val);
}

std::string SmartStorage::read(std::string const& key)
{
    std::lock_guard<std::mutex> lock(m_mtx); 
    return m_storage->read(key);
}

void SmartStorage::corruptor(std::string const& key, std::string const& value)
{
    std::lock_guard<std::mutex> lock(m_mtx); 
    return m_storage->corruptor(key, value);
}