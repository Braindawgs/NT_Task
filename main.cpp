#include "smartStorage.h"
#include "database.h"

#include <iostream>
#include <sstream>
#include <algorithm>

/**
 * @brief Checks if the string contains only numbers.
 * 
 * @param str User input string.
 * @return int Number representation, otherwise error -1.
 */
int isValidNumber(std::string const& str) 
{
    int choice = -1;
    bool is_ok = (!str.empty() && std::all_of(str.begin(), str.end(), ::isdigit));

    if (is_ok)
    {
        std::stringstream ss(str);
        ss >> choice;
    }

    return choice;
}

int main()
{
    std::unique_ptr<SmartStorage> storage;

    try
    {
        storage = std::make_unique<SmartStorage>(std::make_unique<Database>());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Exiting due to a failure..." << std::endl;
        exit(1);
    }

    try
    {
        int key = 1;
        int choice = -1;
        std::string line;

        do 
        {
            std::cout << "--------------" << std::endl;
            std::cout << "Options:\n";
            std::cout << "1) Write\n";
            std::cout << "2) Read\n";
            std::cout << "3) List all entries\n";
            std::cout << "4) Corrupt\n"; 
            std::cout << "5) Quit\n";
            std::cout << "--------------" << std::endl;

            std::getline(std::cin, line);
            choice = isValidNumber(line);

            switch (choice)
            {
                case 1:
                {
                    std::string txt;
                    std::cout << "Enter text:";
                    std::getline(std::cin, txt);

                    storage->write(key, txt);
                    std::cout << "Text:\"" << txt << "\" is saved on position " << key << std::endl;
                    key++;
                }
                break;
                case 2:
                {
                    std::string crow;
                    std::getline(std::cin, crow);
                    int row = isValidNumber(crow);

                    try
                    {
                        std::cout << storage->read(row) << std::endl;
                    }
                    catch(const std::exception& e)
                    {
                        
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                }
                break;
                case 3:
                {
                    storage->listAll();
                }
                break;
                case 4:
                {
                    std::cout << "Which row to corrupt:";

                    std::string crow;
                    std::getline(std::cin, crow);
                    int row = isValidNumber(crow);

                    storage->corruptor(row, "CoRRuPtiiiiNg:!11!230###21");
                }
                break;
                case 5:
                {
                    std::cout << "Exiting..." << std::endl;
                }
                break;
                default:
                    std::cerr << "Non valid option selected" << std::endl;
            }
        } while(5 != choice);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

