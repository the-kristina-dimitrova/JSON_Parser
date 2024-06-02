#pragma once
#include "command.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Open : public Command
{
private:
    void readWhitespaces(std::istream &in);

protected:
    static std::string address;
    static std::fstream fs;
    static MyValue *json;

public:
    Open();
    Open(std::string &);
    void execute();
    virtual ~Open();
    std::vector<std::string> split(std::string &s, char delimiter);
};