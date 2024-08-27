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
        std::cout << "Options:\n";
        std::cout << "1) Write\n";
        std::cout << "2) Read\n";
        std::cout << "3) Corrupt\n"; 
        std::cout << "4) Quit\n";
        std::cout << "--------------" << std::endl;
        std::cin >> choice;

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
                int row;
                std::cout << "Which row to corrupt:";
                std::cin >> row;
                storage.corruptor(row, "CoRRuPtiiiiNg");
            }
            break;
            case 4:
            {
                std::cout << "Exiting..." << std::endl;
            }
            break;
            default:
                std::cerr << "Non valid option selected" << std::endl;
        }
    } while(4 != choice);
    
    return 0;
}

