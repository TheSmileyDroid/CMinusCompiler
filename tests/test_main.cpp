#include <gtest/gtest.h>

#include <string>

#if defined(__linux__) || defined(__APPLE__)
#define COMPILER_PATH "./compiler"
#elif defined(_WIN32)
#define COMPILER_PATH "compiler.exe"
#endif

TEST(HelloTest, BasicAssertions) { EXPECT_EQ(1, 1); }

TEST(ParserTest, BasicAssertions) {
  std::string command = COMPILER_PATH " ./tests/gcd.txt";
  int result = system(command.c_str());
  ASSERT_EQ(0, result);
}

TEST(ParserTest, AdditionalAssertions) {
  std::string command = COMPILER_PATH " ./tests/sort.txt";
  int result = system(command.c_str());
  ASSERT_EQ(0, result);
}

TEST(ParserTest, FibonacciTest) {
  std::string command = COMPILER_PATH " ./tests/fib.txt";
  int result = system(command.c_str());
  ASSERT_EQ(0, result);
}

TEST(ParserTest, ErrorAssertions) {
  std::string command = COMPILER_PATH " ./tests/gcd.1.txt";
  int result = system(command.c_str());
  ASSERT_NE(0, result);
}

TEST(LexicalTest, ErrorAssertions) {
  std::string command = COMPILER_PATH " ./tests/gcd_err.txt";
  int result = system(command.c_str());
  ASSERT_NE(0, result);
}

TEST(SemanticTest, ErrorAssertions) {
  std::string command = COMPILER_PATH " ./tests/gcd_semantic.txt";
  int result = system(command.c_str());
  ASSERT_EQ(1, result);
}

TEST(SemanticTest, UndeclaredVariableTest) {
  std::string command = COMPILER_PATH " ./tests/undeclared.txt";
  int result = system(command.c_str());
  ASSERT_NE(0, result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
