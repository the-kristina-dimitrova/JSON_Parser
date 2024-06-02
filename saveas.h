#pragma once
#include <vector>
#include <cstring>
#include "open.h"

class SaveAs : public Open
{
private:
    std::string filePath;
    std::string objPath;
    bool hasObjPath = false;

public:
    SaveAs(std::string &path);                    // for file
    SaveAs(std::string &file, std::string &path); // for objects
    void execute();
};