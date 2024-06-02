#pragma once
#include <cstring>
#include "open.h"

class Search : public Open
{
private:
    std::string key;

public:
    Search(std::string &args);
    void execute();
};