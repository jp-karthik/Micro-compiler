#include <iostream>
#include <vector>
#include <string>
#include "parser.tab.hpp"

extern FILE* yyin;

using namespace std;
int yylex();
void yyerror(char const* s); 
int yyparse(); /* parser prototype */

void yyerror(char const* s) {
    // cout << "Not Accepted\n";
    return;
}

int main(int argc, char* argv[]) {
    if (argc > 1) { 
        FILE* fp = fopen(argv[1], "r");
        if (fp) yyin = fp;
    }
    if (yyparse() == 0) {}
    return 0;
}