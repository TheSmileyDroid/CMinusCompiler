#include "compiler.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "C- Compiler Initialized." << std::endl;
  openFile(argv[1]);
  parse();

  return 0;
}
