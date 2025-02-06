#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) { EXPECT_EQ(1, 1); }

#include "gtest/gtest.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

TEST(ParserTest, BasicAssertions) {
  std::string command = "compiler ./tests/sort.txt";
  int result = system(command.c_str());
  ASSERT_EQ(0, result);
}

TEST(ParserTest, ErrorAssertions) {
  std::string command = "compiler ./tests/gcd.1.txt";
  int result = system(command.c_str());
  ASSERT_EQ(1, result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
