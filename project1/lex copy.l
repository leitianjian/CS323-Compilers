%{
    #include"syntax.tab.h"
    #include"ASTNode.c"
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    char ttoc(const char*);
    void printError(FILE *);
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

"("  { printf("LP\n");     yylval.node_v = newKWLeaf("LP");     return LP; }
")"  { printf("RP\n");     yylval.node_v = newKWLeaf("RP");     return RP; } 
"{"  { printf("LC\n");     yylval.node_v = newKWLeaf("LC");     return LC; }
"}"  { printf("RC\n");     yylval.node_v = newKWLeaf("RC");     return RC; }
"["  { printf("LB\n");     yylval.node_v = newKWLeaf("LB");     return LB; }
"]"  { printf("RB\n");     yylval.node_v = newKWLeaf("RB");     return RB; }
","  { printf("COMMA\n");  yylval.node_v = newKWLeaf("COMMA");  return COMMA; }
"."  { printf("DOT\n");    yylval.node_v = newKWLeaf("DOT");    return DOT; }
";"  { printf("SEMI\n");   yylval.node_v = newKWLeaf("SEMI");   return SEMI; }
"="  { printf("ASSIGN\n"); yylval.node_v = newKWLeaf("ASSIGN"); return ASSIGN; }
"<"  { printf("LT\n");     yylval.node_v = newKWLeaf("LT");     return LT; }
"<=" { printf("LE\n");     yylval.node_v = newKWLeaf("LE");     return LE; }
">"  { printf("GT\n");     yylval.node_v = newKWLeaf("GT");     return GT; }
">=" { printf("GE\n");     yylval.node_v = newKWLeaf("GE");     return GE; }
"!=" { printf("NE\n");     yylval.node_v = newKWLeaf("NE");     return NE; }
"==" { printf("EQ\n");     yylval.node_v = newKWLeaf("EQ");     return EQ; }
"+"  { printf("PLUS\n");   yylval.node_v = newKWLeaf("PLUS");   return PLUS; } 
"-"  { printf("MINUS\n");  yylval.node_v = newKWLeaf("MINUS");  return MINUS; }
"*"  { printf("MUL\n");    yylval.node_v = newKWLeaf("MUL");    return MUL; }
"/"  { printf("DIV\n");    yylval.node_v = newKWLeaf("DIV");    return DIV; }
"&&" { printf("AND\n");    yylval.node_v = newKWLeaf("AND");    return AND; }
"||" { printf("OR\n");     yylval.node_v = newKWLeaf("OR");     return OR; }
"!"  { printf("NOT\n");    yylval.node_v = newKWLeaf("NOT");    return NOT; }
"\n" { yycolno = 1; }

"struct" { printf("STRUCT\n"); yylval.node_v = newKWLeaf("STRUCT"); return STRUCT; }
"if"     { printf("IF\n");     yylval.node_v = newKWLeaf("IF");     return IF; }
"while"  { printf("WHILE\n");  yylval.node_v = newKWLeaf("WHILE");  return WHILE; }
"else"   { printf("ELSE\n");   yylval.node_v = newKWLeaf("ELSE");   return ELSE; }
"return" { printf("RETURN\n"); yylval.node_v = newKWLeaf("RETURN"); return RETURN; }

{type}  { printf("TYPE %s\n", yytext);  yylval.node_v = newValueLeaf("TYPE", yytext);  return TYPE; }
{char}  { printf("CHAR %s\n", yytext);  yylval.node_v = newValueLeaf("CHAR", yytext);  return CHAR; }
{id}    { printf("ID %s\n", yytext);    yylval.node_v = newValueLeaf("ID", yytext);    return ID; }
{int}   { printf("INT %s\n", yytext);   yylval.node_v = newValueLeaf("INT", yytext);   return INT; }
{float} { printf("FLOAT %s\n", yytext); yylval.node_v = newValueLeaf("FLOAT", yytext); return FLOAT; }
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

void printError (FILE* out)
{
    fprintf(stdout, "Error type A at Line %d: Unknown characters %s\n", yylineno, yytext);
}