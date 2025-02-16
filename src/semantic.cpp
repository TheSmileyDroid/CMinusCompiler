#include "semantic.h"
#include "globals.h"
#include "symtab.h"
#include <iostream>
#include <string>

std::string scope = "global";

DataType getExpressionType(TreeNode *node) {
  if (node->nodeKind == ExpressionK && node->kind.exp == OpK) {
    DataType leftType = getExpressionType(node->children[0]);
    DataType rightType = getExpressionType(node->children[1]);
    if (leftType != rightType) {
      return UNKNOWN_TYPE;
    }
    return leftType;
  } else if (node->nodeKind == ExpressionK && node->kind.exp == ConstK) {
    return INT_TYPE;
  } else if (node->nodeKind == ExpressionK && node->kind.exp == IdK) {
    return st_retrieve(node->attr.name, const_cast<char *>(scope.c_str()),
                       VAR_SYM)
        ->dataType;
  } else if (node->nodeKind == ExpressionK && node->kind.exp == CallK) {
    return st_retrieve(node->attr.name, const_cast<char *>(scope.c_str()),
                       FUN_SYM)
        ->dataType;
  } else if (node->nodeKind == StatementK && node->kind.stmt == ReturnK &&
             node->children[0]) {
    return getExpressionType(node->children[0]);
  } else if (node->nodeKind == StatementK && node->kind.stmt == AssignK) {
    return getExpressionType(node->children[0]);
  }
  return UNKNOWN_TYPE;
}

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
    if (getExpressionType(node) !=
        st_retrieve(node->children[0]->attr.name,
                    const_cast<char *>(scope.c_str()), VAR_SYM)
            ->dataType) {
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

    if (node->children[0]) {
      if (node->children[0]->nodeKind == ExpressionK &&
          node->children[0]->kind.exp == ConstK) {
        skipMemLoc(node->children[0]->attr.val);
      }
    }
  }

  if (node->nodeKind == StatementK && node->kind.stmt == FunDeclK) {
    if (st_lookup(node->attr.name, const_cast<char *>(scope.c_str()),
                  FUN_SYM) != -1) {
      std::cerr << "Erro semântico: função '" << node->attr.name
                << "' já declarada. Na linha " << node->lineno << "."
                << std::endl;
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
    st_insert_func(node->attr.name, const_cast<char *>(scope.c_str()),
                   node->lineno, getNextMemLoc(), FUN_SYM, node->type,
                   paramTypes, paramCount);
    scope = node->attr.name;
  }

  if (node->nodeKind == ExpressionK && node->kind.exp == CallK) {
    if (st_lookup(node->attr.name, const_cast<char *>(scope.c_str()),
                  FUN_SYM) == -1) {
      std::cerr << "Erro semântico: função '" << node->attr.name
                << "' não declarada. Na linha " << node->lineno << "."
                << std::endl;
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
                    << node->attr.name << "'. Na linha " << node->lineno << "."
                    << std::endl;
          printSymTab(stdout);
          exit(1);
        }
        if (getExpressionType(param_node) != fun->paramTypes[i]) {
          std::cerr << "Erro semântico: tipo incompatível para parâmetro "
                    << i + 1 << " da função '" << node->attr.name << "'; '"
                    << param->name << "' era do tipo "
                    << dataTypeToString(getExpressionType(param_node))
                    << " mas esperava-se "
                    << dataTypeToString(fun->paramTypes[i]) << " Na linha "
                    << node->lineno << "." << std::endl;
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

  if (node->nodeKind == StatementK && node->kind.stmt == ReturnK) {
    BucketList fun = st_retrieve(const_cast<char *>(scope.c_str()),
                                 const_cast<char *>(scope.c_str()), FUN_SYM);
    if (getExpressionType(node) != fun->dataType) {
      printSymTab(stdout);
      std::cerr << "Erro semântico: tipo de retorno incompatível para função '"
                << scope << "'. Variável de retorno era do tipo "
                << dataTypeToString(getExpressionType(node))
                << " mas esperava-se " << dataTypeToString(fun->dataType)
                << ". Na linha " << node->lineno << "." << std::endl;

      exit(1);
    }
  }

  if (node->nodeKind == ExpressionK && node->kind.exp == IdK) {
    if (node->children[0]) {
      if (node->children[0]->nodeKind == ExpressionK &&
          node->children[0]->kind.exp == ConstK) {
        if (node->children[0]->attr.val < 0) {
          std::cerr << "Erro semântico: índice negativo para variável '"
                    << node->attr.name << "'. Na linha " << node->lineno << "."
                    << std::endl;
          printSymTab(stdout);
          exit(1);
        }
      }
    }
  }

  if (node->nodeKind == ExpressionK && node->kind.exp == IdK) {
    if (node->children[0]) {
      if (getExpressionType(node->children[0]) != INT_TYPE) {
        std::cerr << "Erro semântico: índice de tipo diferente de int para "
                     "variável '"
                  << node->attr.name << "'. Na linha " << node->lineno << "."
                  << std::endl;
        printSymTab(stdout);
        exit(1);
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
  st_insert_func(const_cast<char *>("output"),
                 const_cast<char *>(scope.c_str()), 0, getNextMemLoc(), FUN_SYM,
                 VOID_TYPE, new DataType[1]{INT_TYPE}, 1);
}

void semanticCheck(TreeNode *tree) {
  addIOFunctions();
  traverse(tree);
}
