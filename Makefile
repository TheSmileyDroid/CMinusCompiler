


all: compiler src/parser.tab.c src/lex.yy.c

src/parser.tab.c: src/parser.y
	bison -d -v -g src/parser.y -o src/parser.tab.c -Wcounterexamples

src/lex.yy.c: src/parser.tab.c src/lexer.l
	flex -o src/lex.yy.c src/lexer.l

src/lex.yy.o: src/lex.yy.c
	gcc -I. -c src/lex.yy.c -o src/lex.yy.o

compiler: src/parser.tab.c src/lex.yy.o src/main.cpp
	g++ -I./src -o compiler src/lex.yy.o src/parser.tab.c src/main.cpp -lfl

clean:
	rm src/lex.yy.c src/parser.dot src/parser.output src/parser.tab.c src/parser.tab.h