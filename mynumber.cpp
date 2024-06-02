#include "mynumber.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <stdexcept>
#include "mystring.h"
#include "myobject.h"

MyNumber::MyNumber() {}

void MyNumber::loadFromFile(std::istream &in)
{
    std::string str;
    i = 0;
    while ((in.peek() <= '9' && in.peek() >= '0') ||
           in.peek() == '.' || in.peek() == 'E' || in.peek() == 'e' ||
           in.peek() == '+' || in.peek() == '-')
    {
        str.push_back(in.get());
    }

    if (str[0] == '-')
    {
        signOfNumber = -1;
        ++i;
    }

    if (str[i] == '0')
    {
        ++i;
        if (i < str.size())
        {
            if (str[i] == '.')
            {
                seenFraction(str);
                if (i < str.size())
                {
                    if (str[i] == 'E' || str[i] == 'e')
                        seenExponent(str);
                    if (i != str.size())
                        throw std::runtime_error("Invalid format in number after processing fractional part");
                }
            }
            else
                throw std::runtime_error("Invalid format in number: unexpected character after '0'");
        }
    }
    else if (str[i] >= '1' && str[i] <= '9')
    {
        result = seenNumber(str);
        if (i + 1 < str.size())
        {
            if (str[i] == '.')
            {
                seenFraction(str);
                if (i < str.size() && (str[i] == 'E' || str[i] == 'e'))
                {
                    seenExponent(str);
                }
                else if (str.size() != i)
                    throw std::runtime_error("Invalid format in number after processing fractional part");
            }
            else if (str[i] == 'E' || str[i] == 'e')
            {
                seenExponent(str);
                if (str.size() != i)
                    throw std::runtime_error("Invalid format in number after processing exponent");
            }
            else
                throw std::runtime_error("Invalid format in number: unexpected character after number");
        }
    }
    else
    {
        std::cout << str[i];
        throw std::runtime_error("Invalid format in number: unexpected character at the start");
    }
    result *= signOfNumber;
    readWhitespaces(in);
}

void MyNumber::saveToFile(std::ostream &out)
{
    out << result;
}

int MyNumber::seenNumber(const std::string &n)
{
    int num = 0;
    while (i < n.size() && n[i] >= '0' && n[i] <= '9')
    {
        num = num * 10 + (n[i] - '0');
        ++i;
    }
    return num;
}

void MyNumber::seenExponent(const std::string &n)
{
    ++i;
    int singOfExponent = 1;
    if (i < n.size() && (n[i] == '-' || n[i] == '+'))
    {
        if (n[i] == '-')
        {
            singOfExponent = -1;
        }
        ++i;
    }

    if (i < n.size() && n[i] >= '0' && n[i] <= '9')
    {
        int expPart = seenNumber(n);
        result *= pow(10, expPart * singOfExponent);
    }
    else
        throw std::runtime_error("Invalid format: expected digits for exponent");
}

void MyNumber::seenFraction(const std::string &n)
{
    const size_t fractIndex = i;
    ++i;
    if (i < n.size() && n[i] >= '0' && n[i] <= '9')
    {
        int fractPart = seenNumber(n);
        result += fractPart * pow(10, fractIndex - i + 1);
    }
    else
        throw std::runtime_error("Invalid format: expected digits after decimal point");
}

MyValue *MyNumber::clone() { return new MyNumber(*this); }
MyValue *MyNumber::getValue(std::string &s) { return nullptr; }
MyValue *MyNumber::getValueFromPath(std::vector<std::string> path) { return nullptr; }

void MyNumber::print()
{
    std::cout << result;
}

void MyNumber::search(std::string &key) {}
void MyNumber::create(std::vector<std::string> path, MyValue *value) {}
void MyNumber::ddelete(std::vector<std::string> path) {}
void MyNumber::set(std::vector<std::string> path, MyValue *value) {}
