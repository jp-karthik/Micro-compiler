%option noyywrap

%{
    #include <iostream>
    //#include "model.hpp"
    #include<vector>
    #include<string>
    #include "parser.tab.hpp"
    int lineCounter = 1;
%}

VOID " "|\t|\n
COMMENT "//".*

IDENTIFIER [a-zA-Z][a-zA-Z0-9]*
STRINGLITERAL \"[^"]*\" 
INTLITERAL [0-9]+
FLOATLITERAL [0-9]*"."[0-9]+|-[0-9]*"."[0-9]+

SEMICOL [;]
COMMA [,]
LEFT_PAR [(]
RIGHT_PAR [)]
PLUS [+]
MINUS [-]
MUL [*]
DIV [/]
ASSIGN [:][=]

%%

\n {
    lineCounter++;
}

{VOID} {}
{COMMENT} {}

PROGRAM {return PROGRAM;}
BEGIN {return pBEGIN;}
END {return END;}
STRING {return STRING;}

FLOAT {
    yylval.str = strdup(yytext);
    return FLOAT;
}

INT {
    yylval.str = strdup(yytext);
    return INT;
}

VOID {return VOID;}

FUNCTION {return FUNCTION;}
RETURN {return RETURN;}
READ {return READ;}
WRITE {return WRITE;}

IF {return IF;}
ENDIF {return ENDIF;}
ELSE {return ELSE;}
CONTINUE {return CONTINUE;}
BREAK {return BREAK;}
WHILE {return WHILE;}
ENDWHILE {return ENDWHILE;}

{IDENTIFIER} {
    yylval.identifier = new std::pair<std::string, int>;
    (yylval.identifier)->first = std::string(yytext);
    (yylval.identifier)->second = lineCounter;
    return IDENTIFIER;
}

{STRINGLITERAL} {
    yylval.str = strdup(yytext);
    return STRINGLITERAL;
}

{INTLITERAL} {
    yylval.str = strdup(yytext);
    return INTLITERAL;
}

{FLOATLITERAL} {
    yylval.str = strdup(yytext);
    return FLOATLITERAL;
}

{ASSIGN} {return ASSIGN;}
{SEMICOL} {return SEMICOL;}
{COMMA} {return COMMA;}
{LEFT_PAR} {return LEFT_PAR;}
{RIGHT_PAR} {return RIGHT_PAR;}
{PLUS} {return PLUS;}
{MINUS} {return MINUS;}
{MUL} {return MUL;}
{DIV} {return DIV;}

\= {return EQ;}
\!\= {return NEQ;}
\>\= {return GEQ;}
\> {return GT;} 
\<\= {return LEQ;}
\< {return LT;}

. {return 0;}

%%