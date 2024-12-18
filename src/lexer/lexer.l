%{
/*
 * Nome: Anna Júlia Magalhães Miranda
 * Nome: Gabriel Henrique Silva
 */

#include <stdio.h>
#include <ostream>
#include <iostream>
#include "parser.hpp"


int run_lexer(FILE* input);
%}

letra       [a-zA-Z]
digit       [0-9]
ID          {letra}{letra}*
NUM         {digit}{digit}*
whitespace  [ \t\n\r]

%option yylineno

%%
{whitespace}+                   {printf(yytext); }        ;
"/*"([^*]|(\*+[^*/]))*"*/"              ;
"if"                { printf("IF "); return IF; }
"else"              { printf("ELSE "); return ELSE; }
"int"               { printf("INT "); return INT; }
"void"              { printf("VOID "); return VOID; }
"return"            { printf("RETURN "); return RETURN; }
"while"             { printf("WHILE "); return WHILE; }
"=="                { printf("EQ "); return EQ; }
"!="                { printf("NE "); return NE; }
"<="                { printf("LE "); return LE; }
">="                { printf("GE "); return GE; }
"<"                 { printf("LT "); return LT; }
">"                 { printf("GT "); return GT; }
"="                 { printf("ASSIGN "); return ASSIGN; }
";"                 { printf("SEMICOLON "); return SEMICOLON; }
","                 { printf("COMMA "); return COMMA; }
"("                 { printf("LPAREN "); return LPAREN; }
")"                 { printf("RPAREN "); return RPAREN; }
"["                 { printf("LBRACKET "); return LBRACKET; }
"]"                 { printf("RBRACKET "); return RBRACKET; }
"{"                 { printf("LBRACE "); return LBRACE; }
"}"                 { printf("RBRACE "); return RBRACE; }
"+"                 { printf("PLUS "); return PLUS; }
"-"                 { printf("MINUS "); return MINUS; }
"*"                 { printf("TIMES "); return TIMES; }
"/"                 { printf("DIV "); return DIV; }

{ID}                { printf("ID(%s) ", yytext);  return ID; }
{NUM}               { printf("NUM(%s) ", yytext);  return NUM; }
<<EOF>>             { return EOF; }
.                   { return ERROR; }

%%


int get_token() {
    return yylex();
}

int run_lexer(FILE* input) {
    yyin = input;
    yylineno = 1;
    int token;
    while ((token = get_token()) != EOF)
    {
        if (token == ERROR)
        {
            std::cerr << "\n\nErro léxico na linha: " << yylineno << " -> " << yytext << std::endl;
            return 1;
        }
    }
    return 0;
}

int yywrap() {
    return 1;
}

int test_file(const char *filename)
{
    std::cout << std::endl
              << "Testing " << filename << "..." << std::endl;

    FILE *input = fopen(filename, "r");
    if (!input)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int result = run_lexer(input);
    fclose(input);

    if (result != 0)
    {
        std::cerr << "Test failed for " << filename << " with exit code " << result << std::endl;
        return result;
    }

    std::cout << std::endl;
    return 0;
}


/*
int main()
{
    // Test gcd.txt
    test_file("gcd.txt");

    // Test sort.txt
    test_file("sort.txt");

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
*/