#include "compiler.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "C- Compiler Initialized." << std::endl;
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  openFile(argv[1]);
  parse();

  return 0;
}
