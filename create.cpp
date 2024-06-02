#include <cstring>
#include "create.h"

Create::Create(std::string &_path, std::string &_newStr)
{
    path = _path;
    newStr = _newStr;
}

void Create::execute()
{
    if (!fs.is_open())
        std::cout << "The file is already closed" << std::endl;
    else
    {
        std::vector<std::string> keys = split(path, '/');
        std::stringstream ss(newStr);
        MyValue *newValue = MyValue::valueFactory(ss);
        newValue->loadFromFile(ss);
        json->create(keys, newValue);
    }
}