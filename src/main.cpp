#include "compiler.h"
#include "globals.h"
#include "symtab.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
  std::cout << "C- Compiler Initialized." << std::endl;
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  openFile(argv[1]);
  TreeNode *tree = parse();
  printSymTab(stdout);
  printTree(tree);

  return 0;
}
