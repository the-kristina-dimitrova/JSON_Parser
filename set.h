#pragma once
#include <iostream>
#include <cstring>
#include "open.h"

class Set : public Open
{
private:
    std::string path;
    std::string newStr;

public:
    Set(std::string &, std::string &);
    void execute();
};