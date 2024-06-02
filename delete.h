#pragma once
#include <cstring>
#include "open.h"

class Delete : public Open
{
private:
    std::string path;

public:
    Delete(std::string &);
    void execute();
};