%{
    #include"syntax.tab.h"
    #include"json.c"
%}
%option noyywrap

unic u[0-9a-fA-F]{4}
esc \\([\"\\/bfnrt]|{unic})
scp [^"\\\x00-\x1f]
string \"({esc}|{scp})*\"

int 0|[1-9][0-9]*
frac \.[0-9]+
exp [Ee][+-]?[0-9]+
number -?{int}{frac}?{exp}?

empty [ \n\r\t]

%%

"{" { return LC; }
"}" { return RC; }
"[" { return LB; }
"]" { return RB; }
":" { return COLON; }
"," { return COMMA; }

"true" { yylval.b = 1; return TRUE; }
"false" { yylval.b = 0; return FALSE; }
"null" { yylval.json = init_json(CA_VNULL); return VNULL; }

{string} { strcpy(yylval.string, yytext); return STRING; }
{number} { yylval.number = atof(yytext); return NUMBER; }

{empty} {}

. { printf("lexical error: %s\n", yytext); }
