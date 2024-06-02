#include <iostream>
#include <fstream>
#include <vector>

#include "myvalue.h"
#include "myobject.h"
#include "myarray.h"
#include "mystring.h"
#include "myconstants.h"
#include "mynumber.h"

char MyValue::whitespaces[5] = {' ', '\n', '\r', '\t'};

bool MyValue::isIn(const char &c, const char *array)
{
    for (int i = 0; i < 4; i++)
    {
        if (array[i] == c)
            return true;
    }
    return false;
}

void MyValue::readWhitespaces(std::istream &in)
{
    while (isIn(in.peek(), whitespaces) && !in.eof())
    {
        in.get();
    }
}

MyValue *MyValue::valueFactory(std::istream &in)
{

    if (in.peek() == '{')
    {
        return new MyObject();
    }
    else if (in.peek() == '[')
    {
        return new MyArray();
    }
    else if (in.peek() == '"')
    {
        return new MyString();
    }
    else
    {
        if (in.peek() == 't' || in.peek() == 'f' || in.peek() == 'n')
        {
            return new MyConstant();
        }
        else
        {
            return new MyNumber();
        }
    }
}
