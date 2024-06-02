#include "myobject.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include "mystring.h"
#include <vector>

MyObject::MyObject() {}

MyObject::~MyObject()
{
    clear();
}

MyObject::MyObject(const MyObject& other)
{
    copy(other);
}
MyObject& MyObject::operator=(const MyObject& other)
{
    if(this!= &other)
    {
        clear();
        copy(other);
    }
    return *this;
}

void MyObject::clear()
{
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i].value;
    }
    objects.clear();
}

void MyObject::copy(const MyObject &other)
{
    for (int i = 0; i < other.objects.size(); i++)
    {
        pair p;
        p.key = other.objects[i].key;
        p.value = other.objects[i].value->clone();
        objects.push_back(p);
        delete p.value;
    }
}

MyValue *MyObject::clone()
{
    return new MyObject(*this);
}

void MyObject::setValue(std::string &key, MyValue *value)
{
    MyString searchKey(key);
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].key == searchKey)
        {
            objects[i].value = value;
        }
    }
}

MyValue *MyObject::getValue(std::string &key)
{
    MyString searchKey(key);
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].key == searchKey)
        {
            return objects[i].value;
        }
    }
    return nullptr;
}

void MyObject::readPair(std::istream &in)
{
    pair p;
    p.key.loadFromFile(in);
    readWhitespaces(in);

    if (in.get() != ':')
    {
        throw "Error with object syntax, missing : ";
    }
    readWhitespaces(in);
    p.value = p.value->valueFactory(in);
    p.value->loadFromFile(in);
    readWhitespaces(in);
    objects.push_back(p);
}

void MyObject::loadFromFile(std::istream &in)
{
    char x = in.get();
    if (x != '{')
    {
        throw std::runtime_error("It's not an object");
        return;
    }
    readWhitespaces(in);
    if (in.peek() == '}')
        return;

    readPair(in);

    while (in.peek() == ',')
    {
        in.get();
        readWhitespaces(in);
        readPair(in);
    }

    if (in.get() != '}')
    {
        throw std::runtime_error("Invalid object syntax");
    }
    readWhitespaces(in);
}

void MyObject::saveToFile(std::ostream &out)
{
    out << "{\n";
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i].key.saveToFile(out);
        out << " : ";
        objects[i].value->saveToFile(out);
        if (i != objects.size() - 1)
            out << " ,\n";
    }
    out << "\n} ";
}

void MyObject::print()
{
    std::cout << "{";
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i].key.print();
        std::cout << " : ";
        objects[i].value->print();
        if (i != objects.size() - 1)
            std::cout << " , " << std::endl;
    }
    std::cout << "}";
}

void MyObject::search(std::string &key)
{
    if (getValue(key) != nullptr)
    {
        getValue(key)->print();
    }
    for (int i = 0; i < objects.size(); i++)
    {

        objects[i].value->search(key);
    }
}

void MyObject::create(std::vector<std::string> path, MyValue *value)
{
    if (path.size() == 1)
    {
        if (getValue(path.front()) != nullptr)
        {
            throw std::runtime_error("There is object on the given path");
        }
        else
        {
            pair temp;
            MyString skey(path.front());
            temp.key = skey;
            temp.value = value;
            objects.push_back(temp);
        }
    }
    else
    {
        if (getValue(path.front()) == nullptr)
        {
            pair temp;
            MyString skey(path.front());
            temp.key = skey;
            temp.value = new MyObject();
            objects.push_back(temp);
        }
        MyValue *object = getValue(path.front());
        path.erase(path.begin());
        object->create(path, value);
    }
}
void MyObject::ddelete(std::vector<std::string> path)
{
    MyValue *obj = nullptr;
    int index;
    if (path.size() == 1)
    {
        MyString searchKey(path.front());
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i].key == searchKey)
            {
                index = i;
                break;
            }
        }
        objects.erase(objects.begin() + index);
    }
    else
    {
        obj = getValue(path.front());
        path.erase(path.begin());
        obj->ddelete(path);
    }
}

void MyObject::set(std::vector<std::string> path, MyValue *value)
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

MyValue *MyObject::getValueFromPath(std::vector<std::string> path)
{
    MyValue *value = nullptr;
    if (path.size() == 1)
    {
        value = getValue(path.front());
    }
    else
    {
        value = getValue(path.front());
        path.erase(path.begin());
        value = value->getValueFromPath(path);
    }
    return value;
}