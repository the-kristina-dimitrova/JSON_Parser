#include <iostream>
#include <stdexcept>
#include "myconstants.h"
#include "mystring.h"
#include "myobject.h"

MyConstant::MyConstant() {}

void MyConstant::loadFromFile(std::istream &in)
{
    std::string s;
    char x = in.peek();
    for (int i = 0; i < 4; i++)
    {
        s.push_back(in.get());
    }
    if (x == 'f')
    {
        s.push_back(in.get());
    }

    if (s == "true")
        value = Constants::mytrue;
    else if (s == "false")
        value = Constants::myfalse;
    else if (s == "null")
        value = Constants::mynull;
    else
        throw std::runtime_error("Invalid constant");
    readWhitespaces(in);
}

void MyConstant::saveToFile(std::ostream &out)
{
    if (value == Constants::mytrue)
        out << "true";
    else if (value == Constants::myfalse)
        out << "false";
    else if (value == Constants::mynull)
        out << "null";
}

MyValue *MyConstant::clone()
{
    return new MyConstant(*this);
}

MyValue *MyConstant::getValue(std::string &s) { return nullptr; }
MyValue *MyConstant::getValueFromPath(std::vector<std::string> path) { return nullptr; }

void MyConstant::print()
{
    if (value == Constants::mytrue)
        std::cout << "true";
    else if (value == Constants::myfalse)
        std::cout << "false";
    else if (value == Constants::mynull)
        std::cout << "null";
}
void MyConstant::search(std::string &key) {}
void MyConstant::create(std::vector<std::string> path, MyValue *value) {}
void MyConstant::ddelete(std::vector<std::string> path) {}
void MyConstant::set(std::vector<std::string> path, MyValue *value) {}
