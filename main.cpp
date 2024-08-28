#include "smartStorage.h"
#include "database.h"

#include <iostream>

int main()
{
    SmartStorage storage(std::make_unique<Database>());

    int choice;
    int key = 1;
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
        std::cin >> choice;

        // Error safety
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
            case 1:
            {
                std::string txt;
                std::cout << "Enter text:";
                std::cin.ignore();
                std::getline(std::cin, txt);

                storage.write(key, txt);
                std::cout << "Text:\"" << txt << "\" is saved on position " << key << std::endl;
                key++;
            }
            break;
            case 2:
            {
                int row;
                std::cout << "Enter row to be read:";
                std::cin >> row;

                try
                {
                    std::cout << storage.read(row) << std::endl;
                }
                catch(const std::exception& e)
                {
                    
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
            break;
            case 3:
            {
                storage.listAll();
            }
            break;
            case 4:
            {
                int row;
                std::cout << "Which row to corrupt:";
                std::cin >> row;
                storage.corruptor(row, "CoRRuPtiiiiNg:!11!230###21");
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
    
    return 0;
}

