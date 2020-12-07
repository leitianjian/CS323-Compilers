%{
    #include "parser.hpp"
    #include "scanner.h"
    // #include "location.hh"
    #include "interpreter.h"
    #include "ASTNode.h"
    #include <iostream>
	#include <cstdlib>
    #include <string>
    // #include<stdio.h>
    // #include<stdlib.h>
    // #include<string.h>
    
    // using namespace Compiler;
    // char ttoc(const char*);
    // void printError();
    int yycolno = 1;
    // int error = 0;
    // char *error_msg;
    #define yyterminate() Compiler::Parser::make_END(m_driver.m_location)

    #define YY_USER_ACTION \
            m_driver.m_location.begin.line = yylineno; \
            m_driver.m_location.begin.column = yycolno; \
            m_driver.m_location.end.line = yylineno; \
            m_driver.m_location.end.column = yycolno + yyleng; \
            yycolno += yyleng;
%}
%option yylineno
%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="Compiler_"

dec 0|([1-9][0-9]*)
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
not_hex 0[xX]{not_hex_ele}({not_hex_ele}*|{hex_ele}+)
not_hf \\x({not_hex_ele}|{not_hex_ele}{hex_ele}|{hex_ele}{not_hex_ele}|({hex_ele}|{not_hex_ele}){2}({hex_ele}|{not_hex_ele})+)

unknow (.|[\|\&]|{ill_id}|[$@]|\'{not_hf}\'|{not_hex})
%%

"("  { const ASTNode* ptr = new ASTNode("LP");    return Compiler::Parser::make_LP(   ptr,   m_driver.m_location); }
")"  { const ASTNode* ptr = new ASTNode("RP");    return Compiler::Parser::make_RP(   ptr,   m_driver.m_location); } 
"{"  { const ASTNode* ptr = new ASTNode("LC");    return Compiler::Parser::make_LC(   ptr,   m_driver.m_location); }
"}"  { const ASTNode* ptr = new ASTNode("RC");    return Compiler::Parser::make_RC(   ptr,   m_driver.m_location); }
"["  { const ASTNode* ptr = new ASTNode("LB");    return Compiler::Parser::make_LB(   ptr,   m_driver.m_location); }
"]"  { const ASTNode* ptr = new ASTNode("RB");    return Compiler::Parser::make_RB(   ptr,   m_driver.m_location); }
","  { const ASTNode* ptr = new ASTNode("COMMA"); return Compiler::Parser::make_COMMA(ptr,   m_driver.m_location); }
"."  { const ASTNode* ptr = new ASTNode("DOT");   return Compiler::Parser::make_DOT(  ptr,   m_driver.m_location); }
";"  { const ASTNode* ptr = new ASTNode("SEMI");  return Compiler::Parser::make_SEMI( ptr,   m_driver.m_location); }
"="  { const ASTNode* ptr = new ASTNode("ASSIGN"); return Compiler::Parser::make_ASSIGN( ptr, m_driver.m_location); }
"<"  { const ASTNode* ptr = new ASTNode("LT");     return Compiler::Parser::make_LT(     ptr, m_driver.m_location); }
"<=" { const ASTNode* ptr = new ASTNode("LE");     return Compiler::Parser::make_LE(     ptr, m_driver.m_location); }
">"  { const ASTNode* ptr = new ASTNode("GT");     return Compiler::Parser::make_GT(     ptr, m_driver.m_location); }
">=" { const ASTNode* ptr = new ASTNode("GE");     return Compiler::Parser::make_GE(     ptr, m_driver.m_location); }
"!=" { const ASTNode* ptr = new ASTNode("NE");     return Compiler::Parser::make_NE(     ptr, m_driver.m_location); }
"==" { const ASTNode* ptr = new ASTNode("EQ");     return Compiler::Parser::make_EQ(     ptr, m_driver.m_location); }
"+"  { const ASTNode* ptr = new ASTNode("PLUS");   return Compiler::Parser::make_PLUS(   ptr, m_driver.m_location); } 
"-"  { const ASTNode* ptr = new ASTNode("MINUS");  return Compiler::Parser::make_MINUS(  ptr, m_driver.m_location); }
"*"  { const ASTNode* ptr = new ASTNode("MUL");    return Compiler::Parser::make_MUL(    ptr, m_driver.m_location); }
"/"  { const ASTNode* ptr = new ASTNode("DIV");    return Compiler::Parser::make_DIV(    ptr, m_driver.m_location); }
"&&" { const ASTNode* ptr = new ASTNode("AND");    return Compiler::Parser::make_AND(    ptr, m_driver.m_location); }
"||" { const ASTNode* ptr = new ASTNode("OR");     return Compiler::Parser::make_OR(     ptr, m_driver.m_location); }
"!"  { const ASTNode* ptr = new ASTNode("NOT");    return Compiler::Parser::make_NOT(    ptr, m_driver.m_location); }
"\n" { yycolno = 1; }

"struct" { const ASTNode* ptr = new ASTNode("STRUCT"); return Compiler::Parser::make_STRUCT(ptr, m_driver.m_location); }
"if"     { const ASTNode* ptr = new ASTNode("IF");     return Compiler::Parser::make_IF(    ptr, m_driver.m_location); }
"while"  { const ASTNode* ptr = new ASTNode("WHILE");  return Compiler::Parser::make_WHILE( ptr, m_driver.m_location); }
"else"   { const ASTNode* ptr = new ASTNode("ELSE");   return Compiler::Parser::make_ELSE(  ptr, m_driver.m_location); }
"return" { const ASTNode* ptr = new ASTNode("RETURN"); return Compiler::Parser::make_RETURN(ptr, m_driver.m_location); }

{type}  { const ASTNode* ptr = new ASTNode("TYPE", yytext); return Compiler::Parser::make_TYPE(ptr,   m_driver.m_location); }
{char}  { const ASTNode* ptr = new ASTNode("CHAR", yytext); return Compiler::Parser::make_CHAR(ptr,   m_driver.m_location); }
{id}    { const ASTNode* ptr = new ASTNode("ID", yytext);   return Compiler::Parser::make_ID(  ptr,   m_driver.m_location); }
{int}   { const ASTNode* ptr = new ASTNode("INT", yytext);  return Compiler::Parser::make_INT( ptr,   m_driver.m_location); }
{float} { const ASTNode* ptr = new ASTNode("FLOAT", yytext); return Compiler::Parser::make_FLOAT(ptr, m_driver.m_location); }
{empty} { }
{unknow} { m_driver.setErrorFlag(); m_driver.appendErrorMsg(0, yytext, m_driver.m_location.begin.line); const ASTNode* ptr = new ASTNode("unknow", yytext);  return Compiler::Parser::make_UNKNOW(ptr, m_driver.m_location);}

<<EOF>>     { yylineno = 1; yycolno = 1; yyleng = 0; yytext = NULL; return yyterminate(); }
%%

/* void resetLine()
{
    yylineno = 1;
    yycolno = 1;
    yyleng = 0;
    yytext = "";
} */
/* char ttoc (const char *text)
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
} */