%{
/*
 * Nome: Anna Júlia Magalhães Miranda
 * Nome: Gabriel Henrique Silva
 */

#include <stdio.h>
#include <ostream>
#include <iostream>

int run_lexer(FILE* input);
%}

letra       [a-zA-Z]
digit       [0-9]
ID          {letra}{letra}*
NUM         {digit}{digit}*
whitespace  [ \t\n\r]

%%
{whitespace}+                           ;
"/*"([^*]|(\*+[^*/]))*"*/"              ;
"if"                { printf("IF "); }
"else"              { printf("ELSE "); }
"int"               { printf("INT "); }
"void"              { printf("VOID "); }
"return"            { printf("RETURN "); }
"while"             { printf("WHILE "); }
"=="                { printf(" == "); }
"!="                { printf(" != "); }
"<="                { printf(" <= "); }
">="                { printf(" >= "); }
"<"                 { printf(" < "); }
">"                 { printf(" > "); }
"="                 { printf(" = "); }
";"                 { printf(" ; "); }
","                 { printf(" , "); }
"("                 { printf(" ( "); }
")"                 { printf(" ) "); }
"["                 { printf(" [ "); }
"]"                 { printf(" ] "); }
"{"                 { printf(" { "); }
"}"                 { printf(" } "); }
"+"                 { printf(" + "); }
"-"                 { printf(" - "); }
"*"                 { printf(" * "); }
"/"                 { printf(" / "); }

{ID}                { printf("ID(%s)", yytext); }
{NUM}               { printf("NUM(%s)", yytext); }
.                   { printf("UNKNOWN(%s) ", yytext); }

%%

int run_lexer(FILE* input) {
    yyin = input;
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

void test_file(const char *filename)
{
    std::cout << std::endl
              << "Testing " << filename << "..." << std::endl;

    FILE *input = fopen(filename, "r");
    if (!input)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    int result = run_lexer(input);
    fclose(input);

    if (result != 0)
    {
        std::cerr << "Test failed for " << filename << " with exit code " << result << std::endl;
        exit(result);
    }

    std::cout << std::endl;
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