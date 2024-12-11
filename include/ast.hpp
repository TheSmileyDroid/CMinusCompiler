#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

enum NodeType
{
    NODE_PROGRAM,
    NODE_DECLARATION,

};

typedef struct ASTNode
{
    NodeType type;
    std::string value;
    std::vector<ASTNode *> children;

    ASTNode(NodeType t, const std::string &val = "") : type(t), value(val) {}
} ASTNode;

#endif // AST_HPP