#pragma once
#include <cstring>
#include <vector>
#include <fstream>

class MyValue
{
protected:
    static bool isIn(const char &, const char *);
    static void readWhitespaces(std::istream &);
    static char whitespaces[5];

public:
    virtual void loadFromFile(std::istream &in) = 0;
    virtual void saveToFile(std::ostream &out) = 0;

    virtual MyValue *clone() = 0;
    virtual MyValue *getValue(std::string &key) = 0;
    virtual MyValue *getValueFromPath(std::vector<std::string>path) = 0;

    virtual void print() = 0;
    virtual void search(std::string &key) = 0;
    virtual void create(std::vector<std::string> pathKeys, MyValue *value) = 0;
    virtual void ddelete(std::vector<std::string> pathKeys) = 0;
    virtual void set(std::vector<std::string> pathKeys, MyValue *value) = 0;

    static MyValue *valueFactory(std::istream &);
};