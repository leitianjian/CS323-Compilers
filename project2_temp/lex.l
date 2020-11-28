%{
    #include"ASTNode.c"
    #include"TreeNode.cpp"
    #include<string>
    #include"syntax.tab.h"
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    char ttoc(const char*);
    void printError();
    int yycolno = 1;
    int error = 0;
    char *error_msg;
    extern "C" int yylex();
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
hex 0[xX](0|[1-9a-fA-F]{hex_ele}*)
frac \.[0-9]+
exp [Ee][+-]?[0-9]+
int {dec}|{hex}
float {dec}{frac}{exp}?
ascii [\x00-\xff]
hf \\x{hex_ele}{1,2}
char \'({ascii}|{hf})\'
type int|char|float

id [a-zA-Z_][a-zA-Z0-9_]*

empty [ \r\t]

ill_id [0-9][a-zA-Z0-9_]+
not_hex_ele [G-Zg-z"#$%&:?@\^`|~]
not_hex 0[^xX]{not_hex_ele}({not_hex_ele}|{hex_ele}+)
not_hf \\x({not_hex_ele}|{not_hex_ele}{hex_ele}|{hex_ele}{not_hex_ele}|({hex_ele}|{not_hex_ele}){2}({hex_ele}|{not_hex_ele})+)

unknow (.|[\|\&]|{ill_id}|[$@]|\'{not_hf}\'|{not_hex})
%%

"("  { return LP; }
")"  { return RP; } 
"{"  { return LC; }
"}"  { return RC; }
"["  { return LB; }
"]"  { return RB; }
","  { return COMMA; }
"."  { return DOT; }
";"  { return SEMI; }
"="  { return ASSIGN; }
"<"  { return LT; }
"<=" { return LE; }
">"  { return GT; }
">=" { return GE; }
"!=" { return NE; }
"==" { return EQ; }
"+"  { return PLUS; } 
"-"  { return MINUS; }
"*"  { return MUL; }
"/"  { return DIV; }
"&&" { return AND; }
"||" { return OR; }
"!"  { return NOT; }
"\n" { yycolno = 1; }

"struct" { return STRUCT; }
"if"     { return IF; }
"while"  { return WHILE; }
"else"   { return ELSE; }
"return" { return RETURN; }

{type}  { yylval.node_v = newValueLeaf("TYPE", yytext);  return TYPE; }
{char}  { yylval.node_v = newValueLeaf("CHAR", yytext);  return CHAR; }
{id}    { yylval.node_v = newValueLeaf("ID", yytext);    return ID; }
{int}   { yylval.node_v = newValueLeaf("INT", yytext);   return INT; }
{float} { yylval.node_v = newValueLeaf("FLOAT", yytext); return FLOAT; }
{empty} { }
{unknow} { error = 1; yylval.node_v = newValueLeaf("unknow", yytext); printError(); return UNKNOW; }

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