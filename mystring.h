#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "myvalue.h"

class MyString : public MyValue
{
private:
    std::string str;

public:
    MyString();
    MyString(const std::string &);

    std::string getStr() const;
    bool operator==(MyString &);

    void loadFromFile(std::istream &);
    void saveToFile(std::ostream &);

    MyValue *clone();
    MyValue *getValue(std::string &);
    MyValue *getValueFromPath(std::vector<std::string>);

    void print();
    void search(std::string &key);
    void create(std::vector<std::string> path, MyValue *value);
    void ddelete(std::vector<std::string> path);
    void set(std::vector<std::string>, MyValue *value);
};