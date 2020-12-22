// %{
//     #include"lex.yy.c"
//     struct ASTNode *root = NULL;
//     void SYNError(const char *, int);
//     void yyerror(const char*);
//     void initiate();
// %}
%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { Parser }

%define api.token.constructor
%define api.value.type variant
/* %define parse.assert */
%define api.namespace { Compiler }
%code requires
{
    #include <iostream>
    /* #include <stdint.h> */
    #include "ASTNode.h"
    #include "SymTab.h"

    using namespace std;

    namespace Compiler {
        class Scanner;
        class Interpreter;
    }
}

%code top
{
    #include <iostream>
    #include "scanner.h"
    #include "parser.hpp"
    #include "interpreter.h"
    #include "location.hh"
    
    // yylex() arguments are defined in parser.y
    static Compiler::Parser::symbol_type yylex(Compiler::Scanner &scanner, Compiler::Interpreter &driver) {
        return scanner.get_next_token();
    }
    
    // you can accomplish the same thing by inlining the code using preprocessor
    // x and y are same as in above static function
    // #define yylex(x, y) scanner.get_next_token()
    
    using namespace Compiler;
}

%lex-param { Compiler::Scanner &scanner }
%lex-param { Compiler::Interpreter &driver }
%parse-param { Compiler::Scanner &scanner }
%parse-param { Compiler::Interpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}
/* %union{
    struct ASTNode *node_v;
} */
%token END 0
%token <Compiler::ASTNode*> LP RP LC RC LB RB COMMA DOT SEMI 
%token <Compiler::ASTNode*> LT LE GT GE NE EQ PLUS MINUS MUL DIV AND OR NOT ASSIGN
%token <Compiler::ASTNode*> STRUCT 
%token <Compiler::ASTNode*> ID 
%token <Compiler::ASTNode*> CHAR
%token <Compiler::ASTNode*> INT 
%token <Compiler::ASTNode*> FLOAT
%token <Compiler::ASTNode*> WHILE TYPE
%token <Compiler::ASTNode*> IF ELSE RETURN UNKNOW
/* %token <Compiler::ASTNode*> READ WRITE */

%type  <Compiler::ASTNode*> Program ExtDefList ExtDef ExtDecList
%type  <Compiler::ASTNode*> Specifier StructSpecifier 
%type  <Compiler::ASTNode*> VarDec FunDec VarList ParamDec
%type  <Compiler::ASTNode*> CompSt StmtList Stmt DefList Def DecList Dec
%type  <Compiler::ASTNode*> Exp Args 

%nonassoc LOWER_ELSE
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left LT LE GT GE EQ NE
%left PLUS MINUS
%left MUL DIV
%right UMINUS NOT
%left LP RP LB RB DOT
%left UNKNOW

/* %start Program */
%%

Program: 
      ExtDefList {
          $$ = new ASTNode("Program", @$.begin.line);
          driver.setRoot($$);
          $$->addChild(1, $1);
      }
    ;
