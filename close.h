#pragma once
#include <iostream>
#include "open.h"

class Close : public Open
{
public:
    void execute();
};