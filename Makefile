dev: task
	./task

task: name.cpp
	g++ name.cpp -o task

clean:
	rm -f task parser.tab.hpp parser.tab.cpp lex.yy.cpp

compiler: parser.tab.cpp lex.yy.cpp main.cpp 
	g++ lex.yy.cpp parser.tab.cpp main.cpp -o compiler

parser.tab.cpp: parser.ypp
	bison -d -t parser.ypp

lex.yy.cpp: lexer.l 
	flex -o lex.yy.cpp lexer.l 