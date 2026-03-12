#include "ShopSystem.h"

#include <iostream>

void ShopSystem::openDebugShop(int &cash)
{
    bool shopping = true;

    while (shopping)
    {
        std::cout << "\n==== SHOP (DEBUG) ====\n"
                  << "Cash: " << cash << "\n"
                  << "1. Debug +10 cash\n"
                  << "2. Debug -10 cash\n"
                  << "3. Leave shop\n> ";

        int option = 0;
        std::cin >> option;

        switch (option)
        {
        case 1:
            cash += 10;
            std::cout << "[DEBUG] Added 10 cash.\n";
            break;

        case 2:
            if (cash >= 10)
            {
                cash -= 10;
                std::cout << "[DEBUG] Removed 10 cash.\n";
            }
            else
            {
                std::cout << "Not enough cash.\n";
            }
            break;

        case 3:
            shopping = false;
            break;

        default:
            std::cout << "Invalid option.\n";
            break;
        }
    }
}
