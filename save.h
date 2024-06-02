#pragma once
#include <cstring>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "open.h"

class Save : public Open
{
private:
    std::string path;
    bool hasObjPath = false;

public:
    Save();                  // for file
    Save(std::string &path); // for objects
    void execute();
};
