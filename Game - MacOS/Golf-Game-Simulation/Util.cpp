#include "Util.h"
#include <random>
#include <iostream>
#include <cstring>
#include <cstdlib>

int randInt(int min, int max)
{
    if (max < min)
        std::swap(max, min);
    static std::random_device rd;
    static std::default_random_engine generator(rd());
    std::uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

void enterToContinue()
{
    std::cin.ignore(10000, '\n');
    std::cout << "Press enter to continue ";
    std::cin.ignore();
}

bool invalidInput()
{
    std::cout << "Invalid input" << std::endl;
    enterToContinue();
    return false;
}

void clearScreen()  // will just write a newline in an Xcode output window
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
