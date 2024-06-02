#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "myarray.h"
#include "myobject.h"

MyArray::MyArray() {}

MyArray::~MyArray()
{
    clear();
}

MyArray::MyArray(const MyArray &other)
{
    copy(other);
}

MyArray &MyArray::operator=(const MyArray &other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }
    return *this;
}

void MyArray::clear()
{
    for (int i = 0; i < arr.size(); i++)
    {

        delete arr[i];
    }
    arr.clear();
}

void MyArray::copy(const MyArray &other)
{
    for (int i = 0; i < other.arr.size(); i++)
    {
        this->arr[i] = other.arr[i]->clone();
    }
}

MyValue *MyArray::clone()
{
    return new MyArray(*this);
}

void MyArray::loadFromFile(std::istream &in)
{
    if (in.get() != '[')
    {
        throw std::runtime_error("It's not an array");
        return;
    }
    readWhitespaces(in);
    MyValue *v;
    v = v->valueFactory(in);
    v->loadFromFile(in);
    arr.push_back(v);
    readWhitespaces(in);
    while (in.peek() == ',')
    {
        in.get();
        readWhitespaces(in);
        v = v->valueFactory(in);
        v->loadFromFile(in);
        arr.push_back(v);
        readWhitespaces(in);
    }
    if (in.get() != ']')
    {
        throw std::runtime_error("Unexpected end of file inside array.");
    }
    readWhitespaces(in);
}

void MyArray::saveToFile(std::ostream &out)
{
    out << "[\n";
    for (int i = 0; i < arr.size(); i++)
    {

        arr[i]->saveToFile(out);
        if (i != arr.size() - 1)
            out << " , \n";
    }
    out << "\n]";
}

void MyArray::print()
{
    std::cout << "[";
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i]->print();
        if (i != arr.size() - 1)
            std::cout << " ,\n ";
    }
    std::cout << "]";
}

void MyArray::setValue(std::string &path, MyValue *value)
{
    int x = stoi(path);
    arr[x] = value;
}

MyValue *MyArray::getValue(std::string &s)
{
    int i = stoi(s); // throws exception if argument is unvalid
    return arr[i];
}

MyValue *MyArray::getValueFromPath(std::vector<std::string> path)
{
    MyValue *result = nullptr;
    if (path.size() == 1)
    {
        result = getValue(path.front());
    }
    else
    {
        MyValue *value = getValue(path.front());
        path.erase(path.begin());
        value->getValueFromPath(path);
    }
    return result;
}

void MyArray::search(std::string &key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i]->search(key);
    }
}

void MyArray::create(std::vector<std::string> path, MyValue *value)
{
    if (path.size() == 1)
    {
        if (getValue(path.front()) != nullptr || stoi(path.front()) != arr.size())
        {
            if (stoi(path.front()) > arr.size())
                throw std::runtime_error("Can not be created object on the given path");
            else
                throw std::runtime_error("There is object on the given path");
        }
        else
        {
            arr.push_back(value);
        }
    }
    else
    {
        if (stoi(path.front()) != arr.size())
        {
            path.erase(path.begin());
            MyValue *obj = new MyObject();
            arr.push_back(obj);
            obj->create(path, value);
        }
        else
        {
            path.erase(path.begin());
            arr[stoi(path.front())]->create(path, value);
        }
    }
}

void MyArray::ddelete(std::vector<std::string> path)
{
    if (path.size() == 1)
    {
        int i = stoi(path.front());
        arr.erase(arr.begin() + i);
    }
    else
    {
        MyValue *object = getValue(path.front());
        path.erase(path.begin());
        object->ddelete(path);
    }
}

void MyArray::set(std::vector<std::string> path, MyValue *value)
{
    if (path.size() == 1)
    {
        setValue(path.front(), value);
    }
    else
    {
        MyValue *object = getValue(path.front());
        path.erase(path.begin());
        object->set(path, value);
    }
}
