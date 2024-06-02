#pragma once
#include <iostream>
#include "command.h"

class Help : public Command
{
public:
    void execute();
};