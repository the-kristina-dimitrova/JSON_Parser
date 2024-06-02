#include <vector>
#include <cstring>
#include <iostream>
#include <filesystem>
#include "save.h"

Save::Save()
{
    fs.close();
    fs.open(std::filesystem::path(address), std::ios::out | std::ios::trunc);
}

Save::Save(std::string &_path)
{
    fs.close();
    fs.open(std::filesystem::path(address), std::ios::out | std::ios::trunc);
    path = _path;
    hasObjPath = true;
}

void Save::execute()
{
    if (!fs.is_open())
        std::cout << "The file is already closed" << std::endl;
    else
    {
        if (hasObjPath)
        {
            std::vector<std::string> keys = split(path, '/');
            MyValue *value = json->getValueFromPath(keys);
            value->saveToFile(fs);
        }
        else
        {
            json->saveToFile(fs);
        }
    }
}