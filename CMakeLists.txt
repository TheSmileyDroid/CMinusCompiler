cmake_minimum_required(VERSION 3.10)
project(CMinusCompiler)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)


# Find Bison
find_package(BISON REQUIRED)
BISON_TARGET(Parser src/parser/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)

# Find Flex
find_package(FLEX REQUIRED)
FLEX_TARGET(Lexer src/lexer/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})


# Include generated files by Flex and Bison
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Source files
file(GLOB LEXER_SRC_FILES
    src/**/*.cpp
    ${FLEX_Lexer_OUTPUTS}
    ${BISON_Parser_OUTPUTS}
)
add_library(lexer_lib ${FLEX_Lexer_OUTPUTS})
target_link_libraries(lexer_lib ${FLEX_LIBRARIES})

# Add Bison and Flex sources
add_executable(cminus_compiler src/main.cpp ${FLEX_Lexer_OUTPUTS} ${BISON_Parser_OUTPUTS})

# Link necessary libraries
target_link_libraries(cminus_compiler ${FLEX_LIBRARIES} ${BISON_LIBRARIES})

enable_testing()

add_executable(test_lexer tests/test_lexer.cpp)

add_dependencies(test_lexer cminus_compiler)

target_link_libraries(test_lexer lexer_lib ${FLEX_LIBRARIES} ${BISON_LIBRARIES})

add_test(NAME LexerTest COMMAND test_lexer)

add_executable(test_parser tests/test_parser.cpp)

add_dependencies(test_parser cminus_compiler)

target_link_libraries(test_parser lexer_lib ${FLEX_LIBRARIES} ${BISON_LIBRARIES})

add_test(NAME ParserTest COMMAND test_parser)