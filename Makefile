BISON     = bison
FLEX      = flex
CC        = gcc
CXX       = g++
CFLAGS    = -I. -Wall -g
CXXFLAGS  = -I./src -Wall -std=c++20 -g
LDFLAGS   =

# Fontes e objetos
SRCS      = src/main.cpp
OBJS      = src/main.o src/lex.yy.o src/parser.tab.o src/utils.o src/symtab.o src/semantic.o

.PHONY: all clean

all: compiler

src/utils.o: src/utils.cpp src/utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/parser.tab.cpp: src/parser.ypp
	$(BISON) -d -v -g $< -o $@ -Wcounterexamples

src/parser.tab.hpp: src/parser.tab.cpp

src/lex.yy.c: src/lexer.l src/parser.tab.cpp
	$(FLEX) -o $@ $<

src/parser.tab.o: src/parser.tab.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

src/lex.yy.o: src/lex.yy.c src/parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

src/main.o: src/main.cpp src/parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/symtab.o: src/symtab.cpp src/symtab.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/semantic.o: src/semantic.cpp src/semantic.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

compiler: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f src/*.o src/parser.tab.* src/lex.yy.* compiler

.PHONY: release
release: clean
	$(MAKE) CXXFLAGS="-I./src -Wall -std=c++20 -O2" LDFLAGS="-static" compiler

GTEST_DIR = $(CURDIR)/googletest
GTEST_LIB = $(GTEST_DIR)/build/lib/libgtest.a
GTEST_INCLUDE = $(GTEST_DIR)/googletest/include

$(GTEST_LIB):
	git -C googletest pull || git clone https://github.com/google/googletest.git
	cd googletest && mkdir -p build && cd build && cmake .. -G"Unix Makefiles" && make

tests/test_main.o: tests/test_main.cpp $(GTEST_LIB) compiler
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE) -c $< -o $@

test: tests/test_main.o $(GTEST_LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lpthread
	./test
