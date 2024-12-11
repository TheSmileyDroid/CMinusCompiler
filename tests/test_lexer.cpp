#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

extern FILE *yyin;
extern int run_lexer(FILE *input);
extern int test_file(const char *filename);

int main()
{
    // Test gcd.txt
    int err = test_file("../tests/gcd.txt");
    if (err != 0)
    {
        std::cerr << "Test failed with error code: " << err << std::endl;
        return err;
    }

    // Test sort.txt
    err = test_file("../tests/sort.txt");
    if (err != 0)
    {
        std::cerr << "Test failed with error code: " << err << std::endl;
        return err;
    }

    // Test gcd_err.txt (should fail)
    err = test_file("../tests/gcd_err.txt");
    if (err == 0)
    {
        std::cerr << "Test failed with error code: " << err << std::endl;
        return err;
    }

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
