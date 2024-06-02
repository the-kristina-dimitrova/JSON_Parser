#include "print.h"

void Print::execute()
{
    if (!fs.is_open())
        std::cout << "The file is already closed" << std::endl;
    else
    {
        json->print();
        std::cout << std::endl;
    }
}
