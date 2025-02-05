BISON     = bison
FLEX      = flex
CC        = gcc
CXX       = g++
CFLAGS    = -I. -Wall
CXXFLAGS  = -I./src -Wall -std=c++11 -g
LDFLAGS   =


# Fontes e objetos
SRCS      = src/main.cpp
OBJS      = src/main.o src/lex.yy.o src/parser.tab.o

.PHONY: all clean

all: compiler

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

compiler: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f src/*.o src/parser.tab.* src/lex.yy.* compiler
