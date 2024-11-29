#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

extern FILE *yyin;
extern int run_lexer(FILE *input);
extern void test_file(const char *filename);

int main()
{
    // Test gcd.txt
    test_file("../tests/gcd.txt");

    // Test sort.txt
    test_file("../tests/sort.txt");

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