ExtDefList:
      ExtDef ExtDefList {
          $$ = new ASTNode("ExtDefList", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    | {
          $$ = new ASTNode("ExtDefList", @$.begin.line); 
      }
    | error {
          std::cout << "Please check by yourself" << endl;
          driver.setErrorFlag();
          driver.appendErrorMsg(1, std::string("Please check by yourself"), @$.begin.line);
          $$ = new ASTNode("Error", @$.begin.line);
      }
    ;
ExtDef:
      Specifier ExtDecList SEMI {
          $$ = new ASTNode("ExtDef", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Specifier SEMI {
          $$ = new ASTNode("ExtDef", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    | Specifier FunDec CompSt {
          $$ = new ASTNode("ExtDef", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Specifier ExtDecList error {
          std::cout << "Missing semicolon ';'" << std::endl;
          driver.setErrorFlag();
          driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), @$.begin.line);
          $$ = new ASTNode("Error", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    /* | Specifier INT error {
          std::cout << "unknown lexme "
      } */
    | Specifier error {
          std::cout << "Missing semicolon ';'" << std::endl;
          driver.setErrorFlag();
          driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), @$.begin.line);
          $$ = new ASTNode("Error", @$.begin.line);
          $$->addChild(1, $1);
      }
    ;
ExtDecList:
      VarDec {
          $$ = new ASTNode("ExtDecList", @$.begin.line);
          $$->addChild(1, $1);
      }
    | VarDec COMMA ExtDecList {
          $$ = new ASTNode("ExtDecList", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    ;
Specifier:
      TYPE {
          $$ = new ASTNode("Specifier", @$.begin.line);
          $$->addChild(1, $1);
      }
    | StructSpecifier {
          $$ = new ASTNode("Specifier", @$.begin.line);
          $$->addChild(1, $1);
      }
    ;
StructSpecifier:
      STRUCT ID LC DefList RC {
          $$ = new ASTNode("StructSpecifier", @$.begin.line);
          $$->addChild(5, $1, $2, $3, $4, $5);
      }
    | STRUCT ID {
          $$ = new ASTNode("StructSpecifier", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    ;
VarDec:
      ID {
          $$ = new ASTNode("VarDec", @$.begin.line);
          $$->addChild(1, $1);
      }
    | VarDec LB INT RB {
          $$ = new ASTNode("VarDec", @$.begin.line);
          $$->addChild(4, $1, $2, $3, $4);
      }
    | UNKNOW {
          $$ = new ASTNode("UNKNOW_VarDec", @$.begin.line);
          $$->addChild(1, $1);
      }
    ;
FunDec:
      ID LP VarList RP {
          $$ = new ASTNode("FunDec", @$.begin.line);
          $$->addChild(4, $1, $2, $3, $4);
      }
    | ID LP RP {
          $$ = new ASTNode("FunDec", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | ID LP error {
        std::cout << "Missing closing parenthesis ')'" << endl;
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing closing parenthesis ')'"), @$.begin.line);
        $$ = new ASTNode("Error", @$.begin.line);
        $$->addChild(2, $1, $2);
      }
    | ID LP VarList error {
        std::cout << "Missing closing parenthesis ')'" << std::endl;
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing closing parenthesis ')'"), @$.begin.line);
        $$ = new ASTNode("Error", @$.begin.line);
        $$->addChild(3, $1, $2, $3);
      }
    | ID LP ID RP error {
        std::cout << "Missing specifier" << std::endl;
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing specifier"), @$.begin.line);
        $$ = new ASTNode("Error", @$.begin.line);
        $$->addChild(4, $1, $2, $3, $4);
      }
    ;
VarList:
      ParamDec COMMA VarList {
          $$ = new ASTNode("VarList", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | ParamDec {
          $$ = new ASTNode("VarList", @$.begin.line);
          $$->addChild(1, $1);
      }
    ;
ParamDec:
      Specifier VarDec {
          $$ = new ASTNode("ParamDec", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    ;
CompSt:
      LC DefList StmtList RC {
          $$ = new ASTNode("CompSt", @$.begin.line);
          $$->addChild(4, $1, $2, $3, $4);
      }
    ;
StmtList:
      Stmt StmtList {
          $$ = new ASTNode("StmtList", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    | {
          $$ = new ASTNode("StmtList", @$.begin.line); 
      }
    ;
Stmt:
      Exp SEMI {
          $$ = new ASTNode("Stmt", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    | CompSt {
          $$ = new ASTNode("Stmt", @$.begin.line);
          $$->addChild(1, $1);
      }
    | RETURN Exp SEMI {
          $$ = new ASTNode("Stmt", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | IF LP Exp RP Stmt %prec LOWER_ELSE {
          $$ = new ASTNode("Stmt", @$.begin.line);
          $$->addChild(5, $1, $2, $3, $4, $5);
      }
    | IF LP Exp RP Stmt ELSE Stmt {
          $$ = new ASTNode("Stmt", @$.begin.line);
          $$->addChild(7, $1, $2, $3, $4, $5, $6, $7);
      }
    | WHILE LP Exp RP Stmt {
          $$ = new ASTNode("Stmt", @$.begin.line);
          $$->addChild(5, $1, $2, $3, $4, $5);
      }
    | Exp error {
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), @$.begin.line);
        std::cout << "Missing semicolon ';'" << std::endl;
        $$ = new ASTNode("Error", @$.begin.line);
        $$->addChild(1, $1);
      }
    | RETURN Exp error {
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), @$.begin.line);
        std::cout << "Missing semicolon ';'" << std::endl;
        $$ = new ASTNode("Error", @$.begin.line);
        $$->addChild(2, $1, $2);
      }
    ;
DefList:
      Def DefList {
          $$ = new ASTNode("DefList", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    | {
          $$ = new ASTNode("DefList", @$.begin.line); 
      }
    ;
Def:
      Specifier DecList SEMI {
          $$ = new ASTNode("Def", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Specifier DecList error {
          driver.setErrorFlag();
          driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), @error.begin.line);
          std::cout << "Missing semicolon ';'" << std::endl;
          $$ = new ASTNode("Error", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    ;
DecList:
      Dec {
          $$ = new ASTNode("DecList", @$.begin.line);
          $$->addChild(1, $1);
      }
    | Dec COMMA DecList {
          $$ = new ASTNode("DecList", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    ;
Dec: 
      VarDec {
          $$ = new ASTNode("Dec", @$.begin.line);
          $$->addChild(1, $1);
      }
    | VarDec ASSIGN Exp {
          $$ = new ASTNode("Dec", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    ;
Exp:
      Exp ASSIGN Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp AND Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp OR Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp LT Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp LE Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp GT Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp GE Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp NE Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp EQ Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp PLUS Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp MINUS Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp MUL Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp DIV Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp UNKNOW Exp {
          $$ = new ASTNode("UNKNOW_Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | LP Exp RP {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | MINUS Exp %prec UMINUS {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    | NOT Exp {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    | ID LP Args RP {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(4, $1, $2, $3, $4);
      }
    | ID LP RP {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    /* | READ LP RP {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | WRITE LP Exp RP {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(4, $1, $2, $3);
      } */
    | Exp LB Exp RB {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(4, $1, $2, $3, $4);
      }
    | Exp DOT ID {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | ID {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(1, $1);
      }
    | INT {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(1, $1);
      }
    | FLOAT {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(1, $1);
      }
    | CHAR {
          $$ = new ASTNode("Exp", @$.begin.line);
          $$->addChild(1, $1);
      }
    | ID LP Args error {
          driver.setErrorFlag();
          std::cout << "Missing closing parenthesis ')'" << endl;
          driver.appendErrorMsg(1, std::string("Missing closing parenthesis ')'"), @$.begin.line);
          $$ = new ASTNode("Error_Exp", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | ID LP error {
          driver.setErrorFlag();
          std::cout << "Missing closing parenthesis ')'" << endl;
          driver.appendErrorMsg(1, std::string("Missing closing parenthesis ')'"), @$.begin.line);
          $$ = new ASTNode("Error_Exp", @$.begin.line);
          $$->addChild(2, $1, $2);
      }
    | UNKNOW {
          $$ = new ASTNode("UNKNOW_Exp", @$.begin.line);
          $$->addChild(1, $1);
      }
    ;
Args:
      Exp COMMA Args {
          $$ = new ASTNode("Args", @$.begin.line);
          $$->addChild(3, $1, $2, $3);
      }
    | Exp {
          $$ = new ASTNode("Args", @$.begin.line);
          $$->addChild(1, $1);
      }
    ;

%%

void Compiler::Parser::error(const location &loc, const std::string &msg) 
{
    /* fprintf(out, "Error type B at Line %d: %s\n", loc.begin.line, s); */
    cout << "Error type B at line " << loc.begin.line << ": " << msg << "\n";
}
 /* void SYNError(const char *s, int line)
{
    fprintf(out, "Error type B at Line %d: %s\n", line, s);
} */

/* void yyerror(const char *s){
    fprintf(out, "syntax error: must be recovered \n");
    fprintf(out, "Error type B at Line %d: %s\n", yylloc.first_line, s);
    yyerrok;
} */

/* void initiate() {
    yycolno = 1;
    yylineno = 1;
    yytext = "";
    yyleng = 0;
    error = 0;
    root = NULL;
}  */

/* int main(int argc, char **argv){
    if(argc == 1) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    } else {
        for (int i = 1; i < argc; ++ i) {
            initiate();
            int name_len = strlen(argv[i]);
            char *out_name = (char *)malloc(name_len + 1);
            strcpy(out_name, argv[i]);
            out_name[name_len - 3] = 'o';
            out_name[name_len - 2] = 'u';
            out_name[name_len - 1] = 't';
            out_name[name_len] = '\0';
            char buf[1024];
            int len;
            FILE *fp;
            if(!(fp = fopen(argv[i],"r")))
            {
                perror("fail to read");
                exit (1) ;
            }
            out = fopen(out_name, "w");
            yyrestart(fp);
            yyparse();
            if(!error)
                dfsPrint(root, 0);
            fclose(fp);
            fclose(out);
        }
    }
    return 0;
} */