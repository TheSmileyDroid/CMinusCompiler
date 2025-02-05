%{
/*
 * Nome: Anna Júlia Magalhães Miranda
 * Nome: Gabriel Henrique Silva
 */

#include <stdio.h>
#include "src/parser.tab.hpp"

extern YYSTYPE yylval;
extern int yylex(void);

int run_lexer(FILE* input);
%}

letra       [a-zA-Z]
digit       [0-9]
ID          {letra}{letra}*
NUM         {digit}{digit}*
whitespace  [ \t\n\r]

%option yylineno
%option noyywrap

%%
{whitespace}+                   {printf("%s", yytext); }        ;
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
.                   { printf("ERRO LÉXICO: caractere inválido '%s' na linha %d\n", yytext, yylineno); }

%%


int get_token() {
    return yylex();
}
