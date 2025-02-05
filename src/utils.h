#ifndef UTILS_H
#define UTILS_H

#include "globals.h"
#include <string>

TreeNode *newStmtNode(StatementKind kind);
TreeNode *newExpNode(ExpressionKind kind);

void printTree(TreeNode *tree);
void printSpaces(int spaces);

std::string getExpKindStr(ExpressionKind kind);
std::string getStmtKindStr(StatementKind kind);
std::string getExpTypeStr(ExpType type);
std::string getTokenStr(int token);

#endif
