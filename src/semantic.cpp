#include "semantic.h"
#include "globals.h"
#include "symtab.h"
#include <iostream>
#include <string>

std::string scope = "global";

static void traverse(TreeNode *node) {
  if (node == nullptr)
    return;

  if (node->nodeKind == StatementK && node->kind.stmt == ParamK &&
      node->type != VOID_TYPE) {
    if (st_lookup(node->attr.name, const_cast<char *>(scope.c_str()),
                  VAR_SYM) != -1) {
      std::cerr << "Erro semântico: parâmetro '" << node->attr.name
                << "' já declarado. Na linha " << node->lineno << "."
                << std::endl;
      printSymTab(stdout);
      exit(1);
    }
    st_insert(node->attr.name, const_cast<char *>(scope.c_str()), node->lineno,
              getNextMemLoc(), VAR_SYM, node->type);
  }

  if (node->nodeKind == ExpressionK && node->kind.exp == IdK) {
    int loc =
        st_lookup(node->attr.name, const_cast<char *>(scope.c_str()), VAR_SYM);
    if (loc == -1) {
      std::cerr << "Erro semântico: variável '" << node->attr.name
                << "' não declarada no escopo de " << scope << ". Na linha "
                << node->lineno << "." << std::endl;

      printSymTab(stdout);
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
      printSymTab(stdout);
      exit(1);
    }
  }

  if (node->nodeKind == StatementK && node->kind.stmt == VarDeclK) {
    if (st_lookup(node->attr.name, const_cast<char *>(scope.c_str()),
                  VAR_SYM) != -1) {
      std::cerr << "Erro semântico: variável '" << node->attr.name
                << "' já declarada. Na linha " << node->lineno << "."
                << std::endl;
      printSymTab(stdout);
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
      printSymTab(stdout);
      exit(1);
    }
    TreeNode *child = node->children[0];
    DataType *paramTypes = nullptr;
    int paramCount = 0;
    while (child) {
      paramCount++;
      paramTypes =
          (DataType *)realloc(paramTypes, paramCount * sizeof(DataType));
      paramTypes[paramCount - 1] = child->type;
      child = child->sibling;
    }
    st_insert(node->attr.name, const_cast<char *>(scope.c_str()), node->lineno,
              getNextMemLoc(), FUN_SYM, node->type, paramTypes, paramCount);
    scope = node->attr.name;
  }

  if (node->nodeKind == ExpressionK && node->kind.exp == CallK) {
    if (st_lookup(node->attr.name, const_cast<char *>(scope.c_str()),
                  FUN_SYM) == -1) {
      std::cerr << "Erro semântico: função '" << node->attr.name
                << "' não declarada. Na linha " << node->lineno << ".";
      printSymTab(stdout);
      exit(1);
    }

    if (node->children[0] && node->children[0]->sibling) {
      TreeNode *param_node = node->children[0];
      BucketList fun = st_retrieve(node->attr.name,
                                   const_cast<char *>(scope.c_str()), FUN_SYM);
      BucketList param =
          st_retrieve(fun->name, const_cast<char *>(scope.c_str()), VAR_SYM);
      int i = 0;
      while (param) {
        if (i >= fun->paramCount) {
          std::cerr << "Erro semântico: número de parâmetros inválido para a "
                       "função '"
                    << node->attr.name << "'. Na linha " << node->lineno << ".";
          printSymTab(stdout);
          exit(1);
        }
        if (param->dataType != fun->paramTypes[i]) {
          std::cerr << "Erro semântico: tipo incompatível para parâmetro "
                    << i + 1 << " da função '" << node->attr.name << "'; '"
                    << param->name << "' era do tipo "
                    << dataTypeToString(param->dataType) << " mas esperava-se "
                    << dataTypeToString(fun->paramTypes[i]) << " Na linha "
                    << node->lineno << ".";
          printSymTab(stdout);
          exit(1);
        }
        param_node = param_node->sibling;
        param = st_retrieve(param_node->attr.name,
                            const_cast<char *>(scope.c_str()), VAR_SYM);
        i++;
      }
    }
  }

  for (int i = 0; i < MAX_CHILDREN; i++) {
    traverse(node->children[i]);
  }

  if (node->nodeKind == StatementK && node->kind.stmt == FunDeclK) {
    scope = "global";
  }
  traverse(node->sibling);
}

void addIOFunctions() {
  st_insert(const_cast<char *>("input"), const_cast<char *>(scope.c_str()), 0,
            getNextMemLoc(), FUN_SYM, INT_TYPE);
  st_insert(const_cast<char *>("output"), const_cast<char *>(scope.c_str()), 0,
            getNextMemLoc(), FUN_SYM, VOID_TYPE, new DataType[1]{INT_TYPE}, 1);
}

void semanticCheck(TreeNode *tree) {
  addIOFunctions();
  traverse(tree);
}
