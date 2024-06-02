#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "myvalue.h"
#include "myarray.h"
#include "mynumber.h"
#include "myobject.h"
#include "mystring.h"
#include "myconstants.h"

#include "close.h"
#include "search.h"
#include "print.h"
#include "set.h"
#include "create.h"
#include "delete.h"
#include "saveas.h"
#include "save.h"
#include "move.h"
#include "command.h"
#include "help.h"
#include "open.h"

void inputArgs(std::string &input, std::string &cmd, std::string &args1, std::string &args2, int &numArgs)
{
    input.clear();
    cmd.clear();
    args1.clear();
    args2.clear();
    bool inCommand = true;
    bool inArgs1 = true;
    bool inArgs2 = true;
    numArgs = 0;

    getline(std::cin, input);
    for (int i = 0; i < input.size(); i++)
    {
        if (inCommand)
        {
            if (input[i] == ' ')
            {
                inCommand = false;
                numArgs++;
            }
            else
                cmd.push_back(input[i]);
        }
        else if (inArgs1)
        {
            if (input[i] == ' ')
            {
                inArgs1 = false;
                numArgs++;
            }
            else
                args1.push_back(input[i]);
        }
        else
        {
            if (input[i] == ' ')
            {
                inArgs2 = false;
            }
            else
                args2.push_back(input[i]);
        }
    }
}

int main()
{
    std::cout<<"Welcome to Kristina's JSON Parser. Please write a command or write \"help\" to print all supported commands"<<std::endl;

    std::string input;
    std::string cmd;
    std::string args1;
    std::string args2;
    int numArgs;
    inputArgs(input, cmd, args1, args2, numArgs);

    Command *c;
    while (cmd != "exit")
    {

        if (cmd == "open" && numArgs == 1)
        {
            c = new Open(args1);
        }
        else if (cmd == "help" && numArgs == 0)
        {
            c = new Help();
        }
        else if (cmd == "close" && numArgs == 0)
        {
            c = new Close();
        }
        else if (cmd == "create" && numArgs == 2)
        {
            c = new Create(args1, args2);
        }
        else if (cmd == "delete" && numArgs == 1)
        {
            c = new Delete(args1);
        }
        else if (cmd == "move" && numArgs == 2)
        {
            c = new Move(args1, args2);
        }
        else if (cmd == "print" && numArgs == 0)
        {
            c = new Print();
        }
        else if (cmd == "search" && numArgs == 1)
        {
            c = new Search(args1);
        }
        else if (cmd == "set" && numArgs == 2)
        {
            c = new Set(args1, args2);
        }
        else if (cmd == "save" && numArgs == 0)
        {
            c = new Save();
        }
        else if (cmd == "save" && numArgs == 1)
        {
            c = new Save(args1);
        }
        else if (cmd == "saveas" && numArgs == 1)
        {
            c = new SaveAs(args1);
        }
        else if (cmd == "saveas" && numArgs == 2)
        {
            c = new SaveAs(args1, args2);
        }
        else
        {
            std::cout << "Wrong command" << std::endl;
        }

        c->execute();

        inputArgs(input, cmd, args1, args2, numArgs);
    }
    std::cout<<"Goodbye!";

    return 0;
}
