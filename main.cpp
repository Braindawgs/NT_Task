#include "smartStorage.h"
#include "database.h"

#include <iostream>

int main()
{
    SmartStorage storage(std::make_unique<Database>());

    storage.write("key1", "value1");
    storage.write("key2", "value2");

    auto v1 = storage.read("key1");
    auto v2 = storage.read("key2");
    std::cout << "V1: " << v1 << " V2: " << v2 << std::endl;

    storage.corruptor("key1", "CORRUPTION");
    try
    {
        auto vx = storage.read("key1");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

