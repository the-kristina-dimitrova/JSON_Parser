#pragma once
#include "myvalue.h"
#include <iostream>
#include <vector>

enum Constants
{
    mytrue,
    myfalse,
    mynull
};

class MyConstant : public MyValue
{
private:
    Constants value;

public:
    MyConstant();

    void loadFromFile(std::istream &);
    void saveToFile(std::ostream &);

    MyValue *clone();
    MyValue *getValue(std::string &);
    MyValue *getValueFromPath(std::vector<std::string>);

    void print();
    void create(std::vector<std::string> path, MyValue *value);
    void ddelete(std::vector<std::string> path);
    void search(std::string &key);
    void set(std::vector<std::string> path, MyValue *value);
};