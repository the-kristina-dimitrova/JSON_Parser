#include <iostream>
#include "help.h"

void Help::execute()
{
    std::cout << "The following commands are supported:\n"
              << "open <file>	         opens <file> \n"
              << "close			         closes currently opened file \n"
              << "save			         saves the currently open file \n"
              << "save <path>			 saves the object on <path> in the currently open file \n"
              << "saveas <file> <path>	 saves the object on <path> in <file> \n"
              << "saveas <file>	         saves the currently open file in <file> \n"
              << "help			         prints this information \n"
              << "exit			         exists the program\n"
              << "print                  prints the content of the currently opened file\n"
              << "search <key>           finds and prints all the values under the key <key>\n"
              << "set <path> <string>    changes the value on <path> with the <string>\n"
              << "create <path> <string> creates <string> on <path>\n"
              << "delete <path> deletes  the object on <path>\n"
              << "move <from> <to>       moves object on path <from> on the plase of object on path <to>"
              << std::endl;
}
