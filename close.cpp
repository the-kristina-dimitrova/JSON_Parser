#include <iostream>
#include "close.h"

void Close::execute()
{
    if (!fs.is_open())
        std::cout << "The file is already closed" << std::endl;
    else
    {
        fs.close();
        if (!fs.is_open())
            std::cout << "The file is closed successfully" << std::endl;
        else
            std::cout << "Closing of file failed" << std::endl;
    }
}
