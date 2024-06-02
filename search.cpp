#include <vector>
#include <cstring>
#include "search.h"

Search::Search(std::string &_key)
{
    key = _key;
}

void Search::execute()
{
    if (!fs.is_open())
        std::cout << "The file is already closed" << std::endl;
    else
    {
        json->search(key);
    }
}
