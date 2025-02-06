#ifndef COMPILER_H
#define COMPILER_H

#include "globals.h"

#include "parser.tab.hpp"

void openFile(const char *filename);
TreeNode *parse();

#endif // COMPILER_H
