#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
#include <filesystem>
#include "open.h"

std::string Open::address = "";
std::fstream Open::fs;
MyValue *Open::json = nullptr;

Open::Open() {}

Open::Open(std::string &_address)
{
    address = _address;
}

std::vector<std::string> Open::split(std::string &s, char delimiter)
{
    if (s == "")
        throw std::runtime_error("Path must not be empty");
    std::vector<std::string> keys;
    std::string key;
    std::istringstream keyStream(s);
    while (std::getline(keyStream, key, delimiter))
    {
        keys.push_back(key);
    }
    return keys;
}

void Open::readWhitespaces(std::istream &in)
{
    while ((in.peek() == ' ' || in.peek() == '\n' || in.peek() == '\r' || in.peek() == '\t') && !in.eof())
    {
        in.get();
    }
}

void Open::execute()
{
    fs.open(std::filesystem::path(address), std::ios::in);

    if (fs.is_open())
        std::cout << "The file \"" << address << "\" is opened SUCCESSFULLY" << std::endl;
    else
        std::cout << "The file" << address << " is NOT opened" << std::endl;

    readWhitespaces(fs);
    json = json->valueFactory(fs);
    json->loadFromFile(fs);
}

Open::~Open()
{
    delete json;
}