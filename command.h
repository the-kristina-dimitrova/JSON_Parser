#pragma once
#include <iostream>
#include "myvalue.h"

class Command
{
public:
    virtual void execute() = 0;
};