#include <vector>
#include <cstring>
#include "move.h"

Move::Move(std::string &_fromPath, std::string &_toPath)
{
    fromPath = _fromPath;
    toPath = _toPath;
}

void Move::execute()
{
    if (!fs.is_open())
        std::cout << "The file is already closed" << std::endl;
    else
    {
        MyValue *value = nullptr;
        std::vector<std::string> fromKeys = split(fromPath, '/');
        std::vector<std::string> toKeys = split(toPath, '/');

        value = json->getValueFromPath(fromKeys);
        json->ddelete(fromKeys);
        json->set(toKeys, value);
    }
}
