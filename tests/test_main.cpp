#include <gtest/gtest.h>

#include <string>

TEST(HelloTest, BasicAssertions) { EXPECT_EQ(1, 1); }

TEST(ParserTest, BasicAssertions) {
  std::string command = "./compiler ./tests/sort.txt";
  int result = system(command.c_str());
  ASSERT_EQ(0, result);
}

TEST(ParserTest, ErrorAssertions) {
  std::string command = "./compiler ./tests/gcd.1.txt";
  int result = system(command.c_str());
  ASSERT_NE(0, result);
}

TEST(LexicalTest, ErrorAssertions) {
  std::string command = "./compiler ./tests/gcd_err.txt";
  int result = system(command.c_str());
  ASSERT_NE(0, result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
