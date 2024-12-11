%{

#include <iostream>
#include <string>
#include "ast.hpp"

ASTNode* root;

extern int getToken(void);

int yylex(void);
int yyparse(void);
int yyerror(std::string message);

ASTNode* parse(void);
%}

%union {
    int num;
    char* str;
}

%token IF ELSE INT VOID RETURN WHILE

%token EQ NE LE GE LT GT ASSIGN SEMICOLON COMMA LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE PLUS MINUS TIMES DIV

%token <num> NUM

%token <str> ID

%token <str> ERROR


%%

program: declaration_list

declaration_list: declaration_list declaration | declaration

declaration: var_declaration | fun_declaration
    ;

var_declaration: type_specifier ID SEMICOLON | type_specifier ID LBRACKET NUM RBRACKET SEMICOLON
   

type_specifier: INT | VOID

fun_declaration: type_specifier ID LPAREN params RPAREN compound_stmt


params: param_list | VOID


param_list: param_list COMMA param | param


param: type_specifier ID | type_specifier ID LBRACKET RBRACKET


compound_stmt: LBRACE local_declarations statement_list RBRACE


local_declarations: local_declarations var_declaration | empty


statement_list: statement_list statement | empty


statement: expression_stmt | compound_stmt | selection_stmt | iteration_stmt | return_stmt | error

expression_stmt: expression SEMICOLON | SEMICOLON


selection_stmt: IF LPAREN expression RPAREN statement | IF LPAREN expression RPAREN statement ELSE statement


iteration_stmt: WHILE LPAREN expression RPAREN statement


return_stmt: RETURN SEMICOLON | RETURN expression SEMICOLON


expression: var ASSIGN expression | simple_expression


var: ID | ID LBRACKET expression RBRACKET


simple_expression: additive_expression relationalOperator additive_expression | additive_expression


relationalOperator: LT | LE | GT | GE | EQ | NE

additive_expression: additive_expression addOperator term | term


addOperator: PLUS | MINUS

term: term mulOperator factor | factor

mulOperator: TIMES | DIV

factor: LPAREN expression RPAREN | var | call | NUM


call: ID LPAREN args RPAREN

args: arg_list | empty

arg_list: arg_list COMMA expression | expression

empty:

ERROR


%%


int yyerror(std::string message)
{
    std::cerr << "Erro sintático: " << message << std::endl;
    return 1;
}


ASTNode* parse(void)
{ yyparse();
  return root;
}
