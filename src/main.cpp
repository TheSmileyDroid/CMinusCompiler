#include "compiler.h"
#include "globals.h"
#include "semantic.h"
#include "symtab.h"
#include "utils.h"
#include <clocale>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "pt_BR.UTF-8");
  std::cout << "\033[32m";
  std::cout << "Compilador para a linguagem C-" << std::endl;
  std::cout << "\033[0m";
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0];
    std::cout << "\033[31m";
    std::cerr << " <arquivo de entrada>" << std::endl;
    std::cout << "\033[0m";
    return 1;
  }
  std::cout << "Abrindo arquivo " << argv[1] << "..." << std::endl;
  openFile(argv[1]);
  std::cout << "Iniciando análise sintática..." << std::endl;
  TreeNode *tree = parse(); // chamada ao parser
  std::cout << "\033[32m";
  std::cout << "Análise sintática concluída." << std::endl;
  std::cout << "\033[0m";
  std::cout << "\033[1;32m";
  std::cout << "Árvore sintática gerada:" << std::endl;
  std::cout << "\033[0m";
  printTree(tree);
  std::cout << "Iniciando análise semântica..." << std::endl;
  semanticCheck(tree); // chamada à verificação semântica
  std::cout << "\033[32m";
  std::cout << "Análise semântica concluída." << std::endl;
  std::cout << "\033[0m";
  std::cout << "\033[1;32m";
  std::cout << "Tabela de símbolos gerada:" << std::endl;
  std::cout << "\033[0m";
  printSymTab(stdout);

  return 0;
}
