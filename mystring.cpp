#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "mystring.h"

MyString::MyString() {}

MyString::MyString(const std::string &_str)
{
    str = _str;
}

std::string MyString::getStr() const
{
    return str;
}

bool MyString::operator==(MyString &other)
{
    return this->str == other.getStr();
}

void MyString::loadFromFile(std::istream &in)
{
    if (in.get() != '\"' || in.eof())
    {
        throw std::runtime_error("String must start with a double quote.");
    }

    while (!in.eof())
    {
        char ch = in.get();

        if (ch == '\"')
        {
            // End of the string
            return;
        }
        else if (ch == '\\')
        {
            // Handle escape sequences
            ch = in.get();
            if (in.eof())
            {
                throw std::runtime_error("Unexpected end of file after escape character in string.");
            }

            switch (ch)
            {
            case '\"':
                str.push_back('\"');
                break;
            case '\\':
                str.push_back('\\');
                break;
            case '/':
                str.push_back('/');
                break;
            case 'b':
                str.push_back('\b');
                break;
            case 'f':
                str.push_back('\f');
                break;
            case 'n':
                str.push_back('\n');
                break;
            case 'r':
                str.push_back('\r');
                break;
            case 't':
                str.push_back('\t');
                break;
            case 'u':
            {
                // Handle unicode escape sequence
                // from here I used code from internet
                std::string hex;
                for (int i = 0; i < 4; ++i)
                {
                    if (std::isxdigit(in.peek()))
                    {
                        hex.push_back(in.get());
                    }
                    else
                    {
                        throw std::runtime_error("Invalid unicode escape sequence in string.");
                    }
                }
                int symbol;
                std::istringstream(hex) >> std::hex >> symbol;
                if (symbol <= 0x7F)
                {
                    str.push_back((char)(symbol));
                }
                else if (symbol <= 0x7FF)
                {
                    str.push_back((char)(0xC0 | (symbol >> 6)));
                    str.push_back((char)(0x80 | (symbol & 0x3F)));
                }
                else
                {
                    str.push_back((char)(0xE0 | (symbol >> 12)));
                    str.push_back((char)(0x80 | ((symbol >> 6) & 0x3F)));
                    str.push_back((char)(0x80 | (symbol & 0x3F)));
                }
                // to here I used code from internet
                readWhitespaces(in);
                break;
            }
            default:
                throw std::runtime_error("Unknown escape sequence in string.");
            }
        }
        else
        {
            str.push_back(ch);
        }
        readWhitespaces(in);
    }

    throw std::runtime_error("Unexpected end of file inside string.");
}

void MyString::saveToFile(std::ostream &out)
{
    out << '"' << str << "\" ";
}

MyValue *MyString::clone()
{
    MyValue *p = new MyString(*this);
    return p;
}

MyValue *MyString::getValue(std::string &s) { return nullptr; }
MyValue *MyString::getValueFromPath(std::vector<std::string> path) { return nullptr; }

void MyString::print()
{
    std::cout << "\"" << str << "\"";
}
void MyString::search(std::string &key) {}
void MyString::create(std::vector<std::string> path, MyValue *value) {}
void MyString::ddelete(std::vector<std::string> path) {}
void MyString::set(std::vector<std::string>, MyValue *value) {}
