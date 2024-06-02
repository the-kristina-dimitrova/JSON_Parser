#include <vector>
#include <cstring>
#include <filesystem>
#include "saveas.h"

SaveAs::SaveAs(std::string &_filePath)
{
    filePath = _filePath;
}
SaveAs::SaveAs(std::string &_filePath, std::string &_objPath)
{
    objPath = _objPath;
    filePath = _filePath;
    hasObjPath = true;
}

void SaveAs::execute()
{
    if (!fs.is_open())
        std::cout << "The file is already closed" << std::endl;
    else
    {
        std::fstream file;
        file.open(std::filesystem::path(filePath), std::ios::out | std::ios::trunc);
        if (hasObjPath)
        {
            MyValue *value = nullptr;
            std::vector<std::string> keys = split(objPath, '/');
            value = json->getValueFromPath(keys);
            value->saveToFile(file);
        }
        else
        {
            json->saveToFile(file);
        }
        file.close();
    }
}