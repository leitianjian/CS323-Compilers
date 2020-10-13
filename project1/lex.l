%{
    #include"syntax.tab.h"
    #include"ASTNode.c"
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    char ttoc(const char*);
    void printError();
    int yycolno = 1;
    int error = 0;
    char *error_msg;
    #define YY_USER_ACTION \
            yylloc.first_line = yylineno; \
            yylloc.first_column = yycolno; \
            yylloc.last_line = yylineno; \
            yylloc.last_column = yycolno + yyleng; \
            yycolno += yyleng;
%}
%option yylineno
%option noyywrap

dec 0|[1-9][0-9]*
hex_ele [0-9a-fA-F]
hex 0[xX]{hex_ele}+
frac \.[0-9]+
exp [Ee][+-]?[0-9]+
int {dec}|{hex}
float {dec}{frac}{exp}?
ascii [\x00-\xff]
hf \\x{hex_ele}{hex_ele}
char \'({ascii}|{hf})\'
type int|char|float

id [a-zA-Z_][a-zA-Z0-9_]*

empty [ \r\t]

ill_id [0-9][a-zA-Z0-9_]+
not_hex_ele [G-Zg-z"#$%&:?@\^`|~]
not_hex 0[^xX]{not_hex_ele}({not_hex_ele}|{hex_ele}+)
not_hf \\x({not_hex_ele}|{not_hex_ele}{hex_ele}|{hex_ele}{not_hex_ele}|({hex_ele}|{not_hex_ele}){2}({hex_ele}|{not_hex_ele})+)

unknow ([\|\&]|{ill_id}|[$@]|\'{not_hf}\'|{not_hex})
%%

"("  { yylval.node_v = newKWLeaf("LP");     return LP; }
")"  { yylval.node_v = newKWLeaf("RP");     return RP; } 
"{"  { yylval.node_v = newKWLeaf("LC");     return LC; }
"}"  { yylval.node_v = newKWLeaf("RC");     return RC; }
"["  { yylval.node_v = newKWLeaf("LB");     return LB; }
"]"  { yylval.node_v = newKWLeaf("RB");     return RB; }
","  { yylval.node_v = newKWLeaf("COMMA");  return COMMA; }
"."  { yylval.node_v = newKWLeaf("DOT");    return DOT; }
";"  { yylval.node_v = newKWLeaf("SEMI");   return SEMI; }
"="  { yylval.node_v = newKWLeaf("ASSIGN"); return ASSIGN; }
"<"  { yylval.node_v = newKWLeaf("LT");     return LT; }
"<=" { yylval.node_v = newKWLeaf("LE");     return LE; }
">"  { yylval.node_v = newKWLeaf("GT");     return GT; }
">=" { yylval.node_v = newKWLeaf("GE");     return GE; }
"!=" { yylval.node_v = newKWLeaf("NE");     return NE; }
"==" { yylval.node_v = newKWLeaf("EQ");     return EQ; }
"+"  { yylval.node_v = newKWLeaf("PLUS");   return PLUS; } 
"-"  { yylval.node_v = newKWLeaf("MINUS");  return MINUS; }
"*"  { yylval.node_v = newKWLeaf("MUL");    return MUL; }
"/"  { yylval.node_v = newKWLeaf("DIV");    return DIV; }
"&&" { yylval.node_v = newKWLeaf("AND");    return AND; }
"||" { yylval.node_v = newKWLeaf("OR");     return OR; }
"!"  { yylval.node_v = newKWLeaf("NOT");    return NOT; }
"\n" { yycolno = 1; }

"struct" { yylval.node_v = newKWLeaf("STRUCT"); return STRUCT; }
"if"     { yylval.node_v = newKWLeaf("IF");     return IF; }
"while"  { yylval.node_v = newKWLeaf("WHILE");  return WHILE; }
"else"   { yylval.node_v = newKWLeaf("ELSE");   return ELSE; }
"return" { yylval.node_v = newKWLeaf("RETURN"); return RETURN; }

{type}  { yylval.node_v = newValueLeaf("TYPE", yytext);  return TYPE; }
{char}  { yylval.node_v = newValueLeaf("CHAR", yytext);  return CHAR; }
{id}    { yylval.node_v = newValueLeaf("ID", yytext);    return ID; }
{int}   { yylval.node_v = newValueLeaf("INT", yytext);   return INT; }
{float} { yylval.node_v = newValueLeaf("FLOAT", yytext); return FLOAT; }
{unknow} { error = 1; yylval.node_v = newValueLeaf("unknow", yytext); printError(NULL); return UNKNOW; }

{empty} { }
. { printError(NULL); return UNKNOW; }

%%
char ttoc (const char *text)
{
    if (strlen(text) == 3) {
        return text[1];
    }

    if (strlen(text) == 6) {
        char hex[3];
        hex[0] = text[3];
        hex[1] = text[4];
        hex[3] = '\0';
        return (char)strtol(hex, NULL, 16);
    }
}

void printError ()
{
    fprintf(out, "Error type A at Line %d: Unknown lexeme %s\n", yylineno, yytext);
}