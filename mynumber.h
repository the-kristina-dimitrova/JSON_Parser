#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "myvalue.h"

class MyNumber : public MyValue
{
private:
    float result = 0;
    int signOfNumber = 1;
    size_t i = 0;

    int seenNumber(const std::string &);
    void seenExponent(const std::string &);
    void seenFraction(const std::string &);

public:
    MyNumber();

    void loadFromFile(std::istream &);
    void saveToFile(std::ostream &);

    MyValue *clone();
    MyValue *getValue(std::string &);
    MyValue *getValueFromPath(std::vector<std::string>);

    void print();
    void create(std::vector<std::string>, MyValue *value);
    void ddelete(std::vector<std::string> path);
    void set(std::vector<std::string>, MyValue *value);
    void search(std::string &key);
};
