#pragma once
#include <cstring>
#include "open.h"

class Create : public Open
{
private:
    std::string path;
    std::string newStr;

public:
    Create(std::string &, std::string &);
    void execute();
};