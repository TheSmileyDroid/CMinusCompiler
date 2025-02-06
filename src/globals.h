#ifndef GLOBALS_H
#define GLOBALS_H

/* Token kinds.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
enum yytokentype {
  YYEMPTY = -2,
  YYEOF = 0,            /* "end of file"  */
  YYerror = 256,        /* error  */
  YYUNDEF = 257,        /* "invalid token"  */
  IF = 258,             /* IF  */
  ELSE = 259,           /* ELSE  */
  INT = 260,            /* INT  */
  VOID = 261,           /* VOID  */
  RETURN = 262,         /* RETURN  */
  WHILE = 263,          /* WHILE  */
  EQ = 264,             /* EQ  */
  NE = 265,             /* NE  */
  LE = 266,             /* LE  */
  GE = 267,             /* GE  */
  LT = 268,             /* LT  */
  GT = 269,             /* GT  */
  ASSIGN = 270,         /* ASSIGN  */
  SEMICOLON = 271,      /* SEMICOLON  */
  COMMA = 272,          /* COMMA  */
  LPAREN = 273,         /* LPAREN  */
  RPAREN = 274,         /* RPAREN  */
  LBRACKET = 275,       /* LBRACKET  */
  RBRACKET = 276,       /* RBRACKET  */
  LBRACE = 277,         /* LBRACE  */
  RBRACE = 278,         /* RBRACE  */
  PLUS = 279,           /* PLUS  */
  MINUS = 280,          /* MINUS  */
  TIMES = 281,          /* TIMES  */
  DIV = 282,            /* DIV  */
  NUM = 283,            /* NUM  */
  ID = 284,             /* ID  */
  LOWER_THAN_ELSE = 285 /* LOWER_THAN_ELSE  */
};
typedef enum yytokentype yytoken_kind_t;
#endif

#define MAX_CHILDREN 3

typedef enum NodeKind { StatementK, ExpressionK } NodeKind;

typedef enum {
  IfK,
  WhileK,
  ReturnK,
  CompoundK,
  AssignK,
  VarDeclK,
  FunDeclK,
  ParamK
} StatementKind;

typedef enum { OpK, ConstK, IdK, CallK } ExpressionKind;

typedef enum { Void, Int } ExpType;

typedef struct treeNode {
  struct treeNode *children[MAX_CHILDREN];
  struct treeNode *sibling;
  int lineno;
  NodeKind nodeKind;
  union {
    StatementKind stmt;
    ExpressionKind exp;
  } kind;
  union {
    yytoken_kind_t op;
    int val;
    char *name;
  } attr;
  ExpType type;
} TreeNode;

#ifndef YYPARSER
#include "parser.tab.hpp"
#define ENDFILE 0
#endif

#define MAX_TOKEN_LENGTH 40

#endif
