
#include "parser.hpp"
#include "ast.hpp"
#include <iostream>
#include <fstream>

extern ASTNode *parse(void);
extern FILE *yyin;

int test_parse_file(const char *filename)
{
    FILE *input = fopen(filename, "r");
    if (input == nullptr)
    {
        return 1;
    }

    yyin = input;
    ASTNode *root = parse();
    fclose(input);

    return 0;
}

int main()
{
    // Test gcd.txt
    int err = test_parse_file("../tests/gcd.txt");
    if (err != 0)
    {
        std::cerr << "Test failed with error code: " << err << std::endl;
        return err;
    }

    // Test sort.txt
    err = test_parse_file("../tests/sort.txt");
    if (err != 0)
    {
        std::cerr << "Test failed with error code: " << err << std::endl;
        return err;
    }

    // Test gcd_err.txt (should fail)
    err = test_parse_file("../tests/gcd_err.txt");
    if (err == 0)
    {
        std::cerr << "Test failed with error code: " << err << std::endl;
        return err;
    }

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}