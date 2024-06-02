#include <cstring>
#include "delete.h"

Delete::Delete(std::string &_path)
{
    path = _path;
}

void Delete::execute()
{
    if (!fs.is_open())
        std::cout << "The file is already closed" << std::endl;
    else
    {
        std::vector<std::string> keys = split(path, '/');
        json->ddelete(keys);
    }
}
