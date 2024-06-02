#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "myvalue.h"

class MyArray : public MyValue
{
private:
    std::vector<MyValue *> arr;
    void clear();
    void copy(const MyArray &other);

public:
    MyArray();
    ~MyArray();
    MyArray(const MyArray& other);
    MyArray& operator=(const MyArray& other);
    

    void loadFromFile(std::istream &);
    void saveToFile(std::ostream &);

    MyValue *clone();
    MyValue *getValue(std::string &);
    MyValue *getValueFromPath(std::vector<std::string>);

    void print();
    void setValue(std::string &path, MyValue *value);

    void search(std::string &key);
    void create(std::vector<std::string> path, MyValue *value);
    void ddelete(std::vector<std::string> path);
    void set(std::vector<std::string> path, MyValue *value);
};