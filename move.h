#pragma once
#include <cstring>
#include "open.h"

class Move : public Open
{
private:
    std::string fromPath;
    std::string toPath;

public:
    Move(std::string &from_path, std::string &to_path);
    void execute();
};