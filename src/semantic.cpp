#include "semantic.h"
#include "globals.h"
#include "symtab.h"
#include <iostream>
#include <string>

std::string scope = "global";

static void traverse(TreeNode *node) {
  if (node == nullptr)
    return;

  if (node->nodeKind == ExpressionK && node->kind.exp == IdK) {
    int loc =
        st_lookup(node->attr.name, const_cast<char *>(scope.c_str()), VAR_SYM);
    if (loc == -1) {
      std::cerr << "Erro semântico: variável '" << node->attr.name
                << "' não declarada. Na linha " << node->lineno << ".";
      exit(1);
    }
  }

  if (node->nodeKind == StatementK && node->kind.stmt == AssignK) {
    if (node->children[0] && node->children[1] &&
        node->children[0]->type != node->children[1]->type) {
      std::cerr << "Erro semântico: tipos incompatíveis em atribuição";
      if (node->attr.name)
        std::cerr << " para '" << node->attr.name << "'";
      std::cerr << "." << std::endl;
      exit(1);
    }
  }

  if (node->nodeKind == StatementK && node->kind.stmt == VarDeclK) {
    if (st_lookup(node->attr.name, const_cast<char *>(scope.c_str()),
                  VAR_SYM) != -1) {
      std::cerr << "Erro semântico: variável '" << node->attr.name
                << "' já declarada. Na linha " << node->lineno << ".";
      exit(1);
    }
    st_insert(node->attr.name, const_cast<char *>(scope.c_str()), node->lineno,
              getNextMemLoc(), VAR_SYM, node->type);
  }

  if (node->nodeKind == StatementK && node->kind.stmt == FunDeclK) {
    if (st_lookup(node->attr.name, const_cast<char *>(scope.c_str()),
                  FUN_SYM) != -1) {
      std::cerr << "Erro semântico: função '" << node->attr.name
                << "' já declarada. Na linha " << node->lineno << ".";
      exit(1);
    }
    st_insert(node->attr.name, const_cast<char *>(scope.c_str()), node->lineno,
              -1, FUN_SYM, node->type);
    scope = node->attr.name;
  }

  for (int i = 0; i < MAX_CHILDREN; i++) {
    traverse(node->children[i]);
  }

  if (node->nodeKind == StatementK && node->kind.stmt == FunDeclK) {
    scope = "global";
  }
  traverse(node->sibling);
}

void semanticCheck(TreeNode *tree) { traverse(tree); }
