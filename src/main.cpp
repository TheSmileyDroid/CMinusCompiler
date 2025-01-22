#include <iostream>
#include "compiler.h"
#include "parser.tab.h"

int main(int argc, char *argv[])
{
    std::cout << "C- Compiler Initialized." << std::endl;
    openFile(argv[1]);
    parse();

    return 0;
}