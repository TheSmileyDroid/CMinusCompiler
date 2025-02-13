#include "compiler.h"
#include "globals.h"
#include "semantic.h"
#include "symtab.h"
#include "utils.h"
#include <clocale>
#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "pt_BR.UTF-8");
  std::cout << "C- Compiler Initialized." << std::endl;
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  openFile(argv[1]);
  TreeNode *tree = parse();
  printTree(tree);
  semanticCheck(tree); // chamada à verificação semântica
  printSymTab(stdout);

  return 0;
}
