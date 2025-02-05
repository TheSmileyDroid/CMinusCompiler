%{

#include <iostream>
#include <string>
#include "compiler.h"

extern int getToken(void);

extern int yyparse(void);
extern int yyerror(std::string message);
extern void openFile(const char* filename);
extern char* yytext;

extern "C" {
    int yylex(void);
}


void parse();
%}

%union {
    int num;
    char* str;
}

%token IF ELSE INT VOID RETURN WHILE

%token EQ NE LE GE LT GT ASSIGN SEMICOLON COMMA LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE PLUS MINUS TIMES DIV

%token <num> NUM

%token <str> ID

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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


local_declarations: local_declarations var_declaration | ;


statement_list: statement_list statement | ;


statement: expression_stmt | compound_stmt | selection_stmt | iteration_stmt | return_stmt | error

expression_stmt: expression SEMICOLON | SEMICOLON


selection_stmt: IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
             | IF LPAREN expression RPAREN statement ELSE statement
             ;


iteration_stmt: WHILE LPAREN expression RPAREN statement


return_stmt: RETURN SEMICOLON | RETURN expression SEMICOLON


expression: var ASSIGN expression 
         | simple_expression
         ;

var: ID 
   | ID LBRACKET expression RBRACKET
   ;

simple_expression: additive_expression relationalOperator additive_expression 
                | additive_expression
                ;

relationalOperator: LT | LE | GT | GE | EQ | NE
                 ;

additive_expression: additive_expression addOperator term 
                  | term
                  ;

addOperator: PLUS 
          | MINUS
          ;

term: term mulOperator factor 
    | factor
    ;

mulOperator: TIMES 
          | DIV
          ;

factor: LPAREN expression RPAREN 
      | var 
      | call 
      | NUM
      ;

call: ID LPAREN args RPAREN
    ;

args: arg_list 
    | /* empty */
    ;

arg_list: arg_list COMMA expression 
        | expression
        ;




%%


int yyerror(std::string message)
{
    extern int yylineno;
    std::cerr << "Erro sintático na linha " << yylineno << ": " << message << std::endl;
    std::cerr << "Último token lido: " << yytext << std::endl;
    return 1;
}


void parse()
{ 
    yyparse();
}

void openFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        exit(1);
    }
    extern FILE* yyin;
    yyin = file;
}