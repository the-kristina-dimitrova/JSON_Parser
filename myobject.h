#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "myvalue.h"
#include "mystring.h"

struct pair
{
    MyString key;
    MyValue *value;
};

class MyObject : public MyValue
{
private:
    void readPair(std::istream &);
    void clear();
    void copy(const MyObject &other);

protected:
    std::vector<pair> objects;

public:
    MyObject();
    ~MyObject();
    MyObject(const MyObject &other);
    MyObject &operator=(const MyObject &other);

    void loadFromFile(std::istream &);
    void saveToFile(std::ostream &);

    MyValue *getValue(std::string &key);
    MyValue *clone();
    MyValue *getValueFromPath(std::vector<std::string> path);

    void setValue(std::string &key, MyValue *value);
    void print();
    void search(std::string &key);
    void ddelete(std::vector<std::string> path);
    void set(std::vector<std::string> path, MyValue *value);
    void create(std::vector<std::string>, MyValue *value);
};