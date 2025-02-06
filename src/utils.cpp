#include "utils.h"
#include "globals.h"
#include <iostream>

TreeNode *newStmtNode(StatementKind kind) {
  TreeNode *t = new TreeNode;
  for (int i = 0; i < MAX_CHILDREN; i++) {
    t->children[i] = nullptr;
  }
  t->sibling = nullptr;
  t->nodeKind = StatementK;
  t->kind.stmt = kind;
  t->lineno = 0;
  return t;
}

TreeNode *newExpNode(ExpressionKind kind) {
  TreeNode *t = new TreeNode;
  for (int i = 0; i < MAX_CHILDREN; i++) {
    t->children[i] = nullptr;
  }
  t->sibling = nullptr;
  t->nodeKind = ExpressionK;
  t->kind.exp = kind;
  t->lineno = 0;
  t->type = Void;
  return t;
}

void printSpaces(int spaces) {
  for (int i = 0; i < spaces; i++) {
    std::cout << " ";
  }
}

std::string getExpKindStr(ExpressionKind kind) {
  switch (kind) {
  case OpK:
    return "Operador";
  case ConstK:
    return "Constante";
  case IdK:
    return "ID";
  case CallK:
    return "Chamada";
  default:
    return "Desconhecido";
  }
}

std::string getStmtKindStr(StatementKind kind) {
  switch (kind) {
  case IfK:
    return "If";
  case WhileK:
    return "While";
  case ReturnK:
    return "Return";
  case CompoundK:
    return "Compound";
  case AssignK:
    return "Assign";
  case VarDeclK:
    return "VarDecl";
  case FunDeclK:
    return "FunDecl";
  case ParamK:
    return "Param";
  default:
    return "Desconhecido";
  }
}

std::string getExpTypeStr(ExpType type) {
  switch (type) {
  case Void:
    return "void";
  case Int:
    return "int";
  default:
    return "unknown";
  }
}

std::string getTokenStr(int token) {
  switch (token) {
  case PLUS:
    return "+";
  case MINUS:
    return "-";
  case TIMES:
    return "*";
  case DIV:
    return "/";
  case LT:
    return "<";
  case GT:
    return ">";
  case LE:
    return "<=";
  case GE:
    return ">=";
  case EQ:
    return "==";
  case NE:
    return "!=";
  case ASSIGN:
    return "=";
  default:
    return "unknown token";
  }
}

void printTree(TreeNode *tree) {
  static int indentno = 0;

  while (tree != nullptr) {
    printSpaces(indentno);
    if (tree->nodeKind == StatementK) {
      std::cout << "Stmt: " << getStmtKindStr(tree->kind.stmt);
      if (tree->kind.stmt == VarDeclK || tree->kind.stmt == FunDeclK) {
        std::cout << " " << tree->attr.name << " " << getExpTypeStr(tree->type);
      }
      if (tree->kind.stmt == ParamK) {
        if (tree->type != Void) {
          std::cout << " " << getExpTypeStr(tree->type) << " "
                    << tree->attr.name;
        } else {
          std::cout << " void ";
        }
      }

      std::cout << "\n";
    } else if (tree->nodeKind == ExpressionK) {
      std::cout << "Expr: " << getExpKindStr(tree->kind.exp);
      if (tree->kind.exp == OpK) {
        std::cout << " " << getTokenStr(tree->attr.op);
      } else if (tree->kind.exp == ConstK) {
        std::cout << " " << tree->attr.val;
      } else if (tree->kind.exp == IdK || tree->kind.exp == CallK) {
        std::cout << " " << tree->attr.name;
      }
      std::cout << "\n";
    }

    indentno += 2;
    for (int i = 0; i < MAX_CHILDREN; i++) {
      printTree(tree->children[i]);
    }
    indentno -= 2;
    tree = tree->sibling;
  }
}
